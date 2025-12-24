#include "PedalECU.h"

PedalECU::PedalECU(CANBus* bus,int periodMS)
    : QObject{nullptr},
    CANNode{"PedalECU",bus}
{
    connect(&d_timer, &QTimer::timeout,this, &PedalECU::sendPedalFrame);
    d_timer.start(periodMS);
}

void PedalECU::receiveFrame(const CANFrame& frame)
{
    //nothing now --> search if normally smthing is done there IRL
}

int PedalECU::pedal() const
{
    return d_pedal;
}

void PedalECU::setPedal(int value)
{
    uint8_t v = qBound(0,value, 255);
    if(d_pedal != v)
    {
        d_pedal = v;
        emit pedalChanged();
    }
}

void PedalECU::sendPedalFrame()
{
    QByteArray data;
    data.resize(8);
    data.fill(0);

    data[0] = static_cast<char>(d_pedal);
    data[1] = static_cast<char>(d_pedal);
    data[2] = 1; //valid flag, future feature :)

    CANFrame frame(0x090,data);
    sendFrame(frame);
}

