#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>
#include <QList>

class CANNode;
class CANFrame;

class CANBus : public QObject
{
    Q_OBJECT

public:
    explicit CANBus(QObject *parent = nullptr);

    void attachNode(CANNode* node);
    void broadcastFrame(const CANFrame& frame, CANNode* sender);

    QList<CANNode *> getD_nodes() const;

private:
    QList<CANNode*> d_nodes;

};

#endif // CANBUS_H
