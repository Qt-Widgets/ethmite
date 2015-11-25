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
    static const quint16 DefaultSettingPort = 5001;
    static const QString DefaultSettingIp;
    static const QString DefaultSettingAgl;

    quint16 settingPort;
    QString settingIp;
    QString settingAgl;
    int timerIdFast;
    int timerIdSlow;
    
    IoForm *ioForm[IoFormCount];
    Ui::MainForm widget;
    EthInterface com;
    PlotForm plotForm;
    QLed *leds[IoFormCount];
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *showAction;
    QAction *hideAction;
    QAction *quitAction;
    QLabel *labelInfo;
    PanelRadar *widgetRadar;
    PanelDiagram *widgetDiagram;
    PanelWorld *widgetWorld;
    PanelInfo *widgetInfo;
    
    void timerEvent(QTimerEvent * event);
    void setChannelState(qint32 index, qint32 state, qint32 label, qreal value);
    void setRadarItem(qint32 index, qreal azm, qreal elv);
    void setWorldLocation(qreal lat, qreal lon);
    void setWorldSolution(qreal lat, qreal lon, qreal alt, boolean isVisible);
    void setTime(qint32 value);
    void createActions();
    void createTrayIcon();
    void readSettings();
    void setChannel(uint32_t channel, uint32_t id, uint32_t carrier);
    
private slots:
    void open();
    void clearLogs();
    void plot();
    void readyPlotSlot(float **plot);
    void setSatelliteIndex();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif	/* _MAINFORM_H */
