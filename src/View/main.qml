import QtQuick
import HuskarUI.Basic

import herald.widget

HusWindow {
    id: heraldWindow

    title: qsTr('HERALD::MAIN::TITLE')

    // Set the default size of the main window
    width: 1100
    height: 750
    minimumWidth: 800
    minimumHeight: 600

    // Set the initial opacity of the window
    // opacity: 0

    // Automatically switch theme based on system settings
    followThemeSwitch: true

    // Use custom caption bar for Windows, Linux, and macOS
    captionBar.visible: Qt.platform.os === 'windows' || Qt.platform.os === 'linux' || Qt.platform.os === 'osx'
    captionBar.height: captionBar.visible ? 30 : 0
    captionBar.color: HusTheme.Primary.colorFillTertiary
    captionBar.showThemeButton: true
    captionBar.showTopButton: true
    captionBar.winIconWidth: 22
    captionBar.winIconHeight: 22
}
