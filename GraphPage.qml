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
    anchors.fill: parent

    background: Rectangle{
        color: primaryColor
    }

    ChartView {
        title: "Line"
        anchors.fill: parent
        antialiasing: true
        ValueAxis {
            id: axisX
            min: 0
            max: 10
            tickCount: 5
        }

        ValueAxis {
            id: axisY
            min: -0.5
            max: 1.5
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
        }

        ScatterSeries {
            id: series2
            axisX: axisX
            axisY: axisY
        }
    }

    Component.onCompleted: {
        for (var i = 0; i <= 10; i++) {
            series1.append(i, Math.random());
            series2.append(i, Math.random());
        }
    }
}
