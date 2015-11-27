/* 
 * File:   PanelWorld.h
 * Author: Taran
 *
 * Created on 25 Ноябрь 2015 г., 13:25
 */

#ifndef PANELWORLD_H
#define	PANELWORLD_H

#include "PanelWidget.h"


class PanelWorld : public PanelWidget {
    Q_OBJECT
public:
    PanelWorld();
    virtual ~PanelWorld();
    void setPosition(qreal lat, qreal lon);
    void setSolution(qreal lat, qreal lon);
protected:    
    virtual void paintEvent(QPaintEvent*);
private:
    void drawItems(QPainter *p);
    qreal latw;
    qreal lonw;
    qreal lats;
    qreal lons;
};

#endif	/* PANELWORLD_H */

