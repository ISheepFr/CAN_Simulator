//#include <QCoreApplication>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QDebug>

#include "can/CANFrame.h"
#include "can/CANNode.h"
#include "can/CANBus.h"
#include "nodes/DashBoard.h"
#include "nodes/EngineECU.h"
#include "nodes/PedalECU.h"
#include "nodes/BrakeECU.h"

#include "nodes/CANMonitor.h"

#include <QByteArray>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QGuiApplication a(argc,argv);

    CANBus my_can_bus;

    DashBoard my_dashboard(&my_can_bus);

    EngineECU my_engine_ecu(&my_can_bus,10,10);
    PedalECU my_pedal_ecu(&my_can_bus,10);
    BrakeECU my_brake_ecu(&my_can_bus,10);

    CANMonitor my_can_monitor(&my_can_bus);

    my_can_bus.attachNode(&my_dashboard);

    my_can_bus.attachNode(&my_engine_ecu);
    my_can_bus.attachNode(&my_pedal_ecu);
    my_can_bus.attachNode(&my_brake_ecu);

    my_can_bus.attachNode(&my_can_monitor);

    QQmlApplicationEngine engineQml;
    engineQml.rootContext()->setContextProperty("dashboard", &my_dashboard);
    engineQml.rootContext()->setContextProperty("canmonitor", &my_can_monitor);
    engineQml.rootContext()->setContextProperty("pedal", &my_pedal_ecu);
    engineQml.rootContext()->setContextProperty("brake", &my_brake_ecu);


    engineQml.load(QUrl(QStringLiteral("qrc:/CanDashboard/src/main.qml")));
    engineQml.load(QUrl(QStringLiteral("qrc:/CanDashboard/src/CANMonitor/CANMonitorWindow.qml")));
    engineQml.load(QUrl(QStringLiteral("qrc:/CanDashboard/src/Window/PedalWindow.qml")));



    //CANFrame f_0x123 = CANFrame(0x123,QByteArray::fromHex("11223344"));
    //CANFrame f_0x012 = CANFrame(0x12,QByteArray::fromHex("112233"),true,true);

    return a.exec();
}
