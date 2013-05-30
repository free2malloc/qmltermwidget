import QtQuick 2.0
import QMLTerminal 1.0

Rectangle {
	width: 640
	height: 480

    Rectangle {
        color: '#feeeff'
        anchors.fill: parent
        anchors.margins: 5
        radius: 5
        QMLTerminal {
            id: terminal
            anchors.fill: parent
            anchors.margins: 10
            focus: true

            Keys.onPressed: {
                sendKey(event.key, event.modifiers, true, event.nativeScanCode, event.text);
                event.accepted = true;
            }

            MouseArea {
                anchors.fill: parent
                onClicked: terminal.forceActiveFocus();
            }
        }
    }
}
