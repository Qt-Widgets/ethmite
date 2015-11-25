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
protected:    
    virtual void paintEvent(QPaintEvent*);
private:
    int time;
    qreal lla[3];
};

#endif	/* PANELINFO_H */

