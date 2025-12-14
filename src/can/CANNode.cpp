#include "CANNode.h"
#include "CANBus.h"

CANNode::CANNode(const QString& name, CANBus* bus)
    :d_name{name},a_bus{bus}
{

}

void CANNode::sendFrame(const CANFrame &frame)
{
    if(a_bus != nullptr)
    {
        a_bus->broadcastFrame(frame,this);
    }
}

QString CANNode::getD_name() const
{
    return d_name;
}
