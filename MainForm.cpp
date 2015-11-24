/*
 * File:   MainForm.cpp
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:56
 */

#include <QSettings>
#include "MainForm.h"
#include "stdio.h"
#include "Satellite.h"
#include "time.h"
#include "QLed.h"

const QString MainForm::DefaultSettingIp = QString("192.168.0.1");
const QString MainForm::DefaultSettingAgl = QString("./almanac/latest.agl");

MainForm::MainForm() {
    widget.setupUi(this);
//    widget.tabWidget->tabBar()->hide();

    labelInfo = new QLabel(widget.statusbar);
    widget.statusbar->addWidget(labelInfo, 1);
    readSettings();
    createActions();
    createTrayIcon();
    trayIcon->show();
    
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

    connect(widget.btnOpen, SIGNAL(clicked()), this, SLOT(clearLogs()));
    connect(widget.btnPlot, SIGNAL(clicked()), this, SLOT(plot()));
    connect(widget.btnSend, SIGNAL(clicked()), this, SLOT(setSatelliteIndex()));
    connect(&com, SIGNAL(readyPlot(float **)), this, SLOT(readyPlotSlot(float **)));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    timerIdFast = startTimer(200);
    timerIdSlow = startTimer(3000);
}

void MainForm::timerEvent(QTimerEvent * event) {
    QTcpSocket *s = com.getSocket();
    
    if (event->timerId() == timerIdFast) {
        for (int i = 0; i < ChannelCount; i++) {
            QColor c = com.isLocked(i) ? Qt::green : Qt::yellow;
            leds[i]->setState(c);
            setChannelState(i, (quint32)com.getStates(i), com.getId(i), com.getSnr(i) * 0.02);
        }
//        int64_t lla[3] = {-1, -1, -1};
//        double *dlla = (double *)lla;
//        setWorldSolution(dlla[0], dlla[1], dlla[2], true);
        setWorldSolution(com.getLla()[0], com.getLla()[1], com.getLla()[2], true);
        for (int i = 0; i < ChannelCount; i++) {
            if (com.getStates(i) == 7) {
                setTime(com.getTime(i));
                break;
            }
        }
    }
    
    if (event->timerId() == timerIdSlow) {
        open();
        setSatelliteIndex();
        QString s1 = (s->state() == QTcpSocket::ConnectedState) ? "Да" : "Нет";
        labelInfo->setText(QString("Соединение: %1 \t Обмен: %2").arg(s1).arg("Да"));
    }
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

    if (lat != lat || lon != lon || lat != lat) {
        return;
    }
    
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
    QTcpSocket *s = com.getSocket();
    
    switch (s->state()) {
        case QTcpSocket::ConnectedState     :
//            com.close();
//            widget.teLog->appendPlainText(QString("Disconnecting"));
            break;
        case QTcpSocket::UnconnectedState   :
            s->connectToHost(settingIp, settingPort);
            widget.teLog->appendPlainText(QString("Connecting to: %1:%2").arg(settingIp).arg(settingPort));
            com.clear();
            break;
        default:
            widget.teLog->appendPlainText(QString("Socket state: %1").arg(s->state()));
            break;
    }
}

void MainForm::clearLogs() {
    com.clear();
}

void MainForm::plot() {
    plotForm.show();
}

void MainForm::readyPlotSlot(float **plot) {
    plotForm.setData(plot, 512);
}

void MainForm::setChannel(uint32_t channel, uint32_t id, uint32_t carrier) {
    EthInterface::command cmd;
    QTcpSocket *s = com.getSocket();
    
    if (s->isOpen() && s->state() == QTcpSocket::ConnectedState && s->isValid() && s->isWritable()) {
        cmd.cmd  = EthInterface::CmdWrite;
        cmd.length = sizeof(uint32_t) / sizeof(uint32_t);

        cmd.addr = (EthInterface::CmdAddrLprsSa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = id;
        cmd.offset = offsetof(EthInterface::loop_prs, number) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(EthInterface::loop_prs, error) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (EthInterface::CmdAddrLprsHa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = id;
        cmd.offset = offsetof(EthInterface::loop_prs, number) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(EthInterface::loop_prs, error) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (EthInterface::CmdAddrLcarSa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = carrier;
        cmd.offset = offsetof(EthInterface::loop_car, code) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(EthInterface::loop_car, error) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));

        cmd.addr = (EthInterface::CmdAddrLcarHa & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
        cmd.value = carrier;
        cmd.offset = offsetof(EthInterface::loop_car, code) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
        cmd.value = 0;
        cmd.offset = offsetof(EthInterface::loop_car, error) / sizeof(uint32_t);
        com.sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
    }
}

void MainForm::setSatelliteIndex() {
    int c = 0;
    Satellite sat;
    sat.loadAgl(settingAgl);
    
    com.findFreeChannels();
    
    for (int i = 0; i < sat.getCount(); i++) {
        if (sat.isValid(i)) {
            sat.setTime(time(0), i);

            setRadarItem(i, sat.getAerv()[0], sat.getAerv()[1]);

            if (sat.isValid(i) && (sat.getAerv()[1] * 180.0 / M_PI > 15.0)) {
                double f = sat.getFrequencyL1Current(i);
                f -= 1575000000.0;
                f = f * 4294967296.0 / 100000000.0;
                c = com.getFreeChannel(i + 1);
                if (c >= 0) {
                    setChannel((uint32_t)c, (uint32_t)(i + 1), (uint32_t)f);
                }
            }
        }
    }

}

void MainForm::createActions() {
    showAction = new QAction(tr("Показать"), this);
    connect(showAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    hideAction = new QAction(tr("Спрятать"), this);
    connect(hideAction, SIGNAL(triggered()), this, SLOT(hide()));

    quitAction = new QAction(tr("Закрыть"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void MainForm::createTrayIcon() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(hideAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/earth.png"));
}

void MainForm::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::MiddleClick:
        if (isVisible()) {
            hideAction->trigger();
        }
        else {
            showAction->trigger();
        }
        break;
    default:
        ;
    }
}
void MainForm::setVisible(bool visible) {
    hideAction->setEnabled(visible);
    showAction->setEnabled(!visible);
    QMainWindow::setVisible(visible);
}

void MainForm::readSettings() {
    QSettings settings("ethmite.ini", QSettings::IniFormat);

    settingIp = settings.value("ip", DefaultSettingIp).toString();
    settingPort = (quint16)settings.value("port", DefaultSettingPort).toUInt();
    settingAgl = settings.value("agl", DefaultSettingAgl).toString();
}

