#include <QCoreApplication>
#include <QDebug>

#include "can/CANFrame.h"
#include "can/CANNode.h"
#include "can/CANBus.h"
#include "nodes/DashBoard.h"

class DummyNode : public CANNode
{
public:
    DummyNode(CANBus* bus): CANNode("dummy",bus){}
    void receiveFrame(const CANFrame& frame) override
    {
        qDebug() << "[DummyNode] Received ID:"
                 << QString("0x%1").arg(frame.getD_id(),0,16)
                 << "DLC:" << frame.getD_dlc()
                 << "DATA:" << frame.getD_data().toHex()
                 << "RTR:" << frame.getD_isRTR()
                 << "EXT:" << frame.getD_isExtended();
    }
};

class DummyNode_2 : public CANNode
{
public:
    DummyNode_2(CANBus* bus): CANNode("dummy2",bus){}
    void receiveFrame(const CANFrame& frame) override
    {
        qDebug() << "[DummyNode_2] Received ID:"
                 << QString("0x%1").arg(frame.getD_id(),0,16)
                 << "DLC:" << frame.getD_dlc()
                 << "DATA:" << frame.getD_data().toHex()
                 << "RTR:" << frame.getD_isRTR()
                 << "EXT:" << frame.getD_isExtended();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CANBus my_can_bus;

    DummyNode my_dummy_node(&my_can_bus);
    DummyNode_2 my_dummy_node_2(&my_can_bus);

    DashBoard my_dashboard(&my_can_bus);

    my_can_bus.attachNode(&my_dashboard);
    my_can_bus.attachNode(&my_dummy_node);
    my_can_bus.attachNode(&my_dummy_node_2);

    CANFrame *f_0x123 = new CANFrame(0x123,QByteArray::fromHex("11223344"));
    CANFrame *f_0x012 = new CANFrame(0x12,QByteArray::fromHex("112233"),true,true);

    my_dummy_node.sendFrame(*f_0x123);
    my_dashboard.sendFrame(*f_0x012);

    return a.exec();
}
