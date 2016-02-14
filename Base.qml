import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4

Item {
    property alias orientation: listView.orientation
    property alias color: rect.color
    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias text: gb.title
    Layout.minimumHeight: 84
    GroupBox {
        id: gb
        anchors.fill: parent
        flat: true
        Rectangle {
            id: rect
            clip: true
            color: "#c6c3c3"
            anchors.fill: parent
            Layout.minimumHeight: 50
            ListView {
                id: listView
                anchors.centerIn: parent
                anchors.fill: parent
                model: modelIO
                delegate: delegateIO
                highlight: highlight
                highlightFollowsCurrentItem: true
            }
        }
    }
    ListModel {
        id: modelIO
        ListElement {
            value: 1
        }
        ListElement {
            value: 5
        }
        ListElement {
            value: 0
        }
        ListElement {
            value: 2
        }
        ListElement {
            value: 2
        }
        ListElement {
            value: 1
        }
    }

    Component {
        id: delegateIO
        Item {
            width: 50; height: 50
            Text {
                id: nameField
                text: value
                anchors.centerIn: parent

            }
        }
    }

    Component {
        id: highlight
        Rectangle {
            width: 50; height: 50
            color: "#a1a3aa"; radius: 1
            y: list.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }
}
