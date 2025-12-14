#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../can/CANNode.h"
#include "QDebug"

class DashBoard : public CANNode
{

public:
    explicit DashBoard(CANBus* bus);

    void receiveFrame(const CANFrame& frame) override;
    QString decodeData(const QByteArray& data);

};

#endif // DASHBOARD_H
