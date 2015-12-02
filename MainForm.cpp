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
#include <math.h>
#include <time.h>
#include <QDir>

const QString MainForm::DefaultSettingIp = QString("192.168.0.1");
const QString MainForm::DefaultSettingAgl = QString("latest.agl");

MainForm::MainForm() {
    widget.setupUi(this);

    widget.tabWidget->tabBar()->hide();

#ifdef DEBUG_LOGFILES
    if (!QDir::current().exists("img")) {
        QDir::current().mkdir("img");
    }
#endif
    
    image_index = 0;
    
    widgetRadar = new PanelRadar();
    widgetDiagram = new PanelDiagram();
    widgetWorld = new PanelWorld();
    widgetInfo = new PanelInfo();
    
    widget.widgetTop->layout()->addWidget(widgetRadar);
    widget.widgetTop->layout()->addWidget(widgetWorld);
    widget.widgetTop->layout()->addWidget(widgetInfo);
    widget.widgetBottom->layout()->addWidget(widgetDiagram);
    
    labelInfo = new QLabel(widget.statusbar);
    widget.statusbar->addWidget(labelInfo, 1);
    
    readSettings();
    com = new EthInterface(settingTimeOffset, settingUdpPort);
    
    createActions();
    createTrayIcon();
    trayIcon->show();
    
    gaincode = 128;
    
    widgetWorld->setPosition(settingLat, settingLon);
    
    ioForm[0] = new IoForm(com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, level), 
            IoForm::FLOAT, 
            "Level"
        );
    
    ioForm[1] = new IoForm(com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, offset), 
            IoForm::UINT32, 
            "Offset"
        );
    
    ioForm[2] = new IoForm(com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, code), 
            IoForm::INT32, 
            "Carrier"
        );
    
    ioForm[3] = new IoForm(com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, k[0]), 
            IoForm::FLOAT, 
            "DLL K0"
        );
    
    ioForm[4] = new IoForm(com, EthInterface::CmdAddrLprsSa, 
            offsetof(EthInterface::loop_prs, k[1]), 
            IoForm::FLOAT, 
            "DLL K1"
        );

    ioForm[5] = new IoForm(com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, k[0]), 
            IoForm::FLOAT, 
            "PLL K0"
        );
    
    ioForm[6] = new IoForm(com, EthInterface::CmdAddrLcarSa, 
            offsetof(EthInterface::loop_car, k[1]), 
            IoForm::FLOAT, 
            "PLL K1"
        );

    ioForm[7] = new IoForm(com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, level), 
            IoForm::FLOAT, 
            "Level"
        );
    
    ioForm[8] = new IoForm(com, EthInterface::CmdAddrLcarHa, 
            offsetof(EthInterface::loop_car, code), 
            IoForm::INT32, 
            "Carrier"
        );
   
    ioForm[9] = new IoForm(com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, offset), 
            IoForm::UINT32, 
            "Offset"
        );
   
    ioForm[10] = new IoForm(com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, k[0]), 
            IoForm::FLOAT, 
            "DLL K0"
        );
    
    ioForm[11] = new IoForm(com, EthInterface::CmdAddrLprsHa, 
            offsetof(EthInterface::loop_prs, k[1]), 
            IoForm::FLOAT, 
            "DLL K1"
        );

    ioForm[15] = new IoForm(com, EthInterface::CmdAddrControl, 
            offsetof(EthInterface::state_ifc, buf_param), 
            IoForm::UINT8, 
            "Parameter"
        );
   
    ioForm[16] = new IoForm(com, EthInterface::CmdAddrControl, 
            offsetof(EthInterface::state_ifc, buf_channel), 
            IoForm::UINT32, 
            "Channel"
        );
   
    ioForm[17] = new IoForm(com, EthInterface::CmdAddrVga, 
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
        widgetRadar->setRadarItem(i, 0.0, -1.0, 0);
    }
    
    widget.gbState->setLayout(layoutSatState);

    connect(widget.btnOpen, SIGNAL(clicked()), this, SLOT(clearLogs()));
    connect(widget.btnPlot, SIGNAL(clicked()), this, SLOT(plot()));
    connect(widget.btnSend, SIGNAL(clicked()), this, SLOT(setSatelliteIndex()));
    connect(com, SIGNAL(readyPlot(float **)), this, SLOT(readyPlotSlot(float **)));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    timerIdFast = startTimer(200);
    timerIdSlow = startTimer(5000);
}

void MainForm::timerEvent(QTimerEvent * event) {
    QTcpSocket *s = com->getSocket();
    bool solutionIsValid = com->solutionIsValid();

    if (event->timerId() == timerIdFast) {
        for (int i = 0; i < ChannelCount; i++) {
            QColor c = com->isLocked(i) ? Qt::green : Qt::yellow;
            leds[i]->setState(c);
            widgetDiagram->setDiagramItem(i, com->getState(i), com->getId(i), com->getSnr(i) * 0.02);
        }
        
        if (solutionIsValid) {
            widgetInfo->setSolution(com->getLla()[0], com->getLla()[1], com->getLla()[2], com->getTimeError());
        }
        widgetWorld->setSolution(com->getLla()[0], com->getLla()[1], solutionIsValid);
        
        int time = com->getTime();
        if (time > 0) {
            widgetInfo->setTime(time);
        }
        
        int date = com->getDate();
        if (date > 0) {
            widgetInfo->setDate(date);
        }
    }
    
    if (event->timerId() == timerIdSlow) {
        open();
        setSatelliteIndex();
        QString s0 = (s->state() == QTcpSocket::ConnectedState) ? "Да" : "Нет";
        QString s1 = (com->exchange()) ? "Да" : "Нет";
        QString s2 = solutionIsValid ? "Да" : "Нет";
        float pwr = com->getPower();
        pwr = (pwr > 0.0) ? log10f(pwr) * 10.0 : 0.0;
        float db = gain2db(gaincode);
        if (pwr < settingMinPower) {
            gaincode = (gaincode + 5 > 255) ? 255 : gaincode + 5;
            com->setGain(gaincode);
        }
        else {
            if (pwr > settingMaxPower) {
                gaincode = ((gaincode - 5 < 128) ? 128 : gaincode - 5);
                com->setGain(gaincode);
            }
        }
        db = gain2db(com->getGain());
        labelInfo->setText(QString( "Соединение: %1 \tОбмен: %2 \t"
                                    "Антенна: %3 дБ \tУсиление: %4 дБ\t"
                                    "Решение: %5")
            .arg(s0).arg(s1).arg(pwr - db, 0, 'f', 1).arg(db, 0, 'f', 1).arg(s2));
        if (settingSlvCount != com->getSlvCount()) {
            com->setSlvCount(settingSlvCount);
        }
#ifdef DEBUG_LOGFILES
        saveScreen();
#endif
    }
}

MainForm::~MainForm() {
}

void MainForm::open() {
    QTcpSocket *s = com->getSocket();
    
    switch (s->state()) {
        case QTcpSocket::ConnectedState     :
//            com->close();
//            widget.teLog->appendPlainText(QString("Disconnecting"));
            break;
        case QTcpSocket::UnconnectedState   :
            s->connectToHost(settingIp, settingPort);
            widget.teLog->appendPlainText(QString("Connecting to: %1:%2").arg(settingIp).arg(settingPort));
            com->clear();
            break;
        default:
            widget.teLog->appendPlainText(QString("Socket state: %1").arg(s->state()));
            break;
    }
}

void MainForm::clearLogs() {
    com->clear();
    image_index = 0;
}

void MainForm::plot() {
    plotForm.show();
}

void MainForm::readyPlotSlot(float **plot) {
    plotForm.setData(plot, 512);
}

void MainForm::setSatelliteIndex() {
    int c = 0;
    Satellite sat(settingLat, settingLon, settingAlt);
    sat.loadAgl(settingAgl);
    
    if (sat.getCount() > 0) {
        com->findFreeChannels();

        for (int i = 0; i < sat.getCount(); i++) {
            if (sat.isValid(i)) {
                sat.setTime(time(0), i);

                widgetRadar->setRadarItem(i, sat.getAerv()[0], sat.getAerv()[1], com->getIdState(i + 1));

                if (sat.isValid(i) && (sat.getAerv()[1] * 180.0 / M_PI > 15.0)) {
                    double f = sat.getFrequencyL1Current(i);
                    f -= 1575000000.0;
                    f = f * 4294967296.0 / 100000000.0;
                    c = com->getFreeChannel(i + 1);
                    if (c >= 0) {
                        com->setChannel((uint32_t)c, (uint32_t)(i + 1), (uint32_t)f);
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < com->ChannelCount; i++) {
            if (((com->getState(i) & 3) != 3) || com->isBadChannel(i)) {
                double f = sat.FrequencyL1 + sat.FrequencyL1Delta * (i - 3);
                f -= 1575000000.0;
                f = f * 4294967296.0 / 100000000.0;
                com->setChannel((uint32_t)i, (uint32_t)(i + 1), (uint32_t)f);
            }
        }
    }

}

void MainForm::showDebug() {
    if (widget.tabWidget->tabBar()->isVisible()) {
        widget.tabWidget->tabBar()->hide();
    }
    else {
        widget.tabWidget->tabBar()->show();
    }
}

void MainForm::createActions() {
    showAction = new QAction("Показать", this);
    connect(showAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    hideAction = new QAction("Спрятать", this);
    connect(hideAction, SIGNAL(triggered()), this, SLOT(hide()));

    quitAction = new QAction("Закрыть", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    debugAction = new QAction(this);
    debugAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_D));
    connect(debugAction, SIGNAL(triggered()), this, SLOT(showDebug()));
    this->addAction(debugAction);
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

    settingTimeOffset = settings.value("timeOffset", DefaultSettingTimeOffset).toInt();
    settingSlvCount = settings.value("slvCount", DefaultSettingSlvCount).toInt();
    settingUdpPort = (quint16)settings.value("udpPort", DefaultSettingUdpPort).toUInt();
    
    settingMaxPower = settings.value("maxPower", DefaultSettingMaxPower).toFloat();
    settingMinPower = settings.value("minPower", DefaultSettingMinPower).toFloat();
    
    settingLat = settings.value("lat", DefaultSettingLat).toDouble() * M_PI / 180.0;
    settingLon = settings.value("lon", DefaultSettingLon).toDouble() * M_PI / 180.0;
    settingAlt = settings.value("alt", DefaultSettingAlt).toDouble();
    
}

void MainForm::saveScreen() {
    widget.tab->grab().save(QString("img/%1.png").arg(image_index, 8, 10, QChar('0')));
    image_index++;
}

float MainForm::gain2db(int value) {
    float db;
    db = (float)(value & 0x7F) * 0.055744 * (1 + (7.079458 - 1) * (float)((value >> 7) & 0x1));
    db = (db <= 0.0) ? 0 : log10f(db) * 20.0;
    return db;
}
