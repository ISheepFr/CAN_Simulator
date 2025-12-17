import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    title: "CAN Monitor"
    width: 900
    height: 450
    visible: true

    ColumnLayout {
        anchors.fill: parent

        HorizontalHeaderView {
            syncView: table
            model: canmonitor
        }

        TableView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: canmonitor
            clip: true

            delegate: Rectangle {
                implicitHeight: 28
                implicitWidth: 120
                border.color: "#ddd"

                Text {
                    anchors.centerIn: parent
                    text: model.display
                    font.pixelSize: 12
                }
            }
        }

        /*Rectangle{
            anchors.fill: parent
            id: rec
            color: "red"
            width: 100
            height: 100

        }*/
    }


}
