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

    static const int StateNotLocked = 0;
    static const int StateDllLocked = 1;
    static const int StatePllLocked = 3;
    static const int StateInfLocked = 7;
    
    static const QColor ColorNotLocked;
    static const QColor ColorDllLocked;
    static const QColor ColorPllLocked;
    static const QColor ColorInfLocked;
    
    static const QColor ColorPenNotLocked;
    static const QColor ColorPenDllLocked;
    static const QColor ColorPenPllLocked;
    static const QColor ColorPenInfLocked;
    
    PanelWidget();
    virtual ~PanelWidget();
protected:    
    virtual void paintEvent(QPaintEvent*);
    void setMargins(QPainter *p);
private:

};

#endif	/* PANELWIDGET_H */

