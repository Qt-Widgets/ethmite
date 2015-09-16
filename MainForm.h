/* 
 * File:   MainForm.h
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 16:56
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "ui_MainForm.h"
#include "EthlInterface.h"
#include "PlotForm.h"
#include "IoForm.h"
#include "QLed.h"

class MainForm : public QMainWindow {
    Q_OBJECT
public:
    MainForm();
    virtual ~MainForm();
private:
    static const int IoFormCount = 18;
    static const int ChannelCount = 8;
    IoForm *ioForm[IoFormCount];
    Ui::MainForm widget;
    EthInterface com;
    PlotForm plotForm;
    QLed *leds[IoFormCount];
    void timerEvent(QTimerEvent * event);
    void setChannelState(qint32 index, qint32 state, qint32 label, qreal value);
    void setTime(qint32 value);
private slots:
    void open();
    void plot();
    void readyPlotSlot(float **plot);
    void setSatelliteIndex();
};

#endif	/* _MAINFORM_H */
