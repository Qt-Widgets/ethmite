/*
 * File:   MainForm.cpp
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:56
 */

#include "MainForm.h"
#include "stdio.h"
#include "Satellite.h"
#include "time.h"
#include "QLed.h"

MainForm::MainForm() {
    widget.setupUi(this);

    ioForm[0] = new IoForm(&com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, level), 
            IoForm::FLOAT, 
            "Level"
        );
    
    ioForm[1] = new IoForm(&com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, offset), 
            IoForm::UINT32, 
            "Offset"
        );
    
    ioForm[2] = new IoForm(&com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, code), 
            IoForm::INT32, 
            "Carrier"
        );
    
    ioForm[3] = new IoForm(&com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, k[0]), 
            IoForm::FLOAT, 
            "DLL K0"
        );
    
    ioForm[4] = new IoForm(&com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, k[1]), 
            IoForm::FLOAT, 
            "DLL K1"
        );

    ioForm[5] = new IoForm(&com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, k[0]), 
            IoForm::FLOAT, 
            "PLL K0"
        );
    
    ioForm[6] = new IoForm(&com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, k[1]), 
            IoForm::FLOAT, 
            "PLL K1"
        );

    ioForm[7] = new IoForm(&com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, level), 
            IoForm::FLOAT, 
            "Level"
        );
    
    ioForm[8] = new IoForm(&com, EthInterface::CmdAddrLcarHa, 
            offsetof(EthInterface::loop_car, code), 
            IoForm::INT32, 
            "Carrier"
        );
   
    ioForm[9] = new IoForm(&com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, offset), 
            IoForm::UINT32, 
            "Offset"
        );
   
    ioForm[10] = new IoForm(&com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, k[0]), 
            IoForm::FLOAT, 
            "DLL K0"
        );
    
    ioForm[11] = new IoForm(&com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, k[1]), 
            IoForm::FLOAT, 
            "DLL K1"
        );

    ioForm[15] = new IoForm(&com, EthInterface::CmdAddrControl, 
            offsetof(EthInterface::state_ifc, buf_param), 
            IoForm::UINT8, 
            "Parameter"
        );
   
    ioForm[16] = new IoForm(&com, EthInterface::CmdAddrControl, 
            offsetof(EthInterface::state_ifc, buf_channel), 
            IoForm::UINT32, 
            "Channel"
        );
   
    ioForm[17] = new IoForm(&com, EthInterface::CmdAddrVga, 
            0, 
            IoForm::UINT32, 
            "VGA"
        );
   
    QLayout *layout = new QVBoxLayout();
    layout->addWidget(ioForm[0]);
    layout->addWidget(ioForm[1]);
    layout->addWidget(ioForm[2]);
    layout->addWidget(ioForm[3]);
    layout->addWidget(ioForm[4]);
    layout->addWidget(ioForm[5]);
    layout->addWidget(ioForm[6]);
    layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    widget.widgetIoSa->setLayout(layout);
    
    QLayout *layoutHa = new QVBoxLayout();
    layoutHa->addWidget(ioForm[7]);
    layoutHa->addWidget(ioForm[8]);
    layoutHa->addWidget(ioForm[9]);
    layoutHa->addWidget(ioForm[10]);
    layoutHa->addWidget(ioForm[11]);
    layoutHa->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    widget.widgetIoHa->setLayout(layoutHa);

    QLayout *layoutState = new QVBoxLayout();
    layoutState->addWidget(ioForm[15]);
    layoutState->addWidget(ioForm[16]);
    layoutState->addWidget(ioForm[17]);
    layoutState->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    widget.widgetIoState->setLayout(layoutState);
    
    QGridLayout *layoutSatState = new QGridLayout();
    
    for (int i = 0; i < ChannelCount; i++) {
        leds[i] = new QLed();
        layoutSatState->addWidget(leds[i], i / 4, i % 4);
    }
    
    for (int i = 0; i < RadarChannelCount; i++) {
        setRadarItem(i, 0.0, -1.0);
    }
    
    setWorldLocation(44.98 * M_PI / 180.0, 41.12 * M_PI / 180.0);
    widget.gbState->setLayout(layoutSatState);

    connect(widget.btnOpen, SIGNAL(clicked()), this, SLOT(open()));
    connect(widget.btnPlot, SIGNAL(clicked()), this, SLOT(plot()));
    connect(widget.btnSend, SIGNAL(clicked()), this, SLOT(setSatelliteIndex()));
    connect(&com, SIGNAL(readyPlot(float **)), this, SLOT(readyPlotSlot(float **)));

    startTimer(200);

}

void MainForm::timerEvent(QTimerEvent * event) {
    for (int i = 0; i < ChannelCount; i++) {
        QColor c = com.isLocked(i) ? Qt::green : Qt::yellow;
        leds[i]->setState(c);
        setChannelState(i, (quint32)com.getStates(i), i, com.getSnr(i) * 0.02);
    }
    
    setWorldSolution(com.getLla()[0], com.getLla()[1], com.getLla()[2], true);
    
    setTime(com.getTime(0));
}

void MainForm::setChannelState(qint32 index, qint32 state, qint32 label, qreal value) {
    QObject *obj = (QObject *)widget.quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "setChannelState", 
            Q_ARG(QVariant, index), 
            Q_ARG(QVariant, state), 
            Q_ARG(QVariant, label), 
            Q_ARG(QVariant, value)
    );
}

void MainForm::setRadarItem(qint32 index, qreal azm, qreal elv) {
    QObject *obj = (QObject *)widget.quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "setRadarItem", 
            Q_ARG(QVariant, index), 
            Q_ARG(QVariant, azm), 
            Q_ARG(QVariant, elv) 
    );
}

void MainForm::setWorldLocation(qreal lat, qreal lon) {
    QObject *obj = (QObject *)widget.quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "setWorldLocation", 
            Q_ARG(QVariant, lat), 
            Q_ARG(QVariant, lon) 
    );
}
    
void MainForm::setWorldSolution(qreal lat, qreal lon, qreal alt, boolean isVisible) {
    QObject *obj = (QObject *)widget.quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "setWorldSolution", 
            Q_ARG(QVariant, lat), 
            Q_ARG(QVariant, lon), 
            Q_ARG(QVariant, alt), 
            Q_ARG(QVariant, isVisible) 
    );
}

void MainForm::setTime(qint32 value) {
    QObject *obj = (QObject *)widget.quickWidget->rootObject();
    QMetaObject::invokeMethod(obj, "setTime", 
            Q_ARG(QVariant, value) 
    );
}

MainForm::~MainForm() {
}

void MainForm::open() {
    switch (com.state()) {
        case QTcpSocket::ConnectedState     :
            com.close();
            widget.teLog->appendPlainText(QString("Disconnecting"));
            break;
        case QTcpSocket::UnconnectedState   :
            com.connectToHost("192.168.1.70", 5001);
            widget.teLog->appendPlainText(QString("Connecting"));
            com.clear();
            break;
        default:
            widget.teLog->appendPlainText(QString("Socket state: %1").arg(com.state()));
            break;
    }
}

void MainForm::plot() {
    plotForm.show();
}

void MainForm::readyPlotSlot(float **plot) {
    plotForm.setData(plot, 512);
}

void MainForm::setSatelliteIndex() {
    int c = 0;
//    int index = widget.sbSatelliteIndex->value() - 1;
    Satellite sat;
    sat.loadAgl("d:/tmp/agl/MCCT_150922.agl");
    
    for (int i = 0; i < RadarChannelCount; i++) {
        sat.setTime(time(0), i);
        
        setRadarItem(i, sat.getAerv()[0], sat.getAerv()[1]);
        
        if ((sat.getAerv()[1] * 180 / M_PI > 15) && (c < com.ChannelCount)) {
            double f = sat.getFrequencyL1Current(i);
            f -= 1580000000.0;
            f = f * 4294967296.0 / 100000000.0;
            ioForm[2]->getLineEdit()->setText(QString::number((int)f));
            ioForm[2]->setChannel(c);
            ioForm[2]->set();

            ioForm[8]->getLineEdit()->setText(QString::number((int)f));
            ioForm[8]->setChannel(c);
            ioForm[8]->set();

            printf("[%d - %d]\n", i + 1, c);
            c++;
        }
    }

//    for (int c = 0; c < com.ChannelCount; c++) {
//        sat.setTime(time(0), 22);
//
//        double f = sat.getFrequencyL1Current(22);
//        f -= 1580000000.0;
//        f = f * 4294967296.0 / 100000000.0;
//        ioForm[2]->getLineEdit()->setText(QString::number((int)f));
//        ioForm[2]->setChannel(c);
//        ioForm[2]->set();
//
//        ioForm[8]->getLineEdit()->setText(QString::number((int)f));
//        ioForm[8]->setChannel(c);
//        ioForm[8]->set();
//
//        printf("[%d - %d]\n", 22 + 1, c);
//    }
}

