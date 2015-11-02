/* 
 * File:   Satellite.cpp
 * Author: Taran
 * 
 * Created on 29 Май 2015 г., 9:38
 */

#include "Satellite.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "time.h"

Satellite::Satellite() {
    count = 0;
    setLocationLla(
            44.98 * M_PI / 180.0, 
            41.12 * M_PI / 180.0, 
            213.0
        );
    
    for (int i = 0; i < AglCount; i++) {
        agl[i].valid = 0;
    }
}

Satellite::~Satellite() {
}

int Satellite::getCount() {
    return count;
}

void Satellite::loadAgl(const QString fileName) {
    QFile file(fileName);
    bool isOpen = file.open(QFile::ReadOnly | QFile::Text);
    
    if (!isOpen) {
        return;
    }
    
    count = 0;
    
    QTextStream txt(&file);
    QString line[3];
    line[0] = txt.readLine();
    
    while (!line[0].isNull()) {
        if (!line[0].isEmpty()) {
            line[1] = txt.readLine();
            line[2] = txt.readLine();
            if (!line[1].isNull() && !line[2].isNull() &&
                    !line[1].isEmpty() && !line[2].isEmpty()) {
                appendAgl(line);
            }
        }
        line[0] = txt.readLine();
    }
    
    file.close();
}

double Satellite::getFrequencyL3Current(int index) const {
    return frequencyL3[index] + frequencyL3Doppler[index];
}

double Satellite::getFrequencyL2Current(int index) const {
    return frequencyL2[index] + frequencyL2Doppler[index];
}

double Satellite::getFrequencyL1Current(int index) const {
    return frequencyL1[index] + frequencyL1Doppler[index];
}

double Satellite::getFrequencyL3Doppler(int index) const {
    return frequencyL3Doppler[index];
}

double Satellite::getFrequencyL2Doppler(int index) const {
    return frequencyL2Doppler[index];
}

double Satellite::getFrequencyL1Doppler(int index) const {
    return frequencyL1Doppler[index];
}

double Satellite::getFrequencyL3(int index) const {
    return frequencyL3[index];
}

double Satellite::getFrequencyL2(int index) const {
    return frequencyL2[index];
}

double Satellite::getFrequencyL1(int index) const {
    return frequencyL1[index];
}

double* Satellite::getGasc() {
    return gasc;
}

double* Satellite::getAerv() {
    return aerv;
}

void Satellite::setLocationLla(double latitude, double longitude, double altitude) {
    this->locationLla[0] = latitude;
    this->locationLla[1] = longitude;
    this->locationLla[2] = altitude;
    geod2asc(locationLla, locationGasc);
    locationGasc[3] = 0.0;
    locationGasc[4] = 0.0;
    locationGasc[5] = 0.0;
}

bool Satellite::appendAgl(const QString line[3]) {
    bool ok;
    bool result = false;
    int index;
    kstruct *s;
    QStringList list2 = line[1].split(" ", QString::SkipEmptyParts);
    QStringList list3 = line[2].split(" ", QString::SkipEmptyParts);

    if (list2.count() >= 10 && list3.count() >= 6) {
        result = true;

        index = list2.at(0).toInt(&ok) - 1;
        s = &agl[index];
        if (index >= 0 || index < AglCount) {
            s->nfreq    = list2.at(1).toInt(&ok);
            s->valid    = list2.at(2).toInt(&ok);
            s->day      = list2.at(3).toInt(&ok);
            s->mon      = list2.at(4).toInt(&ok);
            s->year     = list2.at(5).toInt(&ok);
            s->tlam     = list2.at(6).toDouble(&ok);
            s->timezone = 3;
            
            s->node     = list3.at(0).toDouble(&ok) * M_PI;
            s->incl     = list3.at(1).toDouble(&ok) * M_PI + 63.0 * M_PI / 180.0;
            s->argp     = list3.at(2).toDouble(&ok) * M_PI;
            s->ecc      = list3.at(3).toDouble(&ok);
            s->period   = list3.at(4).toDouble(&ok) + 43200.0;
            s->dperiod  = list3.at(5).toDouble(&ok);
             
            s->hr       =  (int)s->tlam / 3600;
            s->minute   = ((int)s->tlam % 3600) / 60;
            s->sec      = s->tlam - (double)(s->hr * 3600 + s->minute * 60);            
            
            setTime(time(0), index);
            count++;
        }
    }
    return result;
}

void Satellite::setTime(double value, int index) {
    double lla[3];
    kstruct *s = &agl[index];
    glkmodel(value, s);
    
    asc2geod(s->state, lla);
    asc2aerv(locationGasc, s->state, aerv);
    setFrequency(index);
    
//    printf("[%02d]\t", index + 1);
//    printf("lat = %7.2f\t", lla[0] * 180 / M_PI);
//    printf("lon = %7.2f\t", lla[1] * 180 / M_PI);
//    printf("alt = %8.2f\t", lla[2] / 1000.0);
//    printf("azm = %7.2f\t", aerv[0] * 180.0 / M_PI);
//    printf("elv = %7.2f\t", aerv[1] * 180.0 / M_PI);
//    printf("rng = %8.2f\t", aerv[2] / 1000.0);
//    printf("vel = %6.3f\t", aerv[3] / 1000.0);
//    printf("frq = %8.3f\t", getFrequencyL1(index) / 1000000.0);
//    printf("dpr = %8.3f\n", getFrequencyL1Doppler(index) / 1000.0);
//    fflush(stdout);
}

void Satellite::setFrequency(int index) {
    kstruct *s = &agl[index];
    frequencyL1[index] = FrequencyL1 + s->nfreq * FrequencyL1Delta;
    frequencyL1Doppler[index] = -frequencyL1[index] * aerv[3] / SpeedOfLight;
}

bool Satellite::isValid(int index) {
    kstruct *s = &agl[index];
    return (s->valid > 0);
}
