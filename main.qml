import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import org.machine 1.0

//import "." as Custom

Window {
    visible: true
    property int margin: 11
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin
    color: "#4d4d4d"
    ToolBar {
        id: toolbar
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Open"
                onClicked: ui.load()
            }
            ToolButton {
                text: "Run"
                onClicked: ui.run()
            }
            ToolButton {
                text: "Step"
                onClicked: ui.step()
            }
            ToolButton {
                text: "Reset"
                onClicked: ui.reset()
            }
            Item { Layout.fillWidth: true }
        }
    }
    GridLayout {
        id: mainLayout
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolbar.bottom
        anchors.margins: 2
        columns: 2

        Base {
            id: input
            Layout.fillWidth: true

            Layout.columnSpan: 2
            orientation: ListView.Horizontal
            text: "Input tape"
        }

        Base {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 1
            text: "Program"
            model: Program {}
            delegate: ProgramDelegate {
                text: 'hsv(' +
                 Number(model.hue).toFixed(2) + ',' +
                 Number(model.saturation).toFixed() + ',' +
                 Number(model.brightness).toFixed() + ')'
                color: model.name
                onClicked: {
                    ListView.view.currentIndex = index
                    ListView.view.focus = true
                }
            }
//                Component {
//                Item {
//                    Layout.fillWidth: true
//                    height: 50
//                    Button {
//                        id: nameField
//                        text: 'hsv(' +
//                              Number(model.hue).toFixed(2) + ',' +
//                              Number(model.saturation).toFixed() + ',' +
//                              Number(model.brightness).toFixed() + ')'
//                        // color: model.name
//                        anchors.centerIn: parent
//                        anchors.fill: parent

//                        onClicked: {
//                            // make this delegate the current item
//                            ui.reset()
//                            view.currentIndex = index
//                            view.focus = true
//                        }

//                    }
//                }
//            }
        }


        Base {
            Layout.fillHeight: true
            Layout.minimumWidth: 200
            Layout.columnSpan: 1
            text: "Memory"

        }

        Base {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            orientation: ListView.Horizontal
            text: "Output tape"
        }


//            ListView {
//                id: view
//                anchors.fill: parent
//                model: Program {}
//                delegate: Text {
//                    text: name + ": " + number
//                }
//            }
//        ListView {
//            orientation: ListView.Horizontal
//            //anchors.fill: parent
//            model: modelIO
//            delegate: delegateIO
//            highlight: highlight
//            highlightFollowsCurrentItem: true
//        }

    }
}
