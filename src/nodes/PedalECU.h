#ifndef PEDALECU_H
#define PEDALECU_H

#include "../can/CANNode.h"
#include <QObject>
#include <QTimer>

class PedalECU: public QObject, public CANNode
{
    Q_OBJECT
    Q_PROPERTY(int pedal READ pedal WRITE setPedal NOTIFY pedalChanged FINAL)


public:
    explicit PedalECU(CANBus* bus,int periodMS = 100);

    void receiveFrame(const CANFrame& frame) override;

    int pedal() const;
    void setPedal(int value);

signals:
    void pedalChanged();

private slots:
    void sendPedalFrame();

private:
    uint8_t d_pedal = 0; //0 - 100%
    QTimer d_timer;

};

#endif // PEDALECU_H
