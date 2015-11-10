import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

Item {
    id: widget
    x: 0
    y: 0
    height: 300
    width: 400

    property color colorPanel: Qt.rgba(0.9, 0.9, 1.0)
    property color colorBorder: "black"
    property int widthBorder: 2
    property int radiusBorder: 8

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

        repeater.itemAt(index).heightBar = 1 + value * (row.height - 1);
        repeater.itemAt(index).textBar = ("0" + label).slice(-2);
    }

    function setTime(value) {
        var h = Math.floor(value / 3600);
        var m = Math.floor((value % 3600) / 60);
        var s = Math.floor(value % 60);
        h = ("0" + h).slice(-2);
        m = ("0" + m).slice(-2);
        s = ("0" + s).slice(-2);
        rectTime.lineTime = "%1:%2:%3".arg(h).arg(m).arg(s);
    }

    function setLla(lat, lon, alt) {
        var la = Number(lat * 57.295779513).toFixed(4);
        var lo = Number(lon * 57.295779513).toFixed(4);
        var al = Number(alt).toFixed(1);

        rectTime.lineLat = "Ш:%1".arg(la);
        rectTime.lineLon = "Д:%1".arg(lo);
        rectTime.lineAlt = "В:%1".arg(al);
    }

    function setRadarItem(index, azm, elv) {
        var rr, xx, yy, isVisible;

        rr = 0.5 - elv / Math.PI;
        if (rr >= 0.0 && rr <= 0.5) {
            xx = rr * Math.cos(azm);
            yy = rr * Math.sin(azm);
            isVisible = true;
        }
        else {
            xx = 0.0;
            yy = 0.0;
            isVisible = false;
        }

        repRadar.itemAt(index).posX = xx;
        repRadar.itemAt(index).posY = yy;
        repRadar.itemAt(index).colorValue = diagram.colorInfLocked;//(Math.random() > 0.5) ? "green" : "yellow";
        repRadar.itemAt(index).isVisible = isVisible;

    }

    function setWorldLocation(lat, lon) {
        world.locX = 0.5 * lon / Math.PI;
        world.locY = -lat / Math.PI;
    }

    function setWorldSolution(lat, lon, alt, isVisible) {
        world.slvX = 0.5 * lon / Math.PI;
        world.slvY = -lat / Math.PI;
        world.slvVisible = isVisible;
        setLla(lat, lon, alt);
    }

    ColumnLayout {
        anchors.fill: parent
//        spacing: widget.radiusBorder
        anchors.margins: widget.radiusBorder

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: parent.height * 0.333
            anchors.margins: widget.radiusBorder

            property int itemCount: 3
            property int itemWidth: (width - spacing * itemCount) / itemCount

            spacing: widget.radiusBorder

            Rectangle {
                id: radar

                x: 0
                y: 0
                height: 10
                width: 10

                property int itemCount: 24
                property color colorNet: Qt.rgba(0.0, 0.0, 0.0, 1.0)

                border.color: widget.colorBorder
                border.width: widget.widthBorder
                radius: widget.radiusBorder
                color: widget.colorPanel

                Layout.fillWidth: true
                Layout.fillHeight: true

                Canvas {
                    id: canvas
                    readonly property real rscale0: 0.14644661
                    readonly property real rscale1: 1 - rscale0

                    anchors.fill: parent
                    anchors.margins: widget.radiusBorder

                    onPaint: {
                        var ctx = canvas.getContext('2d');
                        ctx.lineWidth = 1.0;
                        ctx.strokeStyle = radar.colorNet;
                        ctx.fillStyle = "white"
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
                        ctx.ellipse(width * 0.25, height * 0.25, width * 0.5, height * 0.5);
                        ctx.fill();
                        ctx.stroke();
                    }

                }

                Repeater {
                    id: repRadar
                    model: radar.itemCount
                    Rectangle {
                        property real posX: Math.random() - 0.5
                        property real posY: Math.random() - 0.5
                        property color colorValue: (Math.random() > 0.5) ? "green" : "yellow"
                        property bool isVisible: (Math.random() > 0.5)
                        x: canvas.x + (canvas.width  - width ) * 0.5 + posX * canvas.width
                        y: canvas.y + (canvas.height - height) * 0.5 + posY * canvas.height
                        width: canvas.width * 0.1
                        height: width
                        radius: width
                        color: colorValue
                        visible: isVisible
                    }
                }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: canvasWorld.requestPaint();//setRadarItem(Math.floor(Math.random() * 23), (Math.random() - 0.5) * Math.PI, 2.0 * Math.random() * Math.PI)
//                }
            }

            Rectangle {
                id: world

                x: 0
                y: 0
                height: 10
                width: 10

                Layout.fillWidth: true
                Layout.fillHeight: true

                border.color: widget.colorBorder
                border.width: widget.widthBorder
                radius: widget.radiusBorder
                color: widget.colorPanel

                property real locX: Math.random() - 0.5
                property real locY: Math.random() - 0.5
                property real slvX: Math.random() - 0.5
                property real slvY: Math.random() - 0.5
                property bool slvVisible: true//(Math.random() > 0.5)

                Image {
                    id: map
                    anchors.fill: parent
                    anchors.margins: widget.radiusBorder
                    smooth: true
                    source: "world.png"
                    visible: false
                }

                OpacityMask {
                    anchors.fill: map
//                    source: map
                    maskSource: map
                }

                Canvas {
                    id: canvasWorld
                    anchors.fill: parent
                    anchors.margins: widget.radiusBorder
                    onPaint: {
                        var ctx = canvasWorld.getContext('2d');
                        ctx.lineWidth = 1.0;
                        ctx.globalCompositeOperation = "xor";
                        ctx.strokeStyle = Qt.rgba(0.9, 0.0, 0.0, 0.8);//"transparency";//

                        ctx.beginPath();

                        ctx.moveTo(width * (world.locX + 0.5), 0     );
                        ctx.lineTo(width * (world.locX + 0.5), height);

                        ctx.moveTo(0    , height * (world.locY + 0.5));
                        ctx.lineTo(width, height * (world.locY + 0.5));

                        ctx.stroke();
                    }
                }

                Rectangle {
                    id: posPoint
                    width: parent.width * 0.1
                    height: width
                    radius: width
                    color: Qt.rgba(0.0, 0.9, 0.0, 0.8)

                    x: canvasWorld.x + (canvasWorld.width  - width ) * 0.5 + world.slvX * canvasWorld.width
                    y: canvasWorld.y + (canvasWorld.height - height) * 0.5 + world.slvY * canvasWorld.height
                    visible: world.slvVisible
                }

            }

            Rectangle {
                id: rectTime

                x: 0
                y: 0
                height: 10
                width: 10

                Layout.fillWidth: true
                Layout.fillHeight: true

                border.color: widget.colorBorder
                border.width: widget.widthBorder
                radius: widget.radiusBorder
                color: widget.colorPanel

                property string lineTime: "00:00:00"
                property string lineLat: "Ш:+0.0000"
                property string lineLon: "Д:+0.0000"
                property string lineAlt: "В:0.0"
                property real textScale: 0.0833
                property string textFont: "Consolas"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.leftMargin: parent.width * 0.1
                    spacing: -height * 0.25 + 1

                    Text {
                        id: textTime
                        font.family: rectTime.textFont
                        font.pointSize: rectTime.width * rectTime.textScale
                        text: rectTime.lineTime
                    }
                    Text {
                        font.family: rectTime.textFont
                        font.pointSize: rectTime.width * rectTime.textScale
                        text: rectTime.lineLat
                    }
                    Text {
                        font.family: rectTime.textFont
                        font.pointSize: rectTime.width * rectTime.textScale
                        text: rectTime.lineLon
                    }
                    Text {
                        font.family: rectTime.textFont
                        font.pointSize: rectTime.width * rectTime.textScale
                        text: rectTime.lineAlt
                    }
                }

            }
        }

        Rectangle {
            id: diagram
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: parent.height * 0.333
            border.color: widget.colorBorder
            border.width: widget.widthBorder
            radius: widget.radiusBorder
            color: widget.colorPanel

            property color colorNotLocked: Qt.rgba(1.0, 1.0, 1.0, 0.0)
            property color colorDllLocked: Qt.rgba(0.5, 0.5, 0.5, 1.0)
            property color colorPllLocked: Qt.rgba(0.9, 0.9, 0.0, 1.0)
            property color colorInfLocked: Qt.rgba(0.0, 0.9, 0.0, 1.0)

            property int stateNotLocked: 0
            property int stateDllLocked: 1
            property int statePllLocked: 3
            property int stateInfLocked: 7

            property int channelCount: 8
            property int channelSpacing: 1 + 0.05 * width / channelCount

            RowLayout {
                id: row
                spacing: diagram.channelSpacing
                anchors.bottom: parent.bottom
                anchors.fill: parent
                anchors.margins: widget.radiusBorder
                Repeater {
                    id: repeater
                    model: diagram.channelCount
                    property real textScale: 0.25
                    property string textFont: "Consolas"
                    anchors.fill: parent
                    Rectangle{
                        x: 0
                        y: 0
                        height: 10
                        width: 10
                        property color colorBar: diagram.colorInfLocked
                        property int heightBar: row.height / (index + 1)
                        property string textBar: "00"
                        Layout.fillWidth: true
                        Layout.fillHeight: false
                        Layout.minimumHeight: 1
                        Layout.maximumHeight: row.height
                        Layout.preferredHeight: heightBar
                        Layout.minimumWidth: 1
                        anchors.bottom: parent.bottom
                        color: colorBar
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.bottom
                            text: parent.textBar
                            font.family: repeater.textFont
                            font.pointSize: Math.ceil(parent.width * repeater.textScale)
                        }
                    }
                }
            }
        }

        Rectangle {
            id: serviceWindow
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: parent.height * 0.333
            border.color: widget.colorBorder
            border.width: widget.widthBorder
            radius: widget.radiusBorder
            color: widget.colorPanel
        }
    }

    Timer {
        interval: 1000;
        running: true;
        repeat: true
        onTriggered: {
            canvas.requestPaint();
            canvasWorld.requestPaint();
        }
    }

}
