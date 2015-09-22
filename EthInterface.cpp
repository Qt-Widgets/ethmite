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

EthInterface::EthInterface() {
    plot[0] = new float[PlotLength];
    plot[1] = new float[PlotLength];
    for (int i = 0; i < ChannelCount; i++) {
        frsa[i].setFileName(QString("%1/rsa.txt").arg(i));
        frsa[i].open(QFile::WriteOnly | QFile::Text);
        srsa[i].setDevice(&frsa[i]);
        
        frha[i].setFileName(QString("%1/rha.txt").arg(i));
        frha[i].open(QFile::WriteOnly | QFile::Text);
        srha[i].setDevice(&frha[i]);
        
        ffsa[i].setFileName(QString("%1/fsa.txt").arg(i));
        ffsa[i].open(QFile::WriteOnly | QFile::Text);
        sfsa[i].setDevice(&ffsa[i]);
        
        ffha[i].setFileName(QString("%1/fha.txt").arg(i));
        ffha[i].open(QFile::WriteOnly | QFile::Text);
        sfha[i].setDevice(&ffha[i]);
        
        fisa[i].setFileName(QString("%1/isa.txt").arg(i));
        fisa[i].open(QFile::WriteOnly | QFile::Text);
        sisa[i].setDevice(&fisa[i]);
        
        fiha[i].setFileName(QString("%1/iha.txt").arg(i));
        fiha[i].open(QFile::WriteOnly | QFile::Text);
        siha[i].setDevice(&fiha[i]);
        
        locked[i] = false;
        states[i] = 0;
        snr[i] = 0.0;
        time[i] = 0;
    }
    
    fsol.setFileName("sol.txt");
    fsol.open(QFile::WriteOnly | QFile::Text);
    ssol.setDevice(&fsol);
    
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}

EthInterface::~EthInterface() {
    for (int i = 0; i < ChannelCount; i++) {
        frsa[i].close();
        frha[i].close();
        ffsa[i].close();
        ffha[i].close();
        fisa[i].close();
        fiha[i].close();
    }
    fsol.close();
}

bool EthInterface::isLocked(int channel) {
    return locked[channel];
}

int EthInterface::getStates(int channel) {
    return states[channel];
}

float EthInterface::getSnr(int channel) {
    return snr[channel];
}

int EthInterface::getTime(int channel) {
    return time[channel];
}

void EthInterface::clear() {
    for (int i = 0; i < ChannelCount; i++) {
        frsa[i].resize(0);
        frha[i].resize(0);
        ffsa[i].resize(0);
        ffha[i].resize(0);
        fisa[i].resize(0);
        fiha[i].resize(0);
    }
    fsol.resize(0);
}

void EthInterface::readyReadSlot() {
    QDataStream ds(this);
//    ds.setByteOrder(QDataStream::BigEndian);
    quint32 value;
    
    while (!atEnd() && (bytesAvailable() >= 4)) {
        ds >> value;
        
        bool is_packet = acceptData(value);
//        printf("0x%08X ", value);
        
        if (is_packet) {
//            printf("packet 0x%08X : 0x%08X\n", buffer[0], buffer[1]);
            fflush(stdout);
            execCommand();
        }
        
    }
}

void EthInterface::execCommand() {
    
    loop_prs *lprs = (loop_prs *)&buffer[2];
    loop_car *lcar = (loop_car *)&buffer[2];
    info     *inf  = (info     *)&buffer[2];
    solution *slv  = (solution *)&buffer[2];
//    int16_t *data = (int16_t *)&buffer[2];

    static int iprssa[ChannelCount];
    static int iprsha[ChannelCount];
    static int icarsa[ChannelCount];
    static int icarha[ChannelCount];
    
    switch (buffer[1]) {
        case CmdAddrLprsSa: 
            if (lprs->id < ChannelCount && lprs->id >= 0 && iprssa[lprs->id] != lprs->index) {
                iprssa[lprs->id] = lprs->index;
                srsa[lprs->id] 
                        << lprs->index << '\t' 
                        << QString::number(lprs->sat[0], 'g', 12) << '\t' 
                        << QString::number(lprs->sat[1], 'g', 12) << '\t' 
                        << QString::number(lprs->sat[2], 'g', 12) << '\t' 
                        << QString::number(lprs->prediction, 'g', 12) << '\t' 
                        << QString::number(lprs->range, 'g', 12) << '\n';
                srsa[lprs->id].flush();
                locked[lprs->id] = (bool)lprs->locked;
                states[lprs->id] = lprs->locked ? states[lprs->id] | 0x01 : states[lprs->id] & 0xFE;
                time[lprs->id] = lprs->index;
            }
            break;
        case CmdAddrLprsHa: 
            if (lprs->id < ChannelCount && lprs->id >= 0 && iprsha[lprs->id] != lprs->index) {
                iprsha[lprs->id] = lprs->index;
                srha[lprs->id] << iprsha[lprs->id] << '\t' << QString::number(lprs->range, 'g', 12) << '\n';
                srha[lprs->id].flush();
            }
            fflush(stdout);
            break;
        case CmdAddrLcarSa: 
            if (lcar->id < ChannelCount && lcar->id >= 0 && icarsa[lcar->id] != lcar->index) {
                icarsa[lcar->id] = lcar->index;
                sfsa[lcar->id] << icarsa[lcar->id] << '\t' << QString::number((qulonglong)lcar->phase) << '\n';
                sfsa[lcar->id].flush();
                states[lcar->id] = lcar->locked ? states[lcar->id] | 0x02 : states[lcar->id] & 0xFD;
                snr[lcar->id] = lcar->snr < 1.0 ? 0.0 : 10.0 * log10f(lcar->snr * 500.0);
            }
            break;
        case CmdAddrLcarHa: 
            if (lcar->id < ChannelCount && lcar->id >= 0 && icarha[lcar->id] != lcar->index) {
                icarha[lcar->id] = lcar->index;
                sfha[lcar->id] << icarha[lcar->id] << '\t' << QString::number((qulonglong)lcar->phase) << '\n';
                sfha[lcar->id].flush();
            }
            break;
        case CmdAddrInfoSa:
            if (inf->id < ChannelCount && inf->id >= 0) {
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[0], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[1], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[2], 8, 16, QChar('0'));
                sisa[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[3], 8, 16, QChar('0'));
                sisa[inf->id] << QString("// %1:\n" ).arg((uint)(inf->inf[0] >> 27), 2, 10, QChar(' '));
                sisa[inf->id].flush();
            }
            break;
        case CmdAddrInfoHa:
            if (inf->id < ChannelCount && inf->id >= 0) {
                siha[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[0], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,\n"  ).arg((uint)inf->inf[1], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,    ").arg((uint)inf->inf[2], 8, 16, QChar('0'));
                siha[inf->id] << QString("0x%1,\n"  ).arg((uint)inf->inf[3], 8, 16, QChar('0'));
                siha[inf->id].flush();
            }
            break;
        case CmdAddrSlv:
            printf("%d\t%f\n", slv->count, slv->err);
            printf("%12.4lf\t%12.4lf\t%12.4lf\t%12.4lf\n\n", slv->dt * 1e6, slv->loc[0] / 1000.0, slv->loc[1] / 1000.0, slv->loc[2] / 1000.0);
            for (int i = 0; i < slv->count; i++) {
                printf("%10d\t%12.4f\t%12.4lf\t%12.4lf\t%12.4lf\t%12.4lf\t%12.4lf\t%12g\n", slv->s[i], slv->ms[i], slv->p[i], slv->rng[i], slv->sat[i * 4 + 0], slv->sat[i * 4 + 1], slv->sat[i * 4 + 2], slv->sat[i * 4 + 3]);
            }
            ssol << slv->count << '\t' << slv->s[0] << '\t' <<
                    QString::number(slv->err, 'g', 12) << '\t' <<
                    QString::number(slv->dt , 'g', 12) << '\t' <<
                    QString::number(slv->loc[0] , 'g', 12) << '\t' <<
                    QString::number(slv->loc[1] , 'g', 12) << '\t' <<
                    QString::number(slv->loc[2] , 'g', 12) << '\n';
            ssol.flush();
            break;
//        default: 
//            printf("default\n");
//            break;
    }
    if (buffer[1] >= CmdAddrPlot) {
        acceptPlot();
    }
    
}

void EthInterface::sendData(const uint32_t value, int32_t *index) {
    QDataStream ds(this);
    
    if (value == Seop) {
        ds << Rseop0;
        ds << Rseop1;
        (*index) += 2;
    }
    else {
        if (value == Rseop0) {
            ds << Rseop0;
            ds << Rseop2;
            (*index) += 2;
        }
        else {
            ds << value;
            (*index)++;
        }
    }
    
}

void EthInterface::sendPacket(uint32_t *data, int dlen) {
    int32_t index = 2;
    uint32_t cs = crc(data, 0, dlen);
    QDataStream ds(this);
    
    ds << Seop;

    for (int i = 0; i < dlen; i++) {
        sendData(data[i], &index);
    }

    sendData(cs, &index);
    
    ds << Seop;
    
    index = (4 - (index % 4)) % 4;
    
    while (index--) {
        ds << Seop;
    }
}

void EthInterface::acceptPlot() {
    int p = (int)buffer[1] - CmdAddrPlot;
    float *data = (float *)&buffer[2];
    p *= PlotSamplesInPacket;

    for (int i = 0; i < PlotSamplesInPacket; ++i) {
        plot[0][p + i] = data[2 * i];
        plot[1][p + i] = data[2 * i + 1];
    }
    
    if (buffer[1] - CmdAddrPlot + 1 == PlotPacketCount) {
        emit readyPlot(plot);
    }
}

bool EthInterface::acceptData(uint32_t value) {
    bool rdy = false;
    static bool rs;
    static int pos;
    
    if (value == Seop) {
        rs = false;
        if ((pos > 1) && (crc(buffer, 0, pos - 1) == buffer[pos - 1])) {
            rdy = true;
        }
        else {
            if (pos > 1) {
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
