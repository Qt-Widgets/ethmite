/* 
 * File:   QLed.h
 * Author: Taran
 *
 * Created on 27 Август 2015 г., 15:47
 */

#ifndef QLED_H
#define	QLED_H
#include <QFrame>
#include <QColor>

class QLed : public QFrame {
    Q_OBJECT
public:
    QLed();
    void setState(const QColor &color);
    virtual ~QLed();
private:

};

#endif	/* QLED_H */

