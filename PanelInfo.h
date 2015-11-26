/* 
 * File:   PanelInfo.h
 * Author: Taran
 *
 * Created on 25 Ноябрь 2015 г., 14:56
 */

#ifndef PANELINFO_H
#define	PANELINFO_H

#include "PanelWidget.h"


class PanelInfo : public PanelWidget {
    Q_OBJECT
public:
    PanelInfo();
    virtual ~PanelInfo();
    
    void setTime(int value);
    void setSolution(qreal lat, qreal lon, qreal alt, qreal dt);
protected:    
    virtual void paintEvent(QPaintEvent*);
private:
    QString lineTime;
    QString lineLat;
    QString lineLon;
    QString lineAlt;
    QString lineDate;
    QString lineDt;
};

#endif	/* PANELINFO_H */

