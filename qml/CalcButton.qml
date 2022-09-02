import QtQuick 2.15
import QtQuick.Controls 2.15



Rectangle {
    id: root
    property alias text: _button_text.text
    property alias textColor: _button_text.color
    signal clicked()
    signal released()
    signal pressed()
    color: "transparent"


    Text {
        id:_button_text
        anchors.centerIn: parent
        color: "white"
        text: qsTr("")
        font.pointSize: 20
    }

    MouseArea {
        id:_button_mouse_area
        anchors.fill: parent

        onClicked: {
            root.clicked()
        }
        onReleased: {
            root.released()
        }

        onPressed: {
            root.pressed()
        }

    }
}




