import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.2


ApplicationWindow {
    id : mainwindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Miner")


    header : ToolBar{
        id: toolbar
        property alias texts: toolbutton.text
        RowLayout{
            anchors.fill: parent

            ToolButton{
                font.pixelSize: Qt.application.font.pixelSize * 1.8
                id: toolbutton
                text: "\u2630  OverView"
                opacity: .5
                onClicked: drawer.open()
            }

            Item{
                Layout.fillWidth: true;
            }

        }
    }

    StackView{
        id: stack
        initialItem: "MinerPage.qml"
        anchors.fill: parent
        background: Rectangle{
            border.color: "red"
        }
    }

    Drawer {
        id : drawer;
        width: mainwindow.width * 0.4
        height: mainwindow.height
        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Miner")
                width: parent.width
                onClicked: {
                    if(stack.depth > 1) stack.pop()
                    stack.push("MinerPage.qml")
                    drawer.close()
                    toolbar.texts = "\u2630  OverView"
                }
            }
            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    if(stack.depth > 1) stack.pop()
                    stack.push("SettingsPage.qml")
                    drawer.close()
                    toolbar.texts = "\u2630  Settings"

                }
            }
        }
    }
}
