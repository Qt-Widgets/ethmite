/* 
 * File:   PanelDiagram.cpp
 * Author: Taran
 * 
 * Created on 25 Ноябрь 2015 г., 9:35
 */

#include "PanelDiagram.h"

PanelDiagram::PanelDiagram() {
    items = new DiagramItem[ChannelCount]();
}

PanelDiagram::~PanelDiagram() {
}

void PanelDiagram::paintEvent(QPaintEvent* event) {
    PanelWidget::paintEvent(event);
    QPainter p;
    p.begin(this);
    setMargins(&p);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    
    QPen pen = p.pen();
    pen.setWidth(1);
    pen.setColor(QColor("black"));
    p.setPen(pen);
    
    drawItems(&p);

    p.end();
}

void PanelDiagram::drawItems(QPainter *p) {
    QString label;
    qreal x = (qreal)BorderRadius * 0.5;
    qreal y;
    qreal dx = (qreal)p->device()->width() / (qreal)ChannelCount;
    qreal w = dx - BorderRadius;
    qreal h;

    QFont font = p->font();
    font.setPointSizeF(w * 0.5);
    font.setFamily("Consolas");
    p->setFont(font);

    for (int i = 0; i < ChannelCount; i++) {
        h = 1 + items[i].value * ((qreal)p->device()->height() - 1);
        y = (qreal)p->device()->height() - h;
        QPainterPath path;
        path.addRect(x + dx * i, y, w, h);
        
        switch (items[i].state) {
            case StateDllLocked:
                p->setPen(ColorPenDllLocked);
                p->fillPath(path, ColorDllLocked);
                break;
            case StatePllLocked:
                p->setPen(ColorPenPllLocked);
                p->fillPath(path, ColorPllLocked);
                break;
            case StateInfLocked:
                p->setPen(ColorPenInfLocked);
                p->fillPath(path, ColorInfLocked);
                break;
            case StateNotLocked:
            default:
                p->setPen(ColorPenNotLocked);
                p->fillPath(path, ColorNotLocked);
                break;
        }

        p->drawPath(path);
        if (items[i].label > 0) {
            p->setPen(QColor("black"));
            h = (qreal)p->device()->height();
            y = (qreal)p->device()->height() - h;
            label = QString("%1").arg(items[i].label, 2, 10, QChar('0'));
            p->drawText(QRectF(x + dx * i, y, w, h), Qt::AlignBottom | Qt::AlignHCenter, label);
        }
    }
}

void PanelDiagram::setDiagramItem(int index, int state, int label, qreal value) {
    if (index >= 0 && index < ChannelCount) {
        items[index].state = state & 0x7;
        items[index].label = label;
        items[index].value = value;
        repaint();
    }
}
