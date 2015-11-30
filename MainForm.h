/* 
 * File:   MainForm.h
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:56
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include <QSystemTrayIcon>
#include <QDebug>
#include "ui_MainForm.h"
#include "EthlInterface.h"
#include "PlotForm.h"
#include "IoForm.h"
#include "QLed.h"
#include "PanelRadar.h"
#include "PanelDiagram.h"
#include "PanelWorld.h"
#include "PanelInfo.h"
#include <QMenu>

class MainForm : public QMainWindow {
    Q_OBJECT
public:
    MainForm();
    virtual ~MainForm();
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    
private:
    static const int IoFormCount = 18;
    static const int ChannelCount = 8;
    static const int RadarChannelCount = 24;
    
    static const int DefaultSettingTimeOffset = 1;
    static const int DefaultSettingSlvCount = 5;

    static const quint16 DefaultSettingPort = 5001;
    static const quint16 DefaultSettingUdpPort = 14003;

    static const float  DefaultSettingMaxPower = 75.0;
    static const float  DefaultSettingMinPower = 65.0;
    
    static const double DefaultSettingLat = 55.75;
    static const double DefaultSettingLon = 37.72;
    static const double DefaultSettingAlt = 150.0;

    static const QString DefaultSettingIp;
    static const QString DefaultSettingAgl;
    
    int settingTimeOffset;
    int settingSlvCount;
    quint16 settingPort;
    quint16 settingUdpPort;
    
    float settingMaxPower;
    float settingMinPower;
    
    double settingLat;
    double settingLon;
    double settingAlt;
    
    QString settingIp;
    QString settingAgl;
    
    int timerIdFast;
    int timerIdSlow;
    int32_t gaincode;
    int image_index;
    
    IoForm *ioForm[IoFormCount];
    Ui::MainForm widget;
    EthInterface *com;
    PlotForm plotForm;
    QLed *leds[IoFormCount];
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *showAction;
    QAction *hideAction;
    QAction *quitAction;
    QAction *debugAction;
    QLabel *labelInfo;
    PanelRadar *widgetRadar;
    PanelDiagram *widgetDiagram;
    PanelWorld *widgetWorld;
    PanelInfo *widgetInfo;
    
    void timerEvent(QTimerEvent * event);
    void createActions();
    void createTrayIcon();
    void readSettings();
    void setChannel(uint32_t channel, uint32_t id, uint32_t carrier);
    void setGain(int32_t value);
    void saveScreen();
    float gain2db(int value);
private slots:
    void open();
    void clearLogs();
    void plot();
    void readyPlotSlot(float **plot);
    void setSatelliteIndex();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showDebug();
};

#endif	/* _MAINFORM_H */
