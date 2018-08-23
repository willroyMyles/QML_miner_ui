import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1


Page {
    property string accentColor: "#21a2ff"
    property string primaryColor: "#253856"
    padding: 20

    background: Rectangle{
        color: primaryColor
    }

    Component.onCompleted: {
     //   console.log(MinerPage.primaryColor)
    }

   ColumnLayout{
       spacing: 10
       anchors.fill: parent

       RowLayout{
           Layout.fillWidth: true

           Label{
               Layout.fillWidth: true
               text: "walletid"
           }
           TextEdit{
               Layout.fillWidth: true
           }
       }
       RowLayout{
           Label{
               Layout.fillWidth: true
               text: "walletid"
           }
           TextEdit{
               Layout.fillWidth: true
           }
       }
       RowLayout{
           Label{
               Layout.fillWidth: true
               text: "walletid"
           }
           TextEdit{
               Layout.fillWidth: true
           }
       }
       RowLayout{
           Label{
               Layout.fillWidth: true
               text: "walletid"
           }
           TextEdit{
               Layout.fillWidth: true
           }
       }
       RowLayout{
           Label{
               Layout.fillWidth: true
               text: "walletid"
           }
           TextEdit{
               Layout.fillWidth: true
           }
       }

       Item{
           Layout.fillHeight: true
       }

       RowLayout{
           Button{
               Layout.fillWidth: true
               text: "cancel"
           }
           Button{
               text: "confirm"
               Layout.fillWidth: true
           }
       }

   }
}
