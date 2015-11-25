/* 
 * File:   PanelWidget.cpp
 * Author: Taran
 * 
 * Created on 24 Ноябрь 2015 г., 9:31
 */

#include "PanelWidget.h"

PanelWidget::PanelWidget() {
    this->resize(400, 300);
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor("White"));
    this->setPalette(pal);
}

PanelWidget::~PanelWidget() {
}

void PanelWidget::setMargins(QPainter *p) {
    qreal w = (qreal)(p->device()->width() == 0 ? 1 :  p->device()->width());
    qreal h = (qreal)(p->device()->height() == 0 ? 1 : p->device()->height());
    qreal kx = (w - 2 * BorderRadius) / w;
    qreal ky = (h - 2 * BorderRadius) / h;
    
    p->translate(BorderRadius, BorderRadius);
    p->scale(kx, ky);
}

void PanelWidget::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    QPen pen = p.pen();
    pen.setWidth(2);
    p.setPen(pen);
    
    QPainterPath path;
    QRectF r(1.0, 1.0, p.device()->width() - 2, p.device()->height() - 2);
    path.addRoundedRect(r, BorderRadius, BorderRadius);
    p.fillPath(path, QColor("lavender"));
    p.drawPath(path);
    p.end();
}
