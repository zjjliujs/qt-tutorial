import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: page
        width: Window.width
        height: Window.height
        color: "lightgray"

        Text {
            id: helloText
            text: "Hello world!"
            y: 130
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
        }
    }
}
