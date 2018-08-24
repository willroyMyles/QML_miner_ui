import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Page {
    property string bgColor: "#20343455"
    id: card

    padding: 11
    Layout.fillWidth: true
    background: Rectangle {
        id: bg
        color: bgColor
        radius: 1
        border.color: "#66222222"
        border.width: 1.0
    }

    property color textColor: "#fff"
    property int textWeight: 63

    property alias cardName: cardName.text
    property alias status: statusLabel.text
    property alias current: currentLabel.text
    property alias previous: previousLabel.text
    property int currentHashes: 0
    property int prevHashes: 0
    property string defaultColor: "#224471"
    property string checkedColor: "#253856"
    property string accentColor: "#21a2ff"


    //property alias minimize: collapseButton
    function setCurrentHashes(hash) {
        currentHashes = hash
    }

    TextMetrics {
        id: customText
        font.pixelSize: Qt.application.font.pixelSize * .9
        font.weight: textWeight
    }

    ColumnLayout {
        anchors.fill: parent
        Layout.fillWidth: true

        RowLayout {
            Layout.fillWidth: true

            // text info section
            Label {
                id: cardName
                text: qsTr("geforece sixty M")
                font.pixelSize: Qt.application.font.pixelSize *1
                font.weight: textWeight
                opacity: 1
                color: textColor
                antialiasing: true
                anchors.left: parent.left
                Layout.fillWidth: true
                layer.enabled: false
                layer.effect: DropShadow {
                    verticalOffset: 2
                    color: "#eee"
                    radius: 1
                    samples: 3
                }
            }

            Label {
                id: statusLabel
                text: "Connected"
                color: textColor
                //font.weight: textWeight
                font: customText.font
                Layout.fillWidth: true
            }
            //                Label {
            //                    id: poolLabel
            //                    text: "xmrstackpool"
            //                    color: textColor
            //                    font: customText.font
            //                    visible: false
            //                    Layout.fillWidth: true

            //                }
            //                Label {
            //                    id: speedLabel
            //                    text: "123 /hr"
            //                    color: textColor
            //                    font: customText.font
            //                    visible: false
            //                    Layout.fillWidth: true

            //                }
            Label {
                id: currentLabel
                text: "Current Hashes : " + currentHashes
                color: textColor
                font: customText.font
                Layout.fillWidth: true
            }
            Label {
                id: previousLabel
                text: "Previous Hashes : " + prevHashes
                color: textColor
                font: customText.font
                Layout.fillWidth: true
            }

            CheckBox {
                id: control
                text: qsTr("CheckBox")
                checked: false

                ToolTip{
                    text: "check to set graphics card to mine"
                }

                indicator: Rectangle {
                    implicitWidth: 16
                    implicitHeight: 16
                    x: control.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 3
                    border.color: defaultColor
                    color: "#00000000"

                    Rectangle {
                        id: checkIndicator
                        anchors.centerIn: parent
                        width: 10
                        height: width
                        x: 6
                        y: 6
                        radius: 2
                        color: control.checked ? checkedColor : "#00000000"
                       // visible: control.checked
                        Behavior on width {
                            SmoothedAnimation{
                                velocity: 50
                            }
                        }
                    }
                }

                contentItem: Text {
                    text: control.text
                    font: control.font
                    opacity: enabled ? 1.0 : 0.3
                    color: textColor
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: control.indicator.width + control.spacing
                }
                onClicked: {
                    if(control.checked){
                        checkIndicator.width = 10
                        bgColor = "#77000000"
                    }else
                       {
                        checkIndicator.width = 0
                        bgColor = "#20343455"
                    }
                }
            }
        }

        RowLayout {
            // addition Info
        }
    }
    onCurrentHashesChanged: {

    }

}
