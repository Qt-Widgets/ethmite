TEMPLATE = app

QT += qml quick widgets network declarative quickwidgets 

CONFIG += qwt

SOURCES += main.cpp \
    EthInterface.cpp \
    IoForm.cpp \
    MainForm.cpp \
    PlotForm.cpp \
    QLed.cpp \
    Satellite.cpp \
    PanelWidget.cpp \
    PanelRadar.cpp \
    PanelDiagram.cpp \
    PanelWorld.cpp \
    PanelInfo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    IoForm.ui \
    MainForm.ui \
    PlotForm.ui

HEADERS += \
    EthlInterface.h \
    IoForm.h \
    MainForm.h \
    PlotForm.h \
    QLed.h \
    Satellite.h \
    PanelWidget.h \
    PanelRadar.h \
    PanelDiagram.h \
    PanelWorld.h \
    PanelInfo.h

win32: {
    RC_FILE = ethmite.rc
}