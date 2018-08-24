import QtQuick 2.0
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

ToolButton {
    implicitHeight: 50

    property int animationTime: 250
    property string thisText: ""
    property string bgColor: "#222222"
    property string defaultColor: "#224471"
    property string checkedColor: "#253856"
    property string accentColor: "#21a2ff"
    id: configBtn
    opacity: 1.0
    Layout.fillWidth: true

    Behavior on bgColor{

        ColorAnimation {  duration: animationTime
        }
    }

    background: Rectangle {
        id:bg
        color: bgColor
    }

    checkable: true

        Text {
            color: "#eeefefff"
            padding: 10
            font.pixelSize: Qt.application.font.pixelSize * .9
            text: thisText
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.weight: Font.ExtraBold
            //opacity: .85
        }

        Item {
            height: 15
        }

        Pane {
            id:borderBottom
            height: 6
            visible: false
            width: parent.width
            anchors.top: parent.top
            background: Rectangle{
                color: "#21a2ff"
            }
        }

        Component.onCompleted: {
            bgColor = defaultColor
        }

        onHoveredChanged:{
            if(!checked)
            bgColor = configBtn.hovered? checkedColor : defaultColor
        }
        onHighlightedChanged: {
            if(highlighted && !checked)
                bg.border.width = 5
        }
        onCheckedChanged: {
            if(checked){
                bgColor = checkedColor
                borderBottom.visible = true;
            }
            else{
                bgColor = defaultColor
                borderBottom.visible = false;

            }
        }

}
