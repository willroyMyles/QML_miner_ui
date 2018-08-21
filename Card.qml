import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4


Page {
    id: card

        leftPadding: 10
        rightPadding: 10
        topPadding: 5



    Layout.fillWidth: true
    background: Rectangle {
        color: "#88000000"
        radius: 6
    }


    property alias cardName: cardName.text
    property alias status: statusLabel.text
    property alias pool: poolLabel.text
    property alias speed: speedLabel.text
    property alias current: currentLabel.text
    property alias previous: previousLabel.text
    property int currentHashes: 0
    property int prevHashes: 0

    //property alias minimize: collapseButton

    function setCurrentHashes(hash){
        currentHashes = hash;
    }

    ColumnLayout {
       anchors.fill: parent
        Layout.fillWidth: true
        RowLayout {
            Text {
                id: cardName
                text: qsTr("geforece sixty M")
                font.pixelSize: Qt.application.font.pixelSize * 2.0
                opacity: .6
            }

            Item {
                Layout.fillWidth: true
            }

            Switch {
                id: button
                text: qsTr("▼")
                onClicked: {

                }

            }
        }

        RowLayout {
            ColumnLayout {
                // text info section
                Label {
                    id: statusLabel
                    text: "status"
                }
                Label {
                    id: poolLabel
                    text: "status"
                }
                Label {
                    id: speedLabel
                    text: "status"
                }
                Label {
                    id: currentLabel
                    text: "Current Hashes : " +currentHashes
                }
                Label {
                    id: previousLabel
                    text: "Previous Hashes : "+prevHashes
                }
            }
            ColumnLayout {
                // graph section
            }

        }

        Item{ // space
            height: 1
        }

        RowLayout{ // line
            Rectangle{
                height: 1
                Layout.fillWidth: true
                color: "#11444444"
            }
        }

        RowLayout{ // addition Info

        }
    }
    onCurrentHashesChanged: {


    }

}
