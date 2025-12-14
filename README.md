# CAN Simulator

**CAN Simulator** is a simple C++ project designed to simulate **CAN (Controller Area Network)** communication. It helps understand how CAN messages are exchanged on a CAN bus.
I'm using QT, C++ and QML.

## 🚀 Overview

This project provides a lightweight CAN simulation environment built around three core classes:

- `CANFrame` – represents a CAN message
- `CANNode` – represents a node connected to the CAN bus like a Car Dashboard or EngineECU
- `CANBus` – simulates the CAN bus itself and message propagation

## 📦 Features

- Basic CAN frame simulation
- Multiple nodes connected to a single CAN bus
- Message broadcasting logic
- Simple and extensible C++ architecture
- Built using **CMake**
  
## 🛠️ Project Structure
```text
CAN_Simulator/
├── src/
│   ├── can/
│   │   ├── CANFrame.*      # CAN frame representation
│   │   ├── CANNode.*       # CAN node logic
│   │   ├── CANBus.*        # CAN bus simulation
│   ├── nodes/
│   │   ├── EngineECU.*     # RPM, temperature and load
│   │   ├── Dashboard.*     # Instrument cluster simulation
│   ├── main.cpp
│   ├── main.qml
├── CMakeLists.txt
```
## 📝 TODO

- Improve the dashboard with more vehicle information, similar to a real car instrument cluster (speed, indicators, warnings, etc.).
- Simulate additional CAN nodes such as:
  - `AcceleratorPedalECU`
  - `SpeedECU`
  - Turn signal / indicator ECU  
- Add dedicated QML windows for specific ECUs (e.g. an Accelerator Pedal window to simulate pedal press and release).
- Create a real-time CAN frame monitor (debug view) displaying all frames circulating on the bus, using a table-based view (e.g. `QTableView`).
