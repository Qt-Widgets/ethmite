/* 
 * File:   TimeSender.cpp
 * Author: Taran
 * 
 * Created on 30 Ноябрь 2015 г., 10:20
 */

#include "TimeSender.h"
#include <qmath.h>

TimeSender::TimeSender(quint16 port) {
    udpSocket = new QUdpSocket(this);
    this->port = port;
    
    packet.marker       = 0xFEDF3A1C;
    packet.length       = sizeof(udptimepacket) - 8;
    packet.code         = 0x01;
    packet.reliability  = 0x00;
    
    current = 0;
}

TimeSender::~TimeSender() {
}

void TimeSender::setTime(time_t value) {
    const char *data = (char *)&packet;

    int h, m, s;
    value %= 86400;
    h = qFloor(value / 3600);
    m = qFloor((value % 3600) / 60);
    s = qFloor(value % 60);

    if (value != current) {
//        tm *t = gmtime(value);
        time_t now = time(0);
        tm *t = localtime(&now);
        packet.year     = (int16_t)t->tm_year + 1900;
        packet.month    = (int16_t)t->tm_mon + 1;
        packet.wday     = (int16_t)t->tm_wday;
        packet.day      = (int16_t)t->tm_mday;
        packet.hour     = (int16_t)h;//t->tm_hour;
        packet.minute   = (int16_t)m;//t->tm_min;
        packet.second   = (int16_t)s;//t->tm_sec;
        packet.millis   = (int16_t)0;

        udpSocket->writeDatagram(data, sizeof(udptimepacket), QHostAddress::Broadcast, port);
        
        current = value;
    }
}

