#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../can/CANNode.h"
#include "QDebug"

class DashBoard : public CANNode
{
    Q_OBJECT
    Q_PROPERTY(int rpm READ getD_rpm NOTIFY engineDataChanged)
    Q_PROPERTY(int temp READ getD_temp NOTIFY engineDataChanged)
    Q_PROPERTY(int load READ getD_load NOTIFY engineDataChanged)

public:
    explicit DashBoard(CANBus* bus);
    void receiveFrame(const CANFrame& frame) override;

    int getD_rpm() const;
    int getD_temp() const;
    int getD_load() const;

private:

    //QString decodeData(const QByteArray& data);
    void decodeEngineData(const QByteArray& data);

    int d_rpm = 0;
    int d_temp = 0;
    int d_load = 0;

signals:
    void engineDataChanged();

};

#endif // DASHBOARD_H
