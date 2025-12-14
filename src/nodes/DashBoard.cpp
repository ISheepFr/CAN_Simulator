#include "DashBoard.h"

DashBoard::DashBoard(CANBus* bus):CANNode{"Dashboard",bus}
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

    qDebug() << decodeData(frame.getD_data());

}

QString DashBoard::decodeData(const QByteArray& data)
{
    uint16_t rpm = (static_cast<uint8_t>(data[0]) << 8) | (static_cast<uint8_t>(data[1]));
    uint8_t temp = (static_cast<uint8_t>(data[2]));
    uint8_t load = (static_cast<uint8_t>(data[3]));

    return QString("RPM=%1 | TEMP=%2°C | LOAD=%3")
            .arg(rpm)
            .arg(temp)
            .arg(load);
}
