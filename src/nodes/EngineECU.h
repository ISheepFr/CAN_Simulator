#ifndef ENGINEECU_H
#define ENGINEECU_H


#include "../can/CANNode.h"
#include <QTimer>

class EngineECU : public QObject, public CANNode
{
    Q_OBJECT
public:

    explicit EngineECU(CANBus* bus, int periodMS = 100, int simPeriodMS = 1000);
    void receiveFrame(const CANFrame& frame) override;

private slots:
    void onTimeout();
    void onSimTimeout();

    void sendEngineFrame();
    void updateEngineState();

private:
    /*QTimer d_timer;
    QTimer d_simTimer;
    qreal d_deltaTime = 0.01;
    qint64 lastTime;

    uint16_t d_rpm = 800;
    uint16_t d_rpm_target = 800;

    uint16_t d_speed = 0;
    uint16_t d_speed_target = 0;

    uint8_t d_temp;
    uint8_t d_load;

    uint8_t d_pedal = 0;
    bool d_pedal_valid = false;

    uint8_t d_brake = 0;
    bool d_brake_valid = false;
    bool d_brake_switch;*/

    float d_rpm = 800.0f;
    float d_pedal = 0.0f;
    float d_brake = 0.0f;
    float d_speed = 0.0f;
    uint8_t d_temp;
    uint8_t d_load;

    bool d_pedal_valid = false;
    bool d_brake_valid = false;
    bool d_brake_switch;

    const float IDLE_RPM = 0;//800.0f;
    const float MAX_RPM  = 8000.0f;

    const float ACCEL_GAIN = 2000.0f;
    const float BRAKE_GAIN = 4000.0f;
    const float DECAY_GAIN = 1.0f;
    const float COAST_DECEL = 1.5f;

    const float SMOOTH_FACTOR = 0.4f;

    const float GEAR_RATIO = 0.03f;

    QTimer d_timer;



};

#endif // ENGINEECU_H
