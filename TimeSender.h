/* 
 * File:   TimeSender.h
 * Author: Taran
 *
 * Created on 30 Ноябрь 2015 г., 10:20
 */

#ifndef TIMESENDER_H
#define	TIMESENDER_H
#include <QUdpSocket>
#include <stdint.h>
#include <time.h>

class TimeSender : public QObject {
    Q_OBJECT
public:
    TimeSender(quint16 port);
    virtual ~TimeSender();
    
    void setTime(time_t value);
private:
    
#pragma pack (1)
    typedef struct udptimepacket_tag {
        int32_t marker;
        int32_t length;
        int32_t code;
        int32_t reliability;
        int16_t year;
        int16_t month;
        int16_t wday;
        int16_t day;
        int16_t hour;
        int16_t minute;
        int16_t second;
        int16_t millis;
    } udptimepacket;
    
    time_t current;
    quint16 port;
    udptimepacket packet;
    QUdpSocket *udpSocket;
};

#endif	/* TIMESENDER_H */

