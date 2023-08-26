QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tools/mymsg.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Tools/mymsg.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    QT-myChat-Client_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/a (1).jpg \
    images/a (1).jpg \
    images/a (1).png \
    images/a (1).png \
    images/a (10).jpg \
    images/a (10).jpg \
    images/a (11).jpeg \
    images/a (11).jpeg \
    images/a (12).jpeg \
    images/a (12).jpeg \
    images/a (13).jpg \
    images/a (13).jpg \
    images/a (14).jpe \
    images/a (14).jpe \
    images/a (15).jpe \
    images/a (15).jpe \
    images/a (16).jpeg \
    images/a (16).jpeg \
    images/a (17).jpg \
    images/a (17).jpg \
    images/a (2).jpg \
    images/a (2).jpg \
    images/a (3).jpg \
    images/a (3).jpg \
    images/a (4).jpg \
    images/a (4).jpg \
    images/a (5).jpg \
    images/a (5).jpg \
    images/a (6).jpg \
    images/a (6).jpg \
    images/a (7).jpg \
    images/a (7).jpg \
    images/a (8).jpg \
    images/a (8).jpg \
    images/a (9).jpg \
    images/a (9).jpg

RESOURCES += \
    res.qrc
