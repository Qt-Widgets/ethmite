/* 
 * File:   PanelRadar.cpp
 * Author: Taran
 * 
 * Created on 24 Ноябрь 2015 г., 10:46
 */

#include "PanelRadar.h"

PanelRadar::PanelRadar() {
    items = new RadarItem[ItemsCount]();
}

PanelRadar::~PanelRadar() {
}

void PanelRadar::paintEvent(QPaintEvent* event) {
    const qreal scale0 = 0.14644660940672623779957781894758;
    const qreal scale1 = (1.0 - scale0);
    
    PanelWidget::paintEvent(event);
    QPainter p;
    p.begin(this);
    setMargins(&p);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    
    QPen pen = p.pen();
    pen.setWidth(1);
    p.setPen(QColor("black"));
    
    QPainterPath path;
    qreal rx = p.device()->width();
    qreal ry = p.device()->height();
    
    QPointF point(0.5 * rx, 0.5 * ry);
    
    path.addEllipse(point, 0.50 * rx, 0.50 * ry);
    p.fillPath(path, QColor("white"));
    path.addEllipse(point, 0.25 * rx, 0.25 * ry);
    p.drawPath(path);

    p.drawLine(0, 0.5 * ry, rx, 0.5 * ry);
    p.drawLine(0.5 * rx, 0, 0.5 * rx, ry);
    p.drawLine(rx * scale0 + 1, ry * scale0 + 1, rx * scale1 - 1, ry * scale1 - 1);
    p.drawLine(rx * scale0 + 1, ry * scale1 - 1, rx * scale1 - 1, ry * scale0 + 1);
    
    drawItems(&p);
    
    p.end();
}

void PanelRadar::drawItems(QPainter *p) {
    
    QString label;
    bool visible;
    qreal xx, yy, rr;
    
    qreal w = (qreal)p->device()->width();
    qreal h = (qreal)p->device()->height();
    qreal r = qMin(w, h) * 0.075;

    QFont font = p->font();
    font.setPointSizeF(r);
    font.setFamily("Consolas");
    p->setFont(font);
    
    for (int i = 0; i < ItemsCount; i++) {
        rr = 0.5 - items[i].elv / M_PI;
        if (rr >= 0.0 && rr <= 0.5) {
            xx = rr * qCos(items[i].azm - M_PI_2);
            yy = rr * qSin(items[i].azm - M_PI_2);
            label = QString("%1").arg(i + 1, 2, 10, QChar('0'));
            visible = true;
        }
        else {
            xx = 0.0;
            yy = 0.0;
            label = "00";
            visible = false;
        }
        
        if (visible) {
            qreal x = w * 0.5 + xx * w;
            qreal y = h * 0.5 + yy * h;

            QPainterPath path;
            path.addEllipse(QPointF(x, y), r, r);
            p->fillPath(path, QColor("lightgreen"));
            p->setPen(QColor("green"));
            p->drawPath(path);
            p->setPen(QColor("black"));
            p->drawText(QRectF(x - r, y - r, 2 * r, 2 * r), Qt::AlignCenter, label);
        }
    }
}

void PanelRadar::setRadarItem(int index, qreal azm, qreal elv) {
    if (index >= 0 && index < ItemsCount) {
        items[index].azm = azm;
        items[index].elv = elv;
        repaint();
    }
}
