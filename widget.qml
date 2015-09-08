import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2


Item {
    id: widget
    x: 0
    y: 0
    width: 100
    height: 100

    function setChannelState(index, state, label, value) {
        switch(state) {
        case diagram.stateDllLocked:
            repeater.itemAt(index).colorBar = diagram.colorDllLocked;
            break;

        case diagram.statePllLocked:
            repeater.itemAt(index).colorBar = diagram.colorPllLocked;
            break;

        case diagram.stateInfLocked:
            repeater.itemAt(index).colorBar = diagram.colorInfLocked;
            break;
        default:
        case diagram.stateNotLocked:
            repeater.itemAt(index).colorBar = diagram.colorNotLocked;
            break;
        }

        repeater.itemAt(index).heightBar = value * row.height;
        repeater.itemAt(index).textBar = label;
    }

    Item {
        id: diagram
        anchors.fill: parent
        width: parent.width
        height: parent.height

        property color colorNotLocked: Qt.rgba(1.0, 1.0, 1.0, 0.0)
        property color colorDllLocked: Qt.rgba(0.5, 0.5, 0.5, 1.0)
        property color colorPllLocked: Qt.rgba(0.9, 0.9, 0.0, 1.0)
        property color colorInfLocked: Qt.rgba(0.0, 0.9, 0.0, 1.0)

        property int stateNotLocked: 0
        property int stateDllLocked: 1
        property int statePllLocked: 2
        property int stateInfLocked: 3

        property int channelCount: 8
        property int channelWidth: (width - channelSpacing * channelCount) / channelCount
        property int channelSpacing: 1 + 0.05 * width / channelCount

        Rectangle {
            id: amps
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            anchors.fill: parent
            antialiasing: true
            Row {
                id: row
                x: 1 + diagram.channelSpacing * 0.5
                width: parent.width
                height: parent.height
                spacing: diagram.channelSpacing
                anchors.bottom: parent.bottom
                Repeater {
                    id: repeater
                    model: diagram.channelCount
                    Rectangle{
                        property color colorBar: diagram.colorInfLocked
                        property int heightBar: parent.height / (index + 1)
                        property string textBar: "00"
                        width: diagram.channelWidth
                        height: heightBar
                        anchors.bottom: parent.bottom
                        color: colorBar
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.bottom
                            text: parent.textBar
                            font.pointSize: parent.width * 0.25
                        }
                    }
                }
            }
        }
    }

    Item {
        id: radar
        property int itemCount: 32
        property color colorNet: Qt.rgba(0.0, 0.0, 0.5, 0.5)
        x: 200
        y: 31
        width: 100
        height: 100
        antialiasing: true

        Canvas {
            id: canvas
            readonly property real rscale0: 0.14644661
            readonly property real rscale1: 1 - rscale0
            anchors.fill: parent
            onPaint: {
                var ctx = canvas.getContext('2d');
                ctx.lineWidth = 1.0;
                ctx.strokeStyle = radar.colorNet;

                ctx.beginPath();

                ctx.moveTo(width * rscale0, height * rscale0);
                ctx.lineTo(width * rscale1, height * rscale1);

                ctx.moveTo(width * rscale1, height * rscale0);
                ctx.lineTo(width * rscale0, height * rscale1);

                ctx.moveTo(width * 0.5, 0     );
                ctx.lineTo(width * 0.5, height);

                ctx.moveTo(0    , height * 0.5);
                ctx.lineTo(width, height * 0.5);

                ctx.ellipse(1, 1, width - 2, height - 2);
                ctx.ellipse(width * 0.25, width * 0.25, width * 0.5, height * 0.5);

                ctx.stroke();
            }
        }

        Repeater {
            id: repRadar
            model: radar.itemCount
            Rectangle {
                x: (radar.width - width) * 0.5 + (Math.random() - 0.5) * radar.width * 0.707
                y: (radar.height - height) * 0.5 + (Math.random() - 0.5) * radar.height * 0.707
                width: radar.width * 0.1
                height: width
                radius: width
                color: "green"
            }
        }
    }

    Item {
        id: world
        x: 0
        y: 0
        width: 100
        height: 50
        antialiasing: true
        Image {
            id: map
            source: "world.png"
            anchors.fill: parent
        }
    }
}
