import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 500
    height: 300
    title: "CAN Dashboard"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "SPEED: " + dashboard.speed
            font.pixelSize: 30
        }

        Text {
            text: "RPM: " + dashboard.rpm
            font.pixelSize: 28
        }

        Text {
            text: "Température: " + dashboard.temp + " °C"
            font.pixelSize: 22
        }

        Text {
            text: "Charge: " + Math.round(dashboard.load * 100 / 255) + " %"
            font.pixelSize: 22
        }
    }

}
