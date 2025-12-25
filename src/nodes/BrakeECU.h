#ifndef BRAKEECU_H
#define BRAKEECU_H

#include "../can/CANNode.h"
#include <QObject>
#include <QTimer>

class BrakeECU: public QObject, public CANNode
{
    Q_OBJECT
    Q_PROPERTY(int brake READ brake WRITE setBrakePressure NOTIFY brakeChanged FINAL)

public:

    explicit BrakeECU(CANBus* bus,int periodMS = 100);

    void receiveFrame(const CANFrame& frame) override;

    int brake() const;
    void setBrakePressure(int value);

signals:
    void brakeChanged();

private slots:
    void sendBrakeFrame();

private:
    uint8_t d_brake = 0;
    QTimer d_timer;

};

#endif // BRAKEECU_H
