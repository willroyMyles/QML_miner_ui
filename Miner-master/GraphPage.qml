import QtQuick 2.0
import QtCharts 2.0
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Page {
    property string accentColor: "#21a2ff"
    property string primaryColor: "#253856"

    background: Rectangle{
        color: primaryColor
    }
        smooth: true
    ChartView {
        id:chart
        title: "Line"
        anchors.fill: parent
        antialiasing: true
        backgroundColor: "transparent"
        titleColor: "white"
        theme: ChartView.ChartThemeDark
//        theme: ChartView.ChartThemeHighContrast

        LineSeries {
                //capStyle: Qt.SquareCap
                width: 2.0
                color: "green"

                name: "LineSeries"
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1.1; y: 2.1 }
                XYPoint { x: 1.9; y: 3.3 }
                XYPoint { x: 2.1; y: 2.1 }
                XYPoint { x: 2.9; y: 4.9 }
                XYPoint { x: 3.4; y: 3.0 }
                XYPoint { x: 4.1; y: 3.3 }
            }

        AreaSeries{
            opacity: .5
            brushFilename: ":/images/brush copy"
            upperSeries: LineSeries{
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1.1; y: 2.1 }
                XYPoint { x: 1.9; y: 3.3 }
                XYPoint { x: 2.1; y: 2.1 }
                XYPoint { x: 2.9; y: 4.9 }
                XYPoint { x: 3.4; y: 3.0 }
                XYPoint { x: 4.1; y: 3.3 }
            }
        }
    }


}
