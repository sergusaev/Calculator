import QtQuick 2.15
import QtQuick.Controls 2.15
import SecretMenuHandler 1.0
import QtGraphicalEffects 1.15

Rectangle {
    id: root
    color: "transparent"

    Rectangle {
        id: _secret_menu_window
        anchors.fill:parent
        color: "#0889A6"
        radius: 10

        Text {
            id:_secret_menu_window_text
            color: "white"
            font {
                pointSize: 24
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            text: "Secret Menu"
        }

        Button {
            id: _back_button
            width: root.width / 2.8
            height: width / 3
            text: _back_button_text.text
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: height
            anchors.rightMargin: height

            contentItem: Text {
                id:_back_button_text
                color:  _back_button.pressed ? "#024873" : "#FFFFFF"
                font {
                    pointSize: 14
                }
                anchors.centerIn: parent
                text: qsTr("Back")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                color: _back_button.pressed ? "#04BFAD" :"#B0D1D8"
                radius: 10

            }



            onClicked: {
                SecretMenuHandler.resetOpening
                root.visible = false;
            }

        }

    }

    DropShadow {
        anchors.fill: _secret_menu_window
        horizontalOffset: 6
        verticalOffset: 6
        color: "black"
        source: _secret_menu_window
    }
}
