/* 
 * File:   PanelRadar.h
 * Author: Taran
 *
 * Created on 24 Ноябрь 2015 г., 10:46
 */

#ifndef PANELRADAR_H
#define	PANELRADAR_H
#include "PanelWidget.h"
#include <qmath.h>

    
class PanelRadar : public PanelWidget {
    Q_OBJECT
    
public:
    static const int ItemsCount = 32;
    PanelRadar();
    virtual ~PanelRadar();
    void setRadarItem(int index, qreal azm, qreal elv);    
protected:    
    virtual void paintEvent(QPaintEvent*);
    
private:
    
    class RadarItem{
    public:
        RadarItem() {    
            azm     = 0.0;//(qreal)(qrand() % 628) * 0.01;
            elv     = -M_PI_2;//(qreal)(qrand() % 157) * 0.01;
        }
        qreal azm;
        qreal elv;
    };
    
    void drawItems(QPainter *p);
    RadarItem *items;
};

#endif	/* PANELRADAR_H */

