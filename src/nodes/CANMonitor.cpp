#include "CANMonitor.h"

CANMonitor::CANMonitor(CANBus* bus, QObject *parent):
    QAbstractTableModel{parent},
    CANNode{"CANMonitor",bus}
{

}

int CANMonitor::rowCount(const QModelIndex &parent) const
{
    return d_frames.size();
}

int CANMonitor::columnCount(const QModelIndex &parent) const
{
    return ColumnCount;
}

QVariant CANMonitor::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    const auto& f = d_frames[index.row()];

    /*        Id,
        Dlc,
        Data,
        Rtr,
        Ext,
        Time,
        ColumnCount*/

    QString hex,result;

    switch (index.column()) {
    case Id: return QString("0x%1").arg(f.getD_id(),0,16);
    case Dlc: return f.getD_dlc();
    case Data:
        hex = f.getD_data().toHex().toLower();

        for (int i = 0; i < hex.length(); i += 2) {
            result += hex.mid(i, 2) + " ";
        }

        return result.trimmed();
        //return f.getD_data().toHex();
    case Rtr: return f.getD_isRTR();
    case Ext: return f.getD_isExtended();
    case Time: return f.getD_timestamp().toString("hh:mm:ss.zzz");

    default:
        return{};
    }

}

QVariant CANMonitor::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal)
        return {};

    static const QString headers[] = {"Id","Dlc","Data","Rtr","Ext","Time"};

    return headers[section];
}


void CANMonitor::receiveFrame(const CANFrame &frame)
{
    int row = d_frames.size();
    beginInsertRows(QModelIndex(),row,row);
    d_frames.append(frame);
    endInsertRows();

    d_lastById.insert(frame.getD_id(),frame);
}
