// pragma Singleton
import QtQuick
import HuskarUI.Basic

Column {
    id: menuBar

    Row {
        id: menuBarFirstRow

        HusButton {
            text: qsTrId("HERALD::MENUBAR::LANGUAGE")
            type: HusButton.Type_Text
        }

        HusButton {
            text: qsTrId("HERALD::MENUBAR::ABOUT")
            type: HusButton.Type_Text
            // radiusBg: 0
        }
    }

    Row {
        id: toolBar
    }
}
