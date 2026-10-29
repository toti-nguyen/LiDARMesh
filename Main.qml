import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import LiDARMesh

ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("LAS Points")

    LASReader {
        id: lasReader
    }

    property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    property color reallyDark: "#1f1f1f"
    property color dark: "#262626"
    property color reallyLight: "#e7e7e7"
    property color light: "#e0e0e0"


    Rectangle {
        width: 600;
        height: 450;
        color: "#550000";

        Text {
            id: x
            color: dark
            text: lasReader.getXQStr
        }
    }

}
