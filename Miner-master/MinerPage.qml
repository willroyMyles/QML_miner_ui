import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick 2.9
import QtQuick.Controls.Material 2.2
import QtGraphicalEffects 1.0

Page {
    property string accentColor: "#21a2ff"
    property string primaryColor: "#253856"

    id: main
    spacing: 0
    background: Rectangle {
        id: mainBg
        color: "#333"
    }

    ColumnLayout {
        anchors.fill: parent
        Pane {
            id: headerPane

            background: Rectangle {
                id: bg
                color: primaryColor
            }
            Layout.fillWidth: true
            padding: 10

            RowLayout {

                anchors.fill: parent
                Layout.fillWidth: true
                Item {
                    Layout.fillWidth: true
                }
                InfoNode {
                    id: node1
                    backgroundColor: "green"
                    //prevHashes: card1.prevHashes + card2.prevHashes
                    //currentHashes: card1.currentHashes + card2.currentHashes
                }

                InfoNode {
                    id: node2
                    backgroundColor: "red"
                    prevHashes: 190
                    currentHashes: 87
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }

        ScrollView {
            id: scrollview
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            topPadding: 20
            background: Rectangle {
                color: "#00000000"
            }
            ColumnLayout {
                id: col
                width: scrollview.width
                spacing: 0

                // Layout.fillWidth: true
                CardSquare {
                    id: card1
                    currentHashes: 33
                    prevHashes: 123
                }

                CardSquare {
                    id: card2
                    currentHashes: 95
                    prevHashes: 109
                }
            }
        }
        Component.onCompleted: {


            //console.log(col.width)
            //console.log(scrollview.width)
        }

        Item {
            Layout.fillHeight: true
        }

        Pane {
            padding: 10
            Layout.fillWidth: true
            background: Rectangle {
                color: "#333"
            }
            RowLayout {
                id: bottomRow
                anchors.fill: parent
                Item {
                    Layout.fillWidth: true
                }

                Button {
                    checkable: true

                    contentItem: Text {
                        id:btn
                           text: "start"
                           color: "#fff"
                           opacity: enabled ? 1.0 : 0.3
                           horizontalAlignment: Text.AlignHCenter
                           verticalAlignment: Text.AlignVCenter
                           elide: Text.ElideRight
                       }

                       background: Rectangle {
                           implicitWidth: 100
                           implicitHeight: 40
                           border.color: "#11000000"
                           border.width: 1
                           radius: 2
                           color: primaryColor
                           layer.enabled: true
                           layer.effect: DropShadow {
                               verticalOffset: 0
                               color: "#33000000"
                               radius: 9

                       }
                    }
                    onClicked: {
                        node1.currentHashes = node1.currentHashes + 10

                        if (checked) {
                            btn.text = "stop"
                        } else {
                            btn.text = "start"
                        }
                    }
                }
            }
        }
    }
}
