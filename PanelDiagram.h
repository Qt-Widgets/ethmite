/* 
 * File:   PanelDiagram.h
 * Author: Taran
 *
 * Created on 25 Ноябрь 2015 г., 9:35
 */

#ifndef PANELDIAGRAM_H
#define	PANELDIAGRAM_H

#include "PanelWidget.h"


class PanelDiagram : public PanelWidget {
    Q_OBJECT
public:
    static const int ChannelCount = 8;
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
    
    PanelDiagram();
    virtual ~PanelDiagram();
void setDiagramItem(int index, int state, int label, qreal value);    
protected:    
    virtual void paintEvent(QPaintEvent*);
private:
    
    class DiagramItem {
    public:
        DiagramItem() {
            value = (qreal)(qrand() % 1000) * 0.001;
            state = 7 >> (qrand() % 3);
            label = qrand() % 24;
        }
        qreal value;
        int state;
        int label;
    };
    
    DiagramItem *items;
    void drawItems(QPainter *p);
};

#endif	/* PANELDIAGRAM_H */

