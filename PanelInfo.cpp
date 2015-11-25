/* 
 * File:   PanelInfo.cpp
 * Author: Taran
 * 
 * Created on 25 Ноябрь 2015 г., 14:56
 */

#include "PanelInfo.h"

PanelInfo::PanelInfo() {
    time = 32768;
    lla[0] = 1;
    lla[1] = 0;
    lla[2] = 0;
}

PanelInfo::~PanelInfo() {
}

void PanelInfo::paintEvent(QPaintEvent* event) {
    int h, m, s;
    
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
    
    qreal dy = p.device()->height() / 6;
    qreal fs = qMin(dy, p.device()->width() / 12.0);
    QFont font = p.font();
    font.setPointSizeF(fs);
    font.setFamily("Consolas");
    p.setFont(font);

    h = qFloor(time / 3600);
    m = qFloor((time % 3600) / 60);
    s = qFloor(time % 60);
    
    QString lineTime = QString("%1:%2:%3")
            .arg(h, 2, 10, QChar('0'))
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
    
    QString lineLat = QString("Ш[\u00b0] :%1").arg(lla[0] * 57.29577951308, 10, 'f', 5, QChar(' '));
    QString lineLon = QString("Д[\u00b0] :%1").arg(lla[1] * 57.29577951308, 10, 'f', 5, QChar(' '));
    QString lineAlt = QString("В[м] :%1").arg(lla[2], 6, 'f', 1, QChar(' '));
    
    p.drawText(QPointF(0, dy * 1), "01.01.2000");
    p.drawText(QPointF(0, dy * 2), lineTime);
    p.drawText(QPointF(0, dy * 3), lineLat);
    p.drawText(QPointF(0, dy * 4), lineLon);
    p.drawText(QPointF(0, dy * 5), lineAlt);
    p.drawText(QPointF(0, dy * 6), "\u0394[мс]:   0.000");
    
    p.end();
}

