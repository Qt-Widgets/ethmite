/* 
 * File:   PanelInfo.cpp
 * Author: Taran
 * 
 * Created on 25 Ноябрь 2015 г., 14:56
 */

#include "PanelInfo.h"
#include <time.h>

PanelInfo::PanelInfo() {
    setTime(0);
    setDate(0);
    setSolution(0.0, 0.0, 0.0, 0.0);
}

PanelInfo::~PanelInfo() {
}

void PanelInfo::paintEvent(QPaintEvent* event) {
    
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

    p.drawText(QPointF(0, dy * 1 - 0.5 * fs), lineDate);
    p.drawText(QPointF(0, dy * 2 - 0.5 * fs), lineTime);
    p.drawText(QPointF(0, dy * 3 - 0.5 * fs), lineLat);
    p.drawText(QPointF(0, dy * 4 - 0.5 * fs), lineLon);
    p.drawText(QPointF(0, dy * 5 - 0.5 * fs), lineAlt);
    p.drawText(QPointF(0, dy * 6 - 0.5 * fs), lineDt);
    
    p.end();
}

void PanelInfo::setTime(int value) {
    int h, m, s;
    value %= 86400;
    h = qFloor(value / 3600);
    m = qFloor((value % 3600) / 60);
    s = qFloor(value % 60);
    
    lineTime = QString("%1:%2:%3")
            .arg(h, 2, 10, QChar('0'))
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
    repaint();
}

void PanelInfo::setDate(time_t value) {
    struct tm *d = gmtime(&value);
    lineDate = QString("%1.%2.%3")
            .arg(d->tm_mday       , 2, 10, QChar('0'))
            .arg(d->tm_mon + 1    , 2, 10, QChar('0'))
            .arg(d->tm_year + 1900, 4, 10, QChar('0'));
    repaint();
}

void PanelInfo::setSolution(qreal lat, qreal lon, qreal alt, qreal dt) {
    
    if ((lat != lat) || (lon != lon) || (alt != alt) || (dt != dt)) {
        return;
    }
    
    lineLat = QString("Ш [\u00b0]:%1").arg(lat * 57.29577951308, 0, 'f', 5, QChar(' '));
    lineLon = QString("Д [\u00b0]:%1").arg(lon * 57.29577951308, 0, 'f', 5, QChar(' '));
    lineAlt = QString("В [м]:%1").arg(alt, 0, 'f', 1, QChar(' '));
    lineDt  = QString("\u0394[мс]:%1").arg(dt * 1000, 0, 'f', 3, QChar(' '));
    repaint();
}
