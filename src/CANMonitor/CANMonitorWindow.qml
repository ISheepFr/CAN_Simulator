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

            ScrollBar.vertical: ScrollBar {
                id: tableVerticalBar
                policy: ScrollBar.AlwaysOn
            }

            columnWidthProvider: function (column) {
                switch (column) {
                case 0: return 80    // Id
                case 1: return 50    // Dlc
                case 2: return 260   // Data
                case 3: return 50    // Rtr
                case 4: return 50    // Ext
                case 5: return 120   // Time
                default: return 100
                }
            }

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
        Connections {
                target: canmonitor

                function onRowsInserted(parent, first, last) {
                    if(!canmonitor.lastByIdMode){Qt.callLater(function () {
                                    table.contentY = table.contentHeight - table.height
                                })}
                }
            }


        RowLayout {
            Button {
                text: canmonitor.lastByIdMode
                      ? "Mode Trace"
                      : "Mode Last by ID"

                onClicked: {
                    canmonitor.lastByIdMode = !canmonitor.lastByIdMode
                }
            }
        }
    }



}
