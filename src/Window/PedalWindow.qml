import QtQuick
import QtQuick.Controls
Window {
    width: 300
    height: 200
    visible: true
    title: "Pedal ECU"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Pedal: " + Math.round((pedal.pedal*100)/255) + "%"
            font.pixelSize: 20
        }

        Slider {
            from: 0
            to: 255
            value: pedal.pedal
            onValueChanged: pedal.pedal = value
        }

        Text {
            text: "BRAKE: " + Math.round((brake.brake*100)/255) + "%"
            font.pixelSize: 20
        }

        Slider {
            from: 0
            to: 255
            value: brake.brake
            onValueChanged: brake.brake = value
        }

        Rectangle{
            color: "red"
            width: 100
            height: 100

            property bool pressed: false

            Timer {
                    id: pedalTimer
                    interval: 10
                    repeat: true
                    running: true
                    onTriggered: {
                        if (parent.pressed) {
                            //brake.brake = Math.min(brake.brake + 1, 255)
                        } else {
                            //brake.brake = Math.max(brake.brake - 1, 0)
                        }
                    }
                }


            Button{

                anchors.fill: parent
                autoRepeat: true
                onPressed: parent.pressed = true
                onReleased: parent.pressed = false

            }
        }
    }
}

