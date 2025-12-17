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

    switch (index.column()) {
    case Id: return QString("0x%1").arg(f.getD_id(),0,16);
    case Dlc: return f.getD_dlc();
    case Data: return f.getD_data().toHex();
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
    beginInsertRows(QModelIndex(),d_frames.size(),d_frames.size());
    d_frames.append(frame);
    endInsertRows();

    d_lastById.insert(frame.getD_id(),frame);

}
