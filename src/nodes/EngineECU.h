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
    QTimer d_timer;
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


};

#endif // ENGINEECU_H
