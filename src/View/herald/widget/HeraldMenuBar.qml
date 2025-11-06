// pragma Singleton
import QtQuick
import HuskarUI.Basic

Row {
    id: menuBar

    HusButton {
        text: qsTr('默认')
        type: HusButton.Type_Text
    }

    HusButton {
        text: qsTr('线框')
        type: HusButton.Type_Text
    }

    HusButton {
        text: qsTr('主要')
        type: HusButton.Type_Text
    }

    HusButton {
        text: qsTr('填充')
        type: HusButton.Type_Text
    }

    HusButton {
        text: qsTr('文本')
        type: HusButton.Type_Text
    }

    HusButton {
        text: qsTr('about')
        type: HusButton.Type_Text
    }
}
