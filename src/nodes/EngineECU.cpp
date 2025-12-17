#include "EngineECU.h"
#include "../can/CANBus.h"


#include <QRandomGenerator>

EngineECU::EngineECU(CANBus* bus, int periodMS)
    : CANNode{"EngineECU", bus},
    d_rpm{0},
    d_temp{0},
    d_load{0}
{
    QObject::connect(&d_timer, &QTimer::timeout,this, &EngineECU::sendEngineFrame);
    d_timer.start(periodMS);

}

void EngineECU::sendEngineFrame()
{
    d_rpm = QRandomGenerator::global()->bounded(0,9000);
    d_temp = QRandomGenerator::global()->bounded(0,200);
    d_load = QRandomGenerator::global()->bounded(0,100);

    QByteArray data;
    data.append(static_cast<char>((d_rpm >> 8) & 0xFF));
    data.append(static_cast<char>(d_rpm & 0xFF));
    data.append(static_cast<char>(d_temp));
    data.append(static_cast<char>(d_load));

    CANFrame frame(0x100,data);
    this->sendFrame(frame);
}

void EngineECU::receiveFrame(const CANFrame& frame)
{

}


