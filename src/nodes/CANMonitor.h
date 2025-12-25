#ifndef CANMONITOR_H
#define CANMONITOR_H

#include <QAbstractTableModel>
#include "can/CANNode.h"
#include "can/CANFrame.h"

class CANMonitor : public QAbstractTableModel, public CANNode
{
    Q_OBJECT
    Q_PROPERTY(bool lastByIdMode READ lastByIdMode WRITE setLastByIdMode NOTIFY modeChanged)

public:

    bool lastByIdMode() const;
    void setLastByIdMode(bool enabled);

    enum Column{
        Id,
        Dlc,
        Data,
        Rtr,
        Ext,
        Time,
        ColumnCount
    };

    enum class DisplayMode{
        Trace,
        LastById
    };

    explicit CANMonitor(CANBus* bus, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:
    void modeChanged();

protected:

    void receiveFrame(const CANFrame& frame) override;

private:
    DisplayMode d_mode = DisplayMode::Trace;

    QList<CANFrame> d_frames;
    QMap<uint32_t, CANFrame> d_lastFrames;
    QSet<uint32_t> d_changedIds;
};

#endif // CANMONITOR_H
