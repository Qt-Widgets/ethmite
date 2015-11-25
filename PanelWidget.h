/* 
 * File:   PanelWidget.h
 * Author: Taran
 *
 * Created on 24 Ноябрь 2015 г., 9:31
 */

#ifndef PANELWIDGET_H
#define	PANELWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <qmath.h>

class PanelWidget : public QWidget{
    Q_OBJECT
public:
    static const int BorderRadius = 8;
    
    PanelWidget();
    virtual ~PanelWidget();
protected:    
    virtual void paintEvent(QPaintEvent*);
    void setMargins(QPainter *p);
private:

};

#endif	/* PANELWIDGET_H */

