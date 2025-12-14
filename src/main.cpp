#include <QCoreApplication>
#include <QDebug>

#include "can/CANFrame.h"
#include "can/CANNode.h"

class DummyNode : public CANNode
{
public:
    DummyNode(CANBus* bus): CANNode("dummy",bus){}
    void receiveFrame(const CANFrame& frame) override
    {
        qDebug() << "[dummynode] Received ID:" << frame.getD_id();
    }
};

void print_frame(CANFrame *frame)
{
    qDebug() << "ID:" << frame->getD_id()
             << "DLC:" << frame->getD_dlc()
             << "DATA:" << frame->getD_data().toHex()
             << "TIME:" << frame->getD_timestamp()
             << "EXTENDED:" << frame->getD_isExtended()
             << "EXTENDED:" << frame->getD_isRTR();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DummyNode node(nullptr);

    CANFrame *f_0x123 = new CANFrame(0x123,QByteArray::fromHex("11223344"));
    CANFrame *f_0x012 = new CANFrame(0x12,QByteArray::fromHex("112233"),true,true);

    print_frame(f_0x123);
    print_frame(f_0x012);

    node.sendFrame(*f_0x123);

    return a.exec();
}
