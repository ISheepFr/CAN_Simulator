#include "CANBus.h"
#include "CANNode.h"
#include "CANFrame.h"

#include <QDebug>

CANBus::CANBus(QObject *parent)
    : QObject{parent}
{

}

void CANBus::attachNode(CANNode *node)
{
    if(!d_nodes.contains(node))
    {
        d_nodes.append(node);
    }
}

void CANBus::broadcastFrame(const CANFrame &frame, CANNode *sender)
{
    qDebug() << "";
    qDebug() << "[CANBus] Broadcast ID:"
             << QString("0x%1").arg(frame.getD_id(),0,16)
             << "DLC:" << frame.getD_dlc()
             << "RTR:" << frame.getD_isRTR()
             << "EXT:" << frame.getD_isExtended();

    for(CANNode* node : d_nodes)
    {
        if(node != sender)
        {
            node->receiveFrame(frame);
        }
    }

}

QList<CANNode *> CANBus::getD_nodes() const
{
    return d_nodes;
}
