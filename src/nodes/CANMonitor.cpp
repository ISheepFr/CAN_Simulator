#include "CANMonitor.h"

CANMonitor::CANMonitor(CANBus* bus, QObject *parent):
    QAbstractTableModel{parent},
    CANNode{"CANMonitor",bus}
{

}

bool CANMonitor::lastByIdMode() const
{
    return d_mode == DisplayMode::LastById;
}
void CANMonitor::setLastByIdMode(bool enabled)
{
    DisplayMode newMode = enabled ? DisplayMode::LastById
                                  : DisplayMode::Trace;

    if (newMode == d_mode)
        return;

    beginResetModel();
    d_mode = newMode;
    d_changedIds.clear();
    endResetModel();

    emit modeChanged();
}

int CANMonitor::rowCount(const QModelIndex &parent) const
{
    if(d_mode == DisplayMode::Trace)
    {
        return d_frames.size();
    }
    else
    {
        return d_lastFrames.size();
    }

}

int CANMonitor::columnCount(const QModelIndex &parent) const
{
    return ColumnCount;
}

QVariant CANMonitor::data(const QModelIndex &index, int role) const
{
    const CANFrame& f =
        (d_mode == DisplayMode::Trace)
            ? d_frames[index.row()]
            : d_lastFrames.values()[index.row()];

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
    if(d_mode == DisplayMode::Trace)
    {
        int row = d_frames.size();
        beginInsertRows(QModelIndex(),row,row);
        d_frames.append(frame);
        endInsertRows();
    }

    else
    {
        uint32_t id = frame.getD_id();
        if(d_lastFrames.contains(id))
        {
            if(d_lastFrames[id].getD_data() != frame.getD_data())
            {
                d_lastFrames[id] = frame;
                d_changedIds.insert(id);

                int row = d_lastFrames.keys().indexOf(id);
                emit dataChanged(index(row,0),index(row,columnCount()-1));
            }
        }
        else
        {
            beginInsertRows(QModelIndex(), d_lastFrames.size(),d_lastFrames.size());
            d_lastFrames.insert(id,frame);
            endInsertRows();
        }
    }
}
