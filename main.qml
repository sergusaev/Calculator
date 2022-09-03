import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Processor 1.0
import "qml" as MyQml

Window {
    id: root
    width: 360
    height: 640
    maximumWidth: 360
    maximumHeight: 640
    minimumWidth: 360
    minimumHeight: 640
    visible: true
    title: qsTr("Calculator")

    Connections {
        id: _calc_connections
        target: Processor

        function onRightValueChanged(argValue) {
            console.log("onRightValueChanged signal caught")
            console.log("argValue: " + argValue)            
            _display_text.text = argValue
            if(argValue.length <= 8) {
                _display_text.font.pointSize = 32
            }
            else if(argValue.length > 8 && argValue.length <= 14) {
                _display_text.font.pointSize = 22
            }
            else {
                _display_text.font.pointSize = 14
            }
        }

        function onExpressionChanged(expression) {
            console.log("onExpressionChanged signal caught")
            console.log("expression: " + expression)
            _display_expr_text.text = expression
        }

    }

    Rectangle {
        id: _root_back
        anchors.fill: parent
        color: "#024873"


        Rectangle{
            id: _display_expr
            z:_root_back.z + 1
            height: 24
            width: 340
            color: "transparent"
            anchors.horizontalCenter: _root_back.horizontalCenter
            anchors.top: _root_back.top
            anchors.topMargin: 70
                Text {
                    id:_display_expr_text
                    color: "white"
                    font {
                        pointSize: 10
                    }
                    anchors.right: parent.right
                    text: "0"
                }



        }
        Rectangle{
            id: _display
            z:_root_back.z + 1
            height: 60
            width: 340
            color: "transparent"
            anchors.horizontalCenter: _root_back.horizontalCenter
            anchors.top: _root_back.top
            anchors.topMargin: 100
            property int radixCount : 0
            Text {
                id:_display_text
                color: "white"
                font {
                    pointSize: 32
                }
                anchors.right: parent.right
                text: "0"
            }



        }


        Rectangle {
            id: _calculation_back
            width: 360
            height: 190
            anchors.top: parent.top
            anchors.topMargin: -10
            color: "#04BFAD"
            radius: 10


        }

        Rectangle {
            id: _buttons_back
            width: 330
            height: 430
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 22
            color: "transparent"

            MyQml.Buttons {
                id: _buttons_grid_view
                anchors.fill:parent



            }

        }
    }
}
