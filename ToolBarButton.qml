import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id : root
    property alias text: "value"

    Text {
        id: name
        text: qsTr(text)

    }
}
