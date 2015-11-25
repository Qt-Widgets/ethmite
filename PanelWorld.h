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
protected:    
    virtual void paintEvent(QPaintEvent*);
private:

};

#endif	/* PANELWORLD_H */

