#include "DashBoard.h"

DashBoard::DashBoard(CANBus* bus):CANNode("Dashboard",bus)
{

}

void DashBoard::receiveFrame(const CANFrame& frame)
{
    qDebug() << "[Dashboard] Received ID:"
             << QString("0x%1").arg(frame.getD_id(),0,16)
             << "DLC:" << frame.getD_dlc()
             << "DATA:" << frame.getD_data().toHex()
             << "RTR:" << frame.getD_isRTR()
             << "EXT:" << frame.getD_isExtended();
}
