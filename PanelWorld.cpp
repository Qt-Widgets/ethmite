/* 
 * File:   PanelWorld.cpp
 * Author: Taran
 * 
 * Created on 25 Ноябрь 2015 г., 13:25
 */

#include "PanelWorld.h"

PanelWorld::PanelWorld() {
    latw = 0.0;
    lonw = 0.0;
    lats = 0.0;
    lons = 0.0;
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
    drawItems(&p);

    p.end();
}

void PanelWorld::drawItems(QPainter *p) {
    
    QString label;
    bool visible;
    qreal xw, yw, xs, ys;
    
    qreal w = (qreal)p->device()->width();
    qreal h = (qreal)p->device()->height();
    qreal r = qMin(w, h) * 0.05;

    xw = 0.5 * (1.0 + lonw / M_PI) * w;
    yw = (0.5 - latw / M_PI) * h;
    xs = 0.5 * (1.0 + lons / M_PI) * w;
    ys = (0.5 - lats / M_PI) * h;

    QPainterPath path;
    p->setPen(Qt::NoPen);
    path.addEllipse(QPointF(xw, yw), r, r);
    p->fillPath(path, QColor::fromRgbF(1.0, 0.0, 0.0, 0.3));
    p->drawPath(path);
    p->setPen("green");
    p->drawLine(0, ys, w, ys);
    p->drawLine(xs, 0, xs, h);

}
void PanelWorld::setPosition(qreal lat, qreal lon) {
    latw = lat;
    lonw = lon;
    repaint();
}

void PanelWorld::setSolution(qreal lat, qreal lon) {
    lats = lat;
    lons = lon;
    repaint();
}
