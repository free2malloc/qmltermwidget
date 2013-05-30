TEMPLATE = lib
TARGET = qmltermwidget
QT += qml quick widgets
CONFIG += qt plugin

LIBS += -lqtermwidget

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.qterminal.qmlterminal
modulename = QMLTerminal

SOURCES += \
    qmltermwidget_plugin.cpp \
    qmlterminal.cpp

HEADERS += \
    qmltermwidget_plugin.h \
    qmlterminal.h

OTHER_FILES = imports/$$modulename/qmldir \
    terminal.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/../imports/$$modulename/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/imports/$$modulename/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = imports/$$modulename/qmldir
unix {
    installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

