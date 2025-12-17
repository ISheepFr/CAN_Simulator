#ifndef CANMONITOR_H
#define CANMONITOR_H

#include <QAbstractTableModel>
#include "can/CANNode.h"
#include "can/CANFrame.h"

class CANMonitor : public QAbstractTableModel, public CANNode
{
    Q_OBJECT

public:

    enum Column{
        Id,
        Dlc,
        Data,
        Rtr,
        Ext,
        Time,
        ColumnCount
    };

    explicit CANMonitor(CANBus* bus, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected:

    void receiveFrame(const CANFrame& frame) override;

private:

    QList<CANFrame> d_frames;
    QMap<uint32_t, CANFrame> d_lastById;
};

#endif // CANMONITOR_H
