import QtQuick 2.2
import QtQuick.Layouts 1.1

Item {
    id: root
    width: ListView.view.width
    height: 24
    property alias text: label.text
    property alias number: num.text
    property alias color: counter.color
    property alias parameter: params.text
    signal clicked()
    signal remove()

    Rectangle {
        color: "#66ffffff"
        anchors.fill: parent
        opacity: 1
        border.color: Qt.darker(color)
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        Item {
            Layout.minimumHeight: 0
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: false
            Layout.minimumWidth: 20
            Rectangle {
                id: counter
                anchors.fill: parent
                opacity: 1
            }
            Text {
                id: num
                color: "#ffffff"
                anchors.rightMargin: 5
                textFormat: Text.PlainText
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                anchors.fill: parent
            }
        }
        Item {
            width: 100
            Layout.fillWidth: false
            Layout.fillHeight: true

            Text {
                id: label
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 8
                color: "#000000"
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.pixelSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onClicked: root.clicked()
            }
        }

        Item {
            width: 20
            Layout.fillHeight: true
            Layout.fillWidth: true
            Text {
                id: params
                width: 20
                color: "#000000"
                visible: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: root.clicked()
            }
        }
    }
}
