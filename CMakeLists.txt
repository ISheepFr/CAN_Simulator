cmake_minimum_required(VERSION 3.14)

project(CAN_SIM LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(CAN_SIM
  src/main.cpp
  src/can/CANFrame.h src/can/CANFrame.cpp
  src/can/CANNode.h src/can/CANNode.cpp
  src/can/CANBus.h src/can/CANBus.cpp
  src/nodes/DashBoard.h src/nodes/DashBoard.cpp


)
target_link_libraries(CAN_SIM Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS CAN_SIM
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
