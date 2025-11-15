import QtQuick
import HuskarUI.Basic

import herald.widget

HusWindow {
    width: 640
    height: 480
    visible: true
    title: qsTrId('Herald')
    // captionBar.winIconVisible: false
    Component.onCompleted: {
        if (Qt.os === 'windows') {
            if (setSpecialEffect(HusWindow.Win_MicaAlt)) return;
            if (setSpecialEffect(HusWindow.Win_Mica)) return;
            if (setSpecialEffect(HusWindow.Win_AcrylicMaterial)) return;
            if (setSpecialEffect(HusWindow.Win_DwmBlur)) return;
        } else if (Qt.os === 'osx') {
            if (setSpecialEffect(HusWindow.Mac_BlurEffect)) return;
        }
    }

    HeraldMenuBar {
    }
}
