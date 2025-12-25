#include "EngineECU.h"
#include "../can/CANBus.h"


#include <QRandomGenerator>

EngineECU::EngineECU(CANBus* bus, int periodMS,int simulationPeriodMS)
    : CANNode{"EngineECU", bus},
    d_rpm{800},
    d_temp{75},
    d_load{0}
   // lastTime{QDateTime::currentMSecsSinceEpoch()}

{
    QObject::connect(&d_timer, &QTimer::timeout,this, &EngineECU::onTimeout);
    d_timer.start(periodMS);

    //QObject::connect(&d_simTimer, &QTimer::timeout,this, &EngineECU::onSimTimeout);
    //d_simTimer.start(simulationPeriodMS);
}

void EngineECU::onTimeout()
{
    updateEngineState();
    sendEngineFrame();
}

void EngineECU::onSimTimeout()
{
    //chatGPT-generated to have a "realistic" simulation
/*
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    d_deltaTime = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;
    //qDebug() << "deltatime = " << d_deltaTime;
    updateEngineState();*/
}

void EngineECU::updateEngineState()
{
    float dt_sec = d_timer.interval() / 1000.0f; //ms to s

    // engine rpm
    float rpmTarget = IDLE_RPM + (d_pedal / 255.0f) * (MAX_RPM - IDLE_RPM);
    float rpmDelta = rpmTarget - d_rpm;
    //float maxRPMChange = ACCEL_GAIN * (d_pedal / 255.0f) * dt_sec;


    if (d_brake > 0.1f)
        rpmDelta -= (d_brake / 255.0f) * BRAKE_GAIN;

    if(d_pedal < 0.1f && d_brake < 0.1f)
        rpmDelta -= DECAY_GAIN;

    d_rpm += rpmDelta * SMOOTH_FACTOR * dt_sec;
    d_rpm = std::clamp(d_rpm,IDLE_RPM,MAX_RPM);

    float speedTarget = d_rpm * GEAR_RATIO;
    speedTarget -= (d_brake / 255.0f) * 12.0f; //coef decel BRAKE

    d_speed += (speedTarget - d_speed) * SMOOTH_FACTOR * dt_sec;
    if(d_speed < 0.0f) d_speed = 0.0f;
}

void EngineECU::sendEngineFrame()
{
    QByteArray data(8,0);

    uint16_t rpm = static_cast<uint16_t>(d_rpm);
    uint16_t speed = static_cast<uint16_t>(d_speed);
    uint8_t pedal = static_cast<uint8_t>(d_pedal);

    data[0] = static_cast<char>((rpm >> 8) & 0xFF);
    data[1] = static_cast<char>(rpm & 0xFF);
    data[2] = static_cast<char>(pedal);
    data[3] = static_cast<char>(75);
    data[4] = static_cast<char>((speed >> 8) & 0xFF);
    data[5] = static_cast<char>(speed & 0xFF);

    CANFrame frame(0x100,data);
    this->sendFrame(frame);
}

void EngineECU::receiveFrame(const CANFrame& frame)
{
    //brake pedal
    if(frame.getD_id() == 0x070 && frame.getD_dlc() == 8)
    {
        d_brake = static_cast<uint8_t>(frame.getD_data()[0]);
        d_brake_valid = frame.getD_data()[2];
        d_brake_switch = frame.getD_data()[3];
    }

    //gas pedal
    if(frame.getD_id() == 0x090 && frame.getD_dlc() == 8)
    {
        d_pedal = static_cast<uint8_t>(frame.getD_data()[0]);
        d_pedal_valid = frame.getD_data()[2];
    }
}


