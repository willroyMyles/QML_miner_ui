import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1


Pane{
    id: pane
    property alias labeld: label.text
    property alias textfieldd: textfield.placeholderText
    property alias textValue: textfield.text
    Layout.fillWidth: true
    height: 155
    background: Rectangle{
        radius: 1
        color: "#ffffff"
        border.color: "#22222222"
        border.width: 0
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Label{
            id:label
            leftPadding: 12
            text: "walled id "
            background: Rectangle{
            }
        }
        TextField{
            id: textfield
            placeholderText: "Enter wallet address"
            text:""
            Layout.fillWidth: true

            background: Rectangle{
                implicitHeight: 35

            }
        }
    }
}

