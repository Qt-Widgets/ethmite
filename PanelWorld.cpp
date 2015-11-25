/* 
 * File:   PanelWorld.cpp
 * Author: Taran
 * 
 * Created on 25 Ноябрь 2015 г., 13:25
 */

#include "PanelWorld.h"

PanelWorld::PanelWorld() {
}

PanelWorld::~PanelWorld() {
}

void PanelWorld::paintEvent(QPaintEvent* event) {
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
    
    QRectF r(0.0, 0.0, p.device()->width(), p.device()->height());

    p.drawImage(r, QImage(":/world.png"));
//    drawItems(&p);

    p.end();
}
