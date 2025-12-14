#include <QCoreApplication>
#include <QDebug>
#include "can/CANFrame.h"

void print_frame(CANFrame *frame)
{
    qDebug() << "ID:" << frame->getD_id()
             << "DLC:" << frame->getD_dlc()
             << "DATA:" << frame->getD_data().toHex()
             << "TIME:" << frame->getD_timestamp();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CANFrame *f_0x123 = new CANFrame(0x123,QByteArray::fromHex("11223344"));
    CANFrame *f_0x012 = new CANFrame(0x12,QByteArray::fromHex("112233"));

    print_frame(f_0x123);
    print_frame(f_0x012);

    return a.exec();
}
