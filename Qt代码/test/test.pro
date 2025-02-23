QT       += core gui
QT       += network
QMAKE_CXXFLAGS += -fpermissive
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    fileprodialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS += \
    client.h \
    fileprodialog.h \
    logindialog.h \
    mainwindow.h \
    server.h

FORMS += \
    fileprodialog.ui \
    logindialog.ui \
    mainwindow.ui

win32{
    LIBS += -lws2_32
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
