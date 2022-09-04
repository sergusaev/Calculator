import QtQuick 2.15
import QtQuick.Controls 2.15
import Button 1.0
import Processor 1.0
import SecretMenuHandler 1.0



GridView {
    id:root
    model: buttonsModel

    cellWidth: width / 4.1
    cellHeight: height / 5
    boundsBehavior: Flickable.StopAtBounds

    Component {
        id:_grid_view_delegate
        CalcButton {
            text: buttonText
            color: buttonColor
            textColor: "#FFFFFF"
            width: 0.9 * Math.min(root.cellWidth, root.cellHeight)
            height: width
            radius: height / 2
            clip: true

            Image {
                id:_button_icon
                anchors.centerIn: parent
                source: buttonIconPath
            }

            onPressed: {
                console.log("Button type role: ")
                console.log(buttonType)
                color = buttonColorActive
                textColor = buttonColor === "#0889A6" ? "#FFFFFF": "#024873"

                SecretMenuHandler.buttonPressed(buttonType)

                Processor.evaluate(buttonType)
                // SecretMenuHandler.equalButtonPressed()
            }
            onReleased: {
                color = buttonColor
                textColor = "#FFFFFF"
                SecretMenuHandler.buttonReleased(buttonType)
            }

            //            onPressAndHold: {
            //                SecretMenuHandler.equalButtonPressAndHold()
            //            }
        }
    }

    delegate: _grid_view_delegate
    focus: true

}


