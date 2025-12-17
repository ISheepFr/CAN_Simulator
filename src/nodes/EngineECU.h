#ifndef ENGINEECU_H
#define ENGINEECU_H


#include "../can/CANNode.h"
#include <QTimer>

class EngineECU : public QObject, public CANNode
{
    Q_OBJECT
public:

    explicit EngineECU(CANBus* bus, int periodMS = 100);
    void receiveFrame(const CANFrame& frame) override;

private slots:
    void sendEngineFrame();

private:
    QTimer d_timer;
    uint16_t d_rpm;
    uint8_t d_temp;
    uint8_t d_load;


};

#endif // ENGINEECU_H
