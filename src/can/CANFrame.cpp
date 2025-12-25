#include "CANFrame.h"
CANFrame::CANFrame()
{

}
CANFrame::CANFrame(uint32_t id, const QByteArray& data, bool isExtended, bool isRTR):
    d_id{id},
    d_data{data},
    d_dlc(static_cast<uint8_t>(data.size())),
    d_timestamp(QDateTime::currentDateTime()),
    d_isExtended{isExtended},
    d_isRTR{isRTR}
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

bool CANFrame::getD_isExtended() const
{
    return d_isExtended;
}
