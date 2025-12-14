#include "CANFrame.h"

CANFrame::CANFrame(uint32_t id, const QByteArray& data): d_id{id},d_data{data},d_dlc(static_cast<uint8_t>(data.size())),d_timestamp(QDateTime::currentDateTime())
{

}

uint32_t CANFrame::getD_id() const
{
    return d_id;
}

bool CANFrame::getD_isRTR() const
{
    return d_isRTR;
}

uint8_t CANFrame::getD_dlc() const
{
    return d_dlc;
}

QByteArray CANFrame::getD_data() const
{
    return d_data;
}

QDateTime CANFrame::getD_timestamp() const
{
    return d_timestamp;
}
