import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import "settings"

Page {
    property string accentColor: "#21a2ff"
    property string primaryColor: "#253856"
    smooth: true
    // padding: 20

    background: Rectangle {
        color: primaryColor
    }

    Component.onCompleted: {

        //   console.log(MinerPage.primaryColor)
    }

    ColumnLayout {
        spacing: 1
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
        }

        SettingsNode{
            labeld: "Walled ID"
            textfieldd: "Enter wallet ID here"
        }

        SettingsNode{
            labeld: "Pool Address"
            textfieldd: "Enter Pool Address"
        }

        SettingsNode{
            labeld: "Identifier"
            textfieldd: "Enter Identifier"
        }

        SettingsNode{
            labeld: "Password"
            textfieldd: "Enter Password"
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Button {
                Layout.fillWidth: true
                text: "cancel"
            }
            Button {
                text: "confirm"
                Layout.fillWidth: true
            }
        }
    }
}
