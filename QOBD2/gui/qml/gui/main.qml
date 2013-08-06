import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: main
    width: 360
    height: 360      

    Label{
        id: lblLogTitle
        text: qsTr("Logs")
        font.bold: true
        font.pointSize: 15
        height: 20
    }

    TextArea{
        id: taLogs
        text: qsTr("")
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 10
        anchors.top: lblLogTitle.bottom
        anchors.left: main.left
        anchors.right: main.right
    }

    Connections{
        target: obdProxy
        onLog: {            
            taLogs.append(message)
        }
    }



}
