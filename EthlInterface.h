/* 
 * File:   SerialInterface.h
 * Author: Taran
 *
 * Created on 7 Май 2015 г., 17:30
 */

#ifndef ETHINTERFACE_H
#define	ETHINTERFACE_H

#include <QFile>
#include <QTextStream>
#include <QTcpSocket>
#include "inttypes.h"
#include "gloinf.h"

class EthInterface : public QTcpSocket {
    Q_OBJECT
public:
    static const int      ChannelCount    = 8;
    
    static const uint32_t CmdRead         = 0;
    static const uint32_t CmdWrite        = 1;
    
    static const uint32_t CmdAddrLprsSa   = 0;
    static const uint32_t CmdAddrLcarSa   = 1;
    static const uint32_t CmdAddrInfoSa   = 2;
    
    static const uint32_t CmdAddrLprsHa   = 4;
    static const uint32_t CmdAddrLcarHa   = 5;
    static const uint32_t CmdAddrInfoHa   = 6;

    static const uint32_t CmdAddrFrame    = 12;
    static const uint32_t CmdAddrSlv      = 13;
    static const uint32_t CmdAddrVga      = 14;
    static const uint32_t CmdAddrControl  = 15;

    static const uint32_t CmdAddrPlot   = 16;
#pragma pack (1)
    typedef struct loop_prs_tag {
        uint32_t id;
        int32_t number;
        uint32_t locked;
        uint32_t tout;
        uint32_t reset;
        int32_t code;
        int32_t offset;
        float error;
        float k[2];
        float z[2];
        float q[5];
        float i[5];
        float level;
        int32_t index;
        uint32_t rc;
        uint32_t phase;
        double range;
        double prediction;
        double sat[3];
    } loop_prs;
    
#pragma pack (1)
    typedef struct loop_car_tag {
        uint32_t id;
        uint32_t enabled;
        uint32_t locked;
        uint32_t tout;
        uint32_t reset;
        int32_t code;
        float error;
        float k[2];
        float z[2];
        float q;
        float i;
        float level;
        int32_t index;
        float snr;
        uint64_t phase;
    } loop_car;

#pragma pack (1)
    typedef struct state_ifc_tag {
        uint32_t buf_param;
        uint32_t buf_channel;
    } state_ifc;

typedef struct {
    double sat[ChannelCount * 4];
    double rng[ChannelCount];
    double p[ChannelCount];
    double loc[3];
    double dt;
    double err;
    int32_t s[ChannelCount];
    float ms[ChannelCount];
    int32_t is_valid;
    int32_t count;
} solution;

#pragma pack (1)
    typedef struct command_tag {
        uint32_t cmd;
        uint32_t addr;
        uint32_t offset;
        uint32_t length;
        uint32_t value;
    } command;

#pragma pack (1)
    typedef struct info_tag {
        uint32_t id;
        uint32_t inf[4];
    } info;
    
    EthInterface();
    virtual ~EthInterface();
    void sendPacket(uint32_t *data, int dlen);
    void clear();
    bool isLocked(int channel);
    int getStates(int channel);
    int getTime(int channel);
    float getSnr(int channel);
    double *getLla();
    
private:
    
    static const uint32_t Seop       = 0x7E7E7E7E;
    static const uint32_t Seopxor    = 0x20202020;
    static const uint32_t Rseop0     = 0x7D7D7D7D;
    static const uint32_t Rseop1     = 0x5E5E5E5E;
    static const uint32_t Rseop2     = 0x5D5D5D5D;
    static const int  BufferLength  = 1024;
    static const int  BufferMask    = BufferLength - 1;
    
    static const int CmdMaxLength   = 128;
    static const int PlotLength     = 512;
    static const int PlotSamplesInPacket = CmdMaxLength / 2 ;
    static const int PlotPacketCount     = PlotLength / PlotSamplesInPacket;

    uint32_t buffer[BufferLength];
    float *plot[2];
    
    QFile frsa[ChannelCount];
    QFile frha[ChannelCount];
    QFile ffsa[ChannelCount];
    QFile ffha[ChannelCount];
    QFile fisa[ChannelCount];
    QFile fiha[ChannelCount];
    QFile fsol;
    
    QTextStream srsa[ChannelCount];
    QTextStream srha[ChannelCount];
    QTextStream sfsa[ChannelCount];
    QTextStream sfha[ChannelCount];
    QTextStream sisa[ChannelCount];
    QTextStream siha[ChannelCount];
    QTextStream ssol;
    
    bool locked[ChannelCount];
    int states[ChannelCount];
    float snr[ChannelCount];
    int time[ChannelCount];
    double xyzt[4];
    double lla[3] = {0, 0, 0};
    
    bool acceptData(uint32_t value);
    void acceptPlot();
    void acceptFrame();
    void sendData(const uint32_t value, int32_t *index);
    uint32_t crc(uint32_t *data, int from, int len);
    void execCommand();
    void setSolution(double x, double y, double z, double t);
    void xyz2lla(double *xyz, double *lla);    
    
private slots:
    void readyReadSlot();
signals:
    void readyPlot(float **plot);
    
};

#endif	/* SERIALINTERFACE_H */

