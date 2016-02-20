import QtQuick 2.2
import QtQuick.Layouts 1.1

Item {
    id: root
    width: ListView.view.width
    height: 24
    property alias text: label.text
    property alias color: label.color

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
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Text {
                id: label
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 8
                color: "#000000"
                font.pixelSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onClicked: root.clicked()
            }
        }
    }
}
