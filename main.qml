import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: mainwindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Miner")

    property string textColor: "#eee"



    ButtonGroup{
        id: btnGrp
    }

    header: ToolBar {
        id: toolbar
        background: Rectangle {
            //   color: "#eee"
        }

        RowLayout {
            anchors.fill: parent
            id: row
            spacing: 0
            ToolBarButton {
                id: overviewBtn
                ButtonGroup.group: btnGrp
                thisText: "OVERVIEW"
                onClicked: {
                    swipe.setCurrentIndex(0)
                }
            }

            ToolBarButton {
                id: graphBtn
                ButtonGroup.group: btnGrp
                thisText: "GRAPHS"
                onClicked: {
                    swipe.setCurrentIndex(1)
                }
            }

            ToolBarButton {
                id: settingsBtn
                ButtonGroup.group: btnGrp
                thisText: "SETTINGS"
                onClicked: {
                    swipe.setCurrentIndex(2)
                }
            }

            ToolBarButton {
                id: aboutBtn
                thisText: "ABOUT US"
                checkable: false
                onClicked: {
                    drawer.open()
                }
            }
        }

        layer.enabled: true
                    layer.effect: DropShadow {
                        //transparentBorder: true
                        verticalOffset: 4
                        color: "#00555555"
                        radius: 9
                        samples: 18
                        visible: false

                    }
    }

    SwipeView {
        id: swipe
       // initialItem: minerpage

        anchors.fill: parent
        interactive: false
        background: Rectangle {
        }

        MinerPage{
            id: minerpage
        }

        Item {
            id: name
GraphPage{}        }

        SettingsPage{
            id:settingsPage
        }
    }

//    Component.onCompleted: {
//        stack.push(minerpage)
//        stack.push(settingsPage)
//        stack.push(chartPage)

//        console.log(stack.depth)
//    }

    Drawer {
        id: drawer
        width: mainwindow.width * 0.3
        height: mainwindow.height

        background: Rectangle {
            color: "#061021"
        }

        Column {
            anchors.fill: parent

            ItemDelegate {
                padding: 10
                width: parent.width
                Text {
                    text: qsTr("Miner")
                    color: textColor
                }
                onClicked: {
                    if (stack.depth > 1)
                        stack.pop()
                    stack.push("MinerPage.qml")
                    drawer.close()
                    toolbar.texts = "\u2630  OverView"
                }
            }
            ItemDelegate {
                padding: 10
                width: parent.width
                Text {
                    text: qsTr("Settings")
                    color: textColor
                }
                onClicked: {
                    if (stack.depth > 1)
                        stack.pop()
                    stack.push("SettingsPage.qml")
                    drawer.close()
                    toolbar.texts = "\u2630  Settings"
                }
            }
        }
    }
}
