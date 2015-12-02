/* 
 * File:   SerialInterface.cpp
 * Author: Taran
 * 
 * Created on 7 Май 2015 г., 17:30
 */

#include "EthlInterface.h"
#include <QDebug>
#include <QDataStream>
#include <math.h>
#include <QDir>

EthInterface::EthInterface(int timeOffset, quint16 udpPort) {
    
    tcpSocket = new QTcpSocket(this);
    ds = new QDataStream(tcpSocket);
    
    timeSender = new TimeSender(udpPort);
    
    this->timeOffset = timeOffset;
    
    lla[0] = 0.0;
    lla[1] = 0.0;
    lla[2] = 0.0;
    
    plot[0] = new float[PlotLength];
    plot[1] = new float[PlotLength];
    
    packetCounter = 0;
    packetErrorCounter = 0;
    
    memset(&settings, 0, sizeof(rx_settings));
    memset(&sol, 0, sizeof(solution));
    
    for (int i = 0; i < ChannelCount; i++) {
        
#ifdef DEBUG_LOGFILES
        
        if (!QDir::current().exists("logs")) {
            QDir::current().mkdir("logs");
        }
        
        frsa[i].setFileName(QString("logs/%1rsa.txt").arg(i));
        frsa[i].open(QFile::WriteOnly | QFile::Text);
        srsa[i].setDevice(&frsa[i]);
        
        frha[i].setFileName(QString("logs/%1rha.txt").arg(i));
        frha[i].open(QFile::WriteOnly | QFile::Text);
        srha[i].setDevice(&frha[i]);
        
        ffsa[i].setFileName(QString("logs/%1fsa.txt").arg(i));
        ffsa[i].open(QFile::WriteOnly | QFile::Text);
        sfsa[i].setDevice(&ffsa[i]);
        
        ffha[i].setFileName(QString("logs/%1fha.txt").arg(i));
        ffha[i].open(QFile::WriteOnly | QFile::Text);
        sfha[i].setDevice(&ffha[i]);
        
        fisa[i].setFileName(QString("logs/%1isa.txt").arg(i));
        fisa[i].open(QFile::WriteOnly | QFile::Text);
        sisa[i].setDevice(&fisa[i]);
        
        fiha[i].setFileName(QString("logs/%1iha.txt").arg(i));
        fiha[i].open(QFile::WriteOnly | QFile::Text);
        siha[i].setDevice(&fiha[i]);
#endif        
        locked[i] = false;
        states[i] = 0;
        snr[i] = 0.0;
        time[i] = 0;
        id[i] = 0;
        date[i] = 0;
        infline[i] = 0;
    }
    
#ifdef DEBUG_LOGFILES
    fsol.setFileName("logs/sol.txt");
    fsol.open(QFile::WriteOnly | QFile::Text);
    ssol.setDevice(&fsol);
#endif
    
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}

EthInterface::~EthInterface() {

#ifdef DEBUG_LOGFILES
    for (int i = 0; i < ChannelCount; i++) {
        frsa[i].close();
        frha[i].close();
        ffsa[i].close();
        ffha[i].close();
        fisa[i].close();
        fiha[i].close();
    }
    fsol.close();
#endif
}

QTcpSocket *EthInterface::getSocket() {
    return tcpSocket;
}

void EthInterface::findFreeChannels() {
    freeChannelsCount = 0;
    for (int i = 0; i < ChannelCount; i++) {
        if ((states[i] & 3) != 3) {
            freeChannels[freeChannelsCount] = i;
            freeChannelsCount++;
        }
    }
}

int EthInterface::getFreeChannel(int id) {
    int channel = -1;
    
    for (int i = 0; i < ChannelCount; i++) {
        if ((this->id[i] == id) && ((states[i] & 3) == 3)) {
            channel = -2;
            break;
        }
    }
    
    if (channel == -1) {
        for (int i = 0; i < freeChannelsCount; i++) {
            if ((freeChannels[i] < ChannelCount) && (freeChannels[i] >= 0) && (this->id[freeChannels[i]] == id)) {
                channel = freeChannels[i];
                freeChannels[i] = -1;
                break;
            }
        }

        if (channel == -1) {
            for (int i = 0; i < ChannelCount; i++) {
                if ((freeChannels[i] < ChannelCount) && (freeChannels[i] >= 0)) {
                    channel = freeChannels[i];
                    freeChannels[i] = -1;
                    break;
                }
            }
        }
    }
    
    return channel;
}


bool EthInterface::isLocked(int channel) {
    return locked[channel];
}

int EthInterface::getId(int channel) {
    return id[channel];
}

int EthInterface::getState(int channel) {
    return states[channel] & 0x7;
}

int EthInterface::getIdState(int id) {
    int result = 0;
    for (int i = 0; i < ChannelCount; i++) {
        if (this->id[i] == id) {
            result = states[i] & 0x7;
        }
    }
    return result;
}

float EthInterface::getSnr(int channel) {
    return snr[channel];
}

int EthInterface::getTime() {
    for (int i = 0; i < ChannelCount; i++) {
        if (states[i] == 7) {
            for (int j = i + 1; j < ChannelCount; j++) {
                if ((states[j] == 7) && (time[i] == time[j])) {
                    return time[i];
                }
            }
        }
    }
    return -1;
}

time_t EthInterface::getDate() {
    for (int i = 0; i < ChannelCount; i++) {
        if (states[i] == 7) {
            for (int j = i + 1; j < ChannelCount; j++) {
                if ((states[j] == 7) && (date[i] == date[j])) {
                    return date[i];
                }
            }
        }
    }
    return -1;
}

bool EthInterface::isBadChannel(int channel) {
    infline[channel] = ((states[channel] == 7) || (infline[channel] >= 12)) ? 0 : infline[channel] + 1;
    return (infline[channel] == 12);
}

bool EthInterface::solutionIsValid() {
    int c = 0;
    for (int i = 0; i < ChannelCount; i++) {
        if (states[i] == 7) {
            c++;
        }
    }
    return ((sol.is_valid > 0) && (c >= settings.slv_count));
}

bool EthInterface::exchange() {
    static int value;
    bool result = false;
    if (value != packetCounter) {
        result = true;
        value = packetCounter;
    }
    return result;
}


void EthInterface::clear() {

#ifdef DEBUG_LOGFILES
    for (int i = 0; i < ChannelCount; i++) {
        frsa[i].resize(0);
        frha[i].resize(0);
        ffsa[i].resize(0);
        ffha[i].resize(0);
        fisa[i].resize(0);
        fiha[i].resize(0);
    }
    fsol.resize(0);
#endif
    
}

void EthInterface::readyReadSlot() {

    if (ds->status() != QDataStream::Ok) {
        ds->resetStatus();
    }
    
    quint32 value;
    
    while (!tcpSocket->atEnd() && (tcpSocket->bytesAvailable() >= 4)) {
        (*ds) >> value;
        
        bool is_packet = acceptData(value);
        
        if (is_packet) {
            execCommand();
        }
        
    }
}

void EthInterface::execCommand() {
    
    loop_prs *lprs = (loop_prs *)&buffer[2];
    loop_car *lcar = (loop_car *)&buffer[2];
    info     *inf  = (info     *)&buffer[2];
    solution *slv  = (solution *)&buffer[2];
    rx_settings *set  = (rx_settings *)&buffer[2];

#ifdef DEBUG_LOGFILES
    static int iprssa[ChannelCount];
    static int iprsha[ChannelCount];
    static int icarsa[ChannelCount];
    static int icarha[ChannelCount];
#endif
    
    switch (buffer[1]) {
        case CmdAddrLprsSa: 
            if (lprs->id < ChannelCount && lprs->id >= 0) {

#ifdef DEBUG_LOGFILES
                if (iprssa[lprs->id] != lprs->index) {
                    iprssa[lprs->id] = lprs->index;
                    srsa[lprs->id] 
                            << lprs->number << "\t" << lprs->index    << "\t" 
//                            << QString::number(lprs->sat[0], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[1], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[2], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[3], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[4], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[5], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[6], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[7], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[8], 'g', 12) << "\t" 
//                            << QString::number(lprs->sat[9], 'g', 12) << "\t" 
                            << QString::number(lprs->range , 'g', 12) << "\n";
                    srsa[lprs->id].flush();
                }
#endif
                
                id[lprs->id] = lprs->number;
                locked[lprs->id] = (bool)lprs->locked;
                states[lprs->id] = lprs->locked ? states[lprs->id] | 0x01 : states[lprs->id] & 0xFE;
                time[lprs->id] = lprs->index + timeOffset;
                
//                if (states[lprs->id] == 0x7) {
//                    timeSender->setTime(time[lprs->id]);
//                }
                int t = getTime();
                if (t > 0) {
                    timeSender->setTime(t);
                }
            }
            break;
        case CmdAddrLprsHa: 
            
#ifdef DEBUG_LOGFILES
            if (lprs->id < ChannelCount && lprs->id >= 0 && iprsha[lprs->id] != lprs->index) {
                iprsha[lprs->id] = lprs->index;
                srha[lprs->id] << iprsha[lprs->id] << '\t' << QString::number(lprs->range, 'g', 12) << '\n';
                srha[lprs->id].flush();
            }
#endif
            break;
        case CmdAddrLcarSa:
            if (lcar->id < ChannelCount && lcar->id >= 0) {

#ifdef DEBUG_LOGFILES
                if (icarsa[lcar->id] != lcar->index) {
                    icarsa[lcar->id] = lcar->index;
                    sfsa[lcar->id] << icarsa[lcar->id] << '\t' << QString::number((qulonglong)lcar->phase) << '\n';
                    sfsa[lcar->id].flush();
                }
#endif
                states[lcar->id] = lcar->locked ? states[lcar->id] | 0x02 : states[lcar->id] & 0xFD;
                snr[lcar->id] = lcar->snr < 1.0 ? 0.0 : 10.0 * log10f(lcar->snr * 500.0);
            }
            break;
        case CmdAddrLcarHa: 
#ifdef DEBUG_LOGFILES
            if (lcar->id < ChannelCount && lcar->id >= 0 && icarha[lcar->id] != lcar->index) {
                icarha[lcar->id] = lcar->index;
                sfha[lcar->id] << icarha[lcar->id] << '\t' << QString::number((qulonglong)lcar->phase) << '\n';
                sfha[lcar->id].flush();
            }
#endif
            break;
        case CmdAddrInfoSa:
            if (inf->id < ChannelCount && inf->id >= 0) {
#ifdef DEBUG_LOGFILES
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[0], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[1], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[2], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[3], 8, 16, QChar('0'));
                sisa[inf->id] << QString("// %1:\n" ).arg((uint)(inf->inf[0] >> 27), 2, 10, QChar(' '));
                sisa[inf->id].flush();
#endif
                states[inf->id] = inf->locked ? states[inf->id] | 0x04 : states[inf->id] & 0xFB;
                date[inf->id] = inf->date;
//                infline[inf->id] = (inf->inf[0] >> 27) & 0x1F;
            }
            break;
        case CmdAddrInfoHa:
#ifdef DEBUG_LOGFILES
            if (inf->id < ChannelCount && inf->id >= 0) {
                siha[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[0], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,\n"  ).arg((uint)inf->inf[1], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[2], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,\n"  ).arg((uint)inf->inf[3], 8, 16, QChar('0'));
                siha[inf->id].flush();
            }
#endif
            break;
        case CmdAddrFrame:
            acceptFrame();
            break;
        case CmdAddrSlv:
            memcpy(&sol, slv, sizeof(solution));
//            if (slv->count > 0 && slv->count <= ChannelCount) {
//                puts("");
//                printf("%d\t%f\t%12.4lf\n", slv->count, slv->err, slv->dt * 1000);
//                solution_valid = (slv->is_valid > 0);
//                for (int i = 0; i < slv->count; i++) {
//                    printf("%12.4lf\t%12.4lf\t%12.4lf\t%12.4lf\t%12e\n",
//                            slv->rng[i], 
//                            slv->sat[i * 4 + 0], slv->sat[i * 4 + 1], 
//                            slv->sat[i * 4 + 2], slv->sat[i * 4 + 3]
//                        );
//                }
//            }
#ifdef DEBUG_LOGFILES
            if (slv->is_valid > 0) {
                ssol << slv->count << '\t' << slv->is_valid << '\t' << slv->iter << '\t' <<
                        QString::number(slv->err, 'g', 12) << '\t' <<
                        QString::number(slv->distance, 'g', 12) << '\t' <<
                        QString::number(slv->dt , 'g', 12) << '\t' <<
                        QString::number(slv->loc[0] , 'g', 12) << '\t' <<
                        QString::number(slv->loc[1] , 'g', 12) << '\t' <<
                        QString::number(slv->loc[2] , 'g', 12) << '\n';
                ssol.flush();
            }
#endif
            setSolution(slv->loc[0], slv->loc[1], slv->loc[2], slv->dt);
            break;
        case CmdAddrSettings:
            memcpy(&settings, set, sizeof(rx_settings));
            break;
        default: 
//            printf("default\n");
            break;
    }
    if (buffer[1] >= CmdAddrPlot) {
        acceptPlot();
    }
    
}
void EthInterface::setSolution(double x, double y, double z, double t) {
    xyzt[0] = x;
    xyzt[1] = y;
    xyzt[2] = z;
    xyzt[3] = t;
    xyz2lla(xyzt, lla);
//    uint64_t *data = (uint64_t *)lla;
//    printf("solve: %8.4llf %8.4llf %8.4llf\n", xyzt[0], xyzt[1], xyzt[2]);
//    printf("solve: %8.4llf %8.4llf %8.4llf\n", lla[0] * 180.0 / M_PI, lla[1] * 180.0 / M_PI, lla[2]);
//    fflush(stdout);
}

double EthInterface::getTimeError() {
    return xyzt[3];
}

double *EthInterface::getLla() {
    return lla;
}

int EthInterface::getGain() {
    return settings.gain;
}

float EthInterface::getPower() {
    return settings.power;
}

int EthInterface::getSlvCount() {
    return settings.slv_count;
}

void EthInterface::xyz2lla(double *xyz, double *lla) {
  	double p, T, sT, cT, N;
//	double const wz = 7.2921151467e-5;
	double const a_axis = 6378137.0;   //WGS-84 earth's semi major axis
	double const b_axis = 6356752.31;  //WGS-84 earth's semi minor axis
	//first  numerical eccentricity
	double const e1sqr = ((a_axis * a_axis - b_axis * b_axis) / (a_axis * a_axis));
	//second numerical eccentricity
	double const e2sqr = ((a_axis * a_axis - b_axis * b_axis) / (b_axis * b_axis));

  	p = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]);
  	T = atan(xyz[2] * a_axis / (p * b_axis));
  	sT = sin(T);
  	cT = cos(T);
  	lla[0] = atan((xyz[2] + e2sqr * b_axis * sT * sT * sT) / (p - e1sqr * a_axis * cT * cT * cT));
  	if (xyz[0] == 0.0)
    		lla[1] = M_PI / 2.0;
  	else
    		lla[1] = atan(xyz[1] / xyz[0]);

  	if (xyz[0] < 0 && xyz[1] > 0) lla[1] += M_PI;
    if (xyz[0] < 0 && xyz[1] < 0) lla[1] -= M_PI;

//    blh[1] += -wz * t * 60 - gsto;
//    blh[1] = fmod(blh[1] + 3 * M_PI, twopi) - M_PI;
//    if (blh[1] < -M_PI) blh[1] += 2 * M_PI;

    N = a_axis / sqrt(1.0 - e1sqr * sin(lla[0]) * sin(lla[0]));
  	lla[2] = p / cos(lla[0]) - N;
}

void EthInterface::sendData(const uint32_t value, int32_t *index) {

    if (ds->status() != QDataStream::Ok) {
        ds->resetStatus();
    }
    
    if (value == Seop) {
        (*ds) << Rseop0;
        (*ds) << Rseop1;
        (*index) += 2;
    }
    else {
        if (value == Rseop0) {
            (*ds) << Rseop0;
            (*ds) << Rseop2;
            (*index) += 2;
        }
        else {
            (*ds) << value;
            (*index)++;
        }
    }
    
}

void EthInterface::sendPacket(uint32_t *data, int dlen) {
    int32_t index = 2;
    uint32_t cs = crc(data, 0, dlen);
    
    if (ds->status() != QDataStream::Ok) {
        ds->resetStatus();
    }
    
    (*ds) << Seop;

    for (int i = 0; i < dlen; i++) {
        sendData(data[i], &index);
    }

    sendData(cs, &index);
    
    (*ds) << Seop;
    
    index = (4 - (index % 4)) % 4;
    
    while (index--) {
        (*ds) << Seop;
    }
//    tcpSocket->write(block);
}

void EthInterface::acceptPlot() {
    int p = (int)buffer[1] - CmdAddrPlot;
    float *data = (float *)&buffer[2];
    p *= PlotSamplesInPacket;

    if (p + PlotSamplesInPacket <= PlotLength) {
        for (int i = 0; i < PlotSamplesInPacket; ++i) {
            plot[0][p + i] = data[2 * i];
            plot[1][p + i] = data[2 * i + 1];
        }
    }
    
    if (buffer[1] - CmdAddrPlot + 1 == PlotPacketCount) {
        emit readyPlot(plot);
    }
}

void EthInterface::acceptFrame() {
    gloinf_frame *frame = (gloinf_frame *)&buffer[2];
    gloinf_print(frame);
}

bool EthInterface::acceptData(uint32_t value) {
    bool rdy = false;
    static bool rs;
    static int pos;
    
    if (value == Seop) {
        rs = false;
        if ((pos > 1) && (crc(buffer, 0, pos - 1) == buffer[pos - 1])) {
            rdy = true;
            packetCounter++;
        }
        else {
            if (pos > 1) {
                packetErrorCounter++;
                printf("bad cs: pos %d\n", pos);
                printf("0x%08X != 0x%08X\n", crc(buffer, 0, pos - 1), buffer[pos - 1]);
                for (int i = 0; i < pos; ++i) {
                    printf("0x%08X ", buffer[i]);
                }
                printf("\n");
            }
        }
        pos = 0;
    }
    else {
        if (value == Rseop0) {
            rs = true;
        }
        else {
            buffer[pos] = rs ? (value ^ Seopxor) : value;
            pos++;
            pos &= BufferMask;
            rs = false;
        }
    }
    fflush(stdout);
    return rdy;
}

uint32_t EthInterface::crc(uint32_t *data, int from, int len) {
    uint32_t cs = 0xFFFFFFFF;

    for (int i = from; i < from + len; i++) {
        cs ^= data[i];
    }

    return cs;
}

void EthInterface::setSlvCount(int32_t value) {
    command cmd;
    
    if (tcpSocket->isOpen() && (tcpSocket->state() == QTcpSocket::ConnectedState) && tcpSocket->isValid() && tcpSocket->isWritable()) {
        cmd.cmd  = CmdWrite;
        cmd.length = sizeof(uint32_t) / sizeof(uint32_t);

        cmd.addr = CmdAddrSettings;
        cmd.value = (uint32_t)value;
        cmd.offset = offsetof(rx_settings, slv_count) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
    }
}

void EthInterface::setGain(int32_t value) {
    command cmd;
    
    if (tcpSocket->isOpen() && (tcpSocket->state() == QTcpSocket::ConnectedState) && tcpSocket->isValid() && tcpSocket->isWritable()) {
        
        cmd.cmd  = CmdWrite;
        cmd.length = sizeof(uint32_t) / sizeof(uint32_t);

        cmd.addr = CmdAddrVga;
        cmd.value = (uint32_t)(value & 0xFF);
        cmd.offset = 0;
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
    }
}

void EthInterface::setChannel(uint32_t channel, uint32_t id, uint32_t carrier) {
    command cmd;
    
    if (tcpSocket->isOpen() && tcpSocket->state() == QTcpSocket::ConnectedState && tcpSocket->isValid() && tcpSocket->isWritable()) {
        cmd.cmd  = CmdWrite;
        cmd.length = sizeof(uint32_t) / sizeof(uint32_t);

        cmd.addr = (CmdAddrLprsSa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = id;
        cmd.offset = offsetof(loop_prs, number) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(loop_prs, error) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (CmdAddrLprsHa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = id;
        cmd.offset = offsetof(loop_prs, number) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(loop_prs, error) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (CmdAddrLcarSa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = carrier;
        cmd.offset = offsetof(loop_car, code) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(loop_car, error) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (CmdAddrLcarHa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = carrier;
        cmd.offset = offsetof(loop_car, code) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(loop_car, error) / sizeof(uint32_t);
        sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
    }
}
