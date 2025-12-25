cmake_minimum_required(VERSION 3.14)

project(CAN_SIM LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
)

qt_add_executable(CAN_SIM
  src/main.cpp
  src/can/CANFrame.h src/can/CANFrame.cpp
  src/can/CANNode.h src/can/CANNode.cpp
  src/can/CANBus.h src/can/CANBus.cpp
  src/nodes/DashBoard.h src/nodes/DashBoard.cpp
  src/nodes/EngineECU.h src/nodes/EngineECU.cpp
  src/nodes/CANMonitor.h src/nodes/CANMonitor.cpp
  src/nodes/PedalECU.h src/nodes/PedalECU.cpp
)

qt_add_qml_module(CAN_SIM
    URI CanDashboard
    VERSION 1.0
    QML_FILES
        src/main.qml
        src/CANMonitor/CANMonitorWindow.qml
        src/Window/PedalWindow.qml
        SOURCES src/nodes/BrakeECU.h src/nodes/BrakeECU.cpp
)


#target_link_libraries(CAN_SIM Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(CAN_SIM PRIVATE
    src
)

target_link_libraries(CAN_SIM PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

#include(GNUInstallDirs)
#install(TARGETS CAN_SIM
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

