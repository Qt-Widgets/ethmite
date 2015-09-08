/* 
 * File:   QLed.cpp
 * Author: Taran
 * 
 * Created on 27 Август 2015 г., 15:47
 */

#include "QLed.h"

QLed::QLed() {
    this->setMinimumSize(12, 12);
    this->setAutoFillBackground(true);
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Sunken);
    QPalette p = this->palette();
    p.setColor(QPalette::Window, Qt::yellow);
    this->setPalette(p);
}

QLed::~QLed() {
}

void QLed::setState(const QColor &color) {
    QPalette p = this->palette();
    p.setColor(QPalette::Window, color);
    this->setPalette(p);
}
