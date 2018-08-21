import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick 2.9
import QtQuick.Controls.Material 2.2

Page {
    id: main

    ColumnLayout {
        anchors.fill: parent

        Pane {
            id: headerPane
            background: Rectangle{
                color: "#ee333333"
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
                    prevHashes: card1.prevHashes + card2.prevHashes
                    currentHashes: card1.currentHashes + card2.currentHashes
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
            padding: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ColumnLayout {
                id: col
                width: scrollview.width - 20

                Card {
                    id: card1
                    currentHashes: 33
                    prevHashes: 123
                }
                Card {
                    id: card2
                    currentHashes: 95
                    prevHashes: 109
                }
            }
        }
        Component.onCompleted: {
            console.log(col.width)
            console.log(scrollview.width)
        }

        Item {
            Layout.fillHeight: true
        }

        Page {
            padding: 10
            Layout.fillWidth: true
            RowLayout{
            id: bottomRow
            anchors.fill: parent
            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "start"
                onClicked: {
                    node1.currentHashes = node1.currentHashes+10
                }
            }
            }
        }
    }
}
