#ifndef CANFRAME_H
#define CANFRAME_H

#include <cstdint>
#include <QByteArray>
#include <QDateTime>

class CANFrame
{
public:
    CANFrame(uint32_t id, const QByteArray& data);

    uint32_t getD_id() const;
    bool getD_isRTR() const;
    uint8_t getD_dlc() const;
    QByteArray getD_data() const;
    QDateTime getD_timestamp() const;

private:
    uint32_t d_id; //both formats 11 and 29 bits
    bool d_isRTR; //remote transmission request
    uint8_t d_dlc; //data length code
    QByteArray d_data; // max 8 Bytes

    QDateTime d_timestamp;

};

#endif // CANFRAME_H
