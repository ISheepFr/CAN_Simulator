#include "BrakeECU.h"

BrakeECU::BrakeECU(CANBus* bus, int periodMS)
    :QObject{nullptr},
    CANNode{"BrakeECU",bus}
{
    connect(&d_timer,&QTimer::timeout,this,&BrakeECU::sendBrakeFrame);
    d_timer.start(periodMS);
}

void BrakeECU::receiveFrame(const CANFrame &frame)
{

}

int BrakeECU::brake() const
{
    return d_brake;
}

void BrakeECU::setBrakePressure(int value)
{
    uint8_t v = qBound(0,value,255);
    if(d_brake != v)
    {
        d_brake = v;
        emit brakeChanged();
    }
}

void BrakeECU::sendBrakeFrame()
{
    QByteArray data(8,0);

    data[0] = static_cast<char>(d_brake);
    data[1] = static_cast<char>(d_brake);
    data[2] = 1; //valid flag
    data[3] = (d_brake > 5) ? 1:0; //brake switch

    CANFrame frame(0x070,data);
    sendFrame(frame);
}
