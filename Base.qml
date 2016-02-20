import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Item {
    property alias orientation: listView.orientation
    property alias color: rect.color
    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias text: gb.title
    //Layout.minimumHeight: 60
    GroupBox {
        id: gb
        anchors.fill: parent
        flat: true
        Rectangle {
            id: rect
            clip: true
            color: "#c6c3c3"
            anchors.fill: parent
            //Layout.minimumHeight: 50
            ListView {
                id: listView
                opacity: 1
                anchors.centerIn: parent
                anchors.fill: parent
                model: modelIO
                delegate: delegateIO
                //highlight: highlight
                //highlightFollowsCurrentItem: true
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
