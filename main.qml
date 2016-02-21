import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2

Window {
    id: root
    visible: true
    //property int margin: 11
    color: "#4b4b4b"
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    FileDialog {
        id: fileDialog
        title: "Please choose a ram program file"
        folder: shortcuts.home + "/test/Ram-Machine"
        nameFilters: [ "Source ram-machine files (*.ram)", "All files (*)" ]
        onAccepted: {
            machine.loadFile(fileDialog.fileUrl)
        }

    }

    FileDialog {
        id: inputFile
        title: "Please choose a input file"
        folder: shortcuts.home + "/test/Ram-Machine"
        nameFilters: [ "All files (*)" ]
        onAccepted: {
            itape.loadInput(inputFile.fileUrl)
        }
    }

    Dialog {
        id: manualInput
        title: "Introducir entrada:"
        contentItem: Rectangle {
            color: "#302F2F"
            implicitWidth: 400
            implicitHeight: 100
            TextInput {
                focus: true
                color: "white"
                text: "1 2 3"
                font.bold: true
                font.pointSize: 15
                anchors.centerIn: parent
                onAccepted: {
                    itape.loadString(text)
                    manualInput.close()
                }
            }
        }
    }

    Dialog {
        id: memoryInput
        title: "Introducir entrada:"
        contentItem: Rectangle {
            color: "#302F2F"
            implicitWidth: 400
            implicitHeight: 100
            TextInput {
                focus: true
                color: "white"
                text: "1 2 3"
                font.bold: true
                font.pointSize: 15
                anchors.centerIn: parent
                onAccepted: {
                    memory.reset(parseInt(text))
                    memoryInput.close()
                }
            }
        }
    }

    ToolBar {
        id: toolbar
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        RowLayout {
            spacing: 6
            anchors.fill: parent
            visible: true
            clip: false
            ToolButton {
                text: "Open"
                onClicked: fileDialog.open()
            }
            ToolButton {
                text: "Open input file"
                onClicked: inputFile.open()
            }
            ToolButton {
                text: "Save Output Tape"
                onClicked: fileDialog.open()
            }
            ToolButton {
                text: "Run"
                onClicked: machine.run()
            }
            ToolButton {
                text: "Step"
                onClicked: machine.step()
            }
            ToolButton {
                text: "Reset"
                onClicked: machine.reset()
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
        anchors.margins: 10
        columns: 2

        Base {
            id: input
            color: qsTr("#c6c3c3")
            Layout.fillWidth: true

            Layout.columnSpan: 2
            text: "Input tape"
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.minimumHeight: 53
            Layout.minimumWidth: 16
            transformOrigin: Item.Center
            Layout.fillHeight: false
            orientation: 1
            model: itape
            delegate: TapeDelegate {
                text: model.display
                onClicked: {
                    manualInput.open()
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: manualInput.open()
            }
        }

        Base {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 1
            width: 200; height: 250
            text: "Program"
            model: machine
            delegate: ProgramDelegate {
                text: name
                number: line
                parameter: param
                color: pc
                onClicked: {
                    ListView.view.currentIndex = index
                    ListView.view.focus = true
                }
            }
        }

        Base {
            Layout.fillHeight: true
            Layout.minimumWidth: 200
            Layout.columnSpan: 1
            text: "Memory"
            model: memory
            delegate: MemoryDelegate {
                text: model.display
                backgroundColor: model.decoration
                onClicked: {
                    memoryInput.open()
                }
            }
        }

        Base {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            orientation: ListView.Horizontal
            text: "Output tape"
            Layout.minimumHeight: 53
            model: otape
            delegate: TapeDelegate {
                text: model.display
                onClicked: {
                    ListView.view.currentIndex = index
                    ListView.view.focus = true
                }
            }
        }
    }


}

//                Component {
//                Item {
//                    height: 30
//                    width: ListView.view.width
//                    Rectangle {
//                        anchors.fill: parent
//                        color: '#000000'
//                        opacity: 0.2
//                        border.color: Qt.darker(color)
//                    }
//                    Text {
//                        anchors.fill: parent
//                        anchors.centerIn: parent
//                        text: "Animal: " + type + ", " + size
//                    }
//                }
//            }
//        Base {
//            Layout.fillWidth: true
//            Layout.fillHeight: true
//            Layout.columnSpan: 1
//            text: "Program"
//            model: program
//            delegate: ProgramDelegate {
//                text: 'hsv(' +
//                 Number(hue).toFixed(2) + ',' +
//                 Number(saturation).toFixed() + ',' +
//                 Number(brightness).toFixed() + ')'
//                color: name
//                onClicked: {
//                    ListView.view.currentIndex = index
//                    ListView.view.focus = true
//                }
//            }
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
//        }



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
