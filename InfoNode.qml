import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Item {
    id : root
    width:180
    height: 140
    property int animationTime : 1250;

    property color textColor: "#fff"
    property int textWeight: 65
    property alias backgroundColor: box.color
    property int prevHashes: 97;
    property int currentHashes: 88;
    property string hashesString: currentHashes.toString()

    Behavior on currentHashes {
        SmoothedAnimation{
            duration: animationTime
        }
    }

    function updateFontSize() {
            while(textMa.width+10 > boxBackground.width){
                textMa.font.pixelSize--;
            }
        }

    function checkHashes(){
        if(prevHashes < currentHashes){
            previous.y = boxBackground.height + boxBackground.y - previous.height
            current.y = boxBackground.y
            box.height = boxBackground.height
        }
    }

    onCurrentHashesChanged: {
        hashesString = currentHashes.toString()
        updateFontSize()
        checkHashes()
    }

    Component.onCompleted: {
        updateFontSize()
        checkHashes()
    }

    NumberAnimation {
        target: box
        property: "height"
        duration: animationTime
        easing.type: Easing.InOutQuad
    }

    Rectangle{
        anchors.centerIn: root
        width: 80
        height: 80
        id : boxBackground
        antialiasing: true
        radius: 10
        color: "#000"
    }

    Rectangle{

        id : box
        width: boxBackground.width
        height: boxBackground.height * currentHashes/prevHashes
        anchors{
            left: boxBackground.left
            bottom: boxBackground.bottom
        }
        antialiasing: true
        radius: boxBackground.radius
        color: "green"
        opacity: 0.7
        Behavior on height {

            NumberAnimation {
                target: box
                property: "height"
                duration: animationTime
                easing.type: Easing.InOutQuad
            }
        }
    }

    Label{
        id : previous
        text: "previous \n"+ prevHashes
        x: boxBackground.x - width
        y:boxBackground.y
        opacity: .4
        color: textColor
        font.weight: textWeight

        Behavior on y{
            NumberAnimation {
                target: previous
                property: "y"
                duration: animationTime
                easing.type: Easing.InOutQuad
            }
        }
    }

    Label{
        id : current
        Text {
            id: texta
            text: qsTr("Current ")
            visible: false
        }
        text: texta.text
        x: box.x - width
        y: box.y + box.height - height
        color: textColor
        font.weight: textWeight

        Behavior on y{
            NumberAnimation {
                target: current
                property: "y"
                duration: animationTime
                easing.type: Easing.InOutQuad
            }
        }
    }


    Label{

        TextMetrics{
            id: textMa
            font.pixelSize: 400
            text: hashesString
            font.weight: textWeight

        }
        id: currenthash
        anchors.centerIn: boxBackground
        opacity: 1.0
        text : currentHashes
        font: textMa.font
        color: textColor
    }


}
