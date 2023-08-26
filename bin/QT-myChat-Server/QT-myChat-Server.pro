QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #Database/DBHelper.cpp \
    Thread/chatbusiness.cpp \
    Thread/chatthread.cpp \
    Tools/log.cpp \
    Tools/mymsg.cpp \
    main.cpp \
    mainwindow.cpp \
    Service/tcpservice.cpp


HEADERS += \
    #Database/DBHelper.h \
    Thread/chatbusiness.h \
    Thread/chatthread.h \
    Tools/log.h \
    Tools/mymsg.h \
    mainwindow.h \
    Service/tcpservice.h



FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    QT-myChat-Server_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
