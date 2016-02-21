import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Item {
    property alias orientation: listView.orientation
    property alias color: rect.color
    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias text: txt.text
    //Layout.minimumHeight: 60
    ColumnLayout {
        anchors.fill: parent

        Column {
            id: column1
            width: 200
            height: 400
            Layout.fillWidth: true

            Text {
                id: txt
                height: 25
                color: "white"
                text: "ghfgdhfg"
                clip: true
                anchors.horizontalCenter: parent.horizontalCenter
                //Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                font.bold: false
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: false
                Layout.fillWidth: true
            }
        }

        Column {
            id: column2
            width: 200
            height: 400
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Rectangle {
                id: rect
                x: 0
                y: 23
                clip: true
                color: "#c6c3c3"
                Layout.fillHeight: true
                Layout.fillWidth: true
                anchors.fill: parent
                //Layout.minimumHeight: 50
            }

            ListView {
                id: listView
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                contentWidth: 0
                Layout.preferredHeight: -1
                Layout.preferredWidth: -1
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillHeight: true
                transformOrigin: Item.Center
                Layout.fillWidth: true
                opacity: 1
                model: modelIO
                delegate: delegateIO
            }
        }



    }


    Component {
        id: highlight
        Rectangle {
            width: 50; height: 50
            color: "#a1a3aa"; radius: 1
            //y: list.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }


}
