/* 
 * File:   gloinf.h
 * Author: Taran
 *
 * Created on October 23, 2015, 11:02 AM
 */

#ifndef GLOINF_H
#define	GLOINF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef struct {
    int32_t p1;     ///< period of the information update
    int32_t t;      ///< frame time
    float x[3];   ///< x coords
} gloinf_line1;

typedef struct {
    int32_t b;      ///< sign of frame unreliability
    int32_t p2;     ///< sign parity of time interval
    int32_t t;      ///< time interval of the operational information
    float y[3];   ///< x coords
} gloinf_line2;

typedef struct {
    int32_t p3;     ///< sign 5 units in current frame
    float gamma;  ///< frequency offset from the nominal value
    int32_t p;      ///< frequency-time mode
    int32_t l;      ///< sign of unreliability
    float z[3];   ///< x coords
} gloinf_line3;

typedef struct {
    float tau;    ///< time offset current unit from the system
    float dtau;   ///< time offset beetwen L1 and L2 PRS
    int32_t e;      ///< age of operational information after loading
    int32_t p4;     ///< information is updated in the current time interval
    int32_t f;      ///< target measurement accuracy range
    int32_t nt;     ///< the operational current calendar day
    int32_t n;      ///< the system number of the current unit
    int32_t m;      ///< mark of the unit
} gloinf_line4;

typedef struct {
    int32_t n;      ///< the almanac current calendar day
    float tau;    ///< correction system time of the UTC
    int32_t n4;     ///< number of four-year period
    float taug;   ///< correction system time of the GPS (NAVSTAR)
    int32_t l;      ///< sign of unreliability
} gloinf_line5;

typedef struct {
    int32_t c;      ///< suitability
    int32_t m;      ///< mark of the unit
    int32_t n;      ///< system number
    float tau;    ///< coarse correction of the system time
    float lambda; ///< longitude of the ascending node
    float di;     ///< correction of the inclination
    float eps;    ///< eccentricity
} gloinf_linea1;

typedef struct {
    float omega;
    float t;      ///< crossing time of the ascending node
    float dt;
    float dtt;
    int32_t h;
    int32_t l;      ///< sign of unreliability
} gloinf_linea2;

typedef struct {
    float b[2];   ///< dUT1 poly coefficients
    int32_t kp;     ///< sign of second correction
} gloinf_linea3;

typedef struct {
    int32_t l;      ///< sign of unreliability
} gloinf_linea4;

typedef struct {
//    int32_t lines[45];
    int32_t index;
    int32_t frame_index;
    gloinf_line1  s1;
    gloinf_line2  s2;
    gloinf_line3  s3;
    gloinf_line4  s4;
    gloinf_line5  s5;
    gloinf_linea1 s6;
    gloinf_linea2 s7;
    gloinf_linea1 s8;
    gloinf_linea2 s9;
    gloinf_linea1 s10;
    gloinf_linea2 s11;
    gloinf_linea1 s12;
    gloinf_linea2 s13;
    
    gloinf_linea1 s14;
    gloinf_linea2 s15;
    gloinf_linea3 s14a;
    gloinf_linea4 s15a;
} gloinf_frame;

void gloinf_print(gloinf_frame *frame);
void gloinf_save(const char *fname);

#ifdef	__cplusplus
}
#endif

#endif	/* GLOINF_H */

