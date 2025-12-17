#ifndef CANNODE_H
#define CANNODE_H

#include <QObject>
#include <QString>
#include "CANFrame.h"

class CANBus;

class CANNode //: public QObject
{
    //Q_OBJECT
public:
    explicit CANNode(const QString& name, CANBus* bus);
    virtual ~CANNode() = default;

    void sendFrame(const CANFrame& frame);
    virtual void receiveFrame(const CANFrame& frame)=0;

    QString getD_name() const;

private:
    QString d_name;

protected:
    CANBus* a_bus;



};

#endif // CANNODE_H
