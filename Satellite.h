/* 
 * File:   Satellite.h
 * Author: Taran
 *
 * Created on 29 Май 2015 г., 9:38
 */

#ifndef SATELLITE_H
#define	SATELLITE_H

#include "inttypes.h"
#include "kmodel.h"

#include <QString>

class Satellite {
public:
    Satellite();
    virtual ~Satellite();
    void loadAgl(const QString fileName);
    double getFrequencyL3Current(int index) const;
    double getFrequencyL2Current(int index) const;
    double getFrequencyL1Current(int index) const;
    double getFrequencyL3Doppler(int index) const;
    double getFrequencyL2Doppler(int index) const;
    double getFrequencyL1Doppler(int index) const;
    double getFrequencyL3(int index) const;
    double getFrequencyL2(int index) const;
    double getFrequencyL1(int index) const;
    double* getGasc();
    double* getAerv();
    void setLocationLla(double latitude, double longitude, double altitude);
    void setTime(double value, int index);
    bool isValid(int index);
    int getCount();
private:
    int count;
    static const double SpeedOfLight        = 299792458.0;
    
    static const int    AglCount            = 32;
    static const double FrequencyL1         = 1602000000.0;
    static const double FrequencyL2         = 1246000000.0;
    static const double FrequencyL3         = 1202025000.0;
    static const double FrequencyL1Delta    = 562500.0;
    static const double FrequencyL2Delta    = 437500.0;
    
    kstruct agl[AglCount];
    double locationGasc[6];
    double locationLla[3]; //lat lon alt
    double aerv[4]; //azimuth elevation range velocity
    double gasc[6]; // GASC
    double frequencyL1[AglCount];
    double frequencyL2[AglCount];
    double frequencyL3[AglCount];
    double frequencyL1Doppler[AglCount];
    double frequencyL2Doppler[AglCount];
    double frequencyL3Doppler[AglCount];
    bool appendAgl(const QString line[3]);
    void setFrequency(int index);
};

#endif	/* SATELLITE_H */

