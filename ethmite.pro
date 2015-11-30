TEMPLATE = app

QT += widgets network

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
    PanelInfo.cpp \
    TimeSender.cpp

RESOURCES += qml.qrc

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
    PanelInfo.h \
    TimeSender.h

win32: {
    RC_FILE = ethmite.rc
}