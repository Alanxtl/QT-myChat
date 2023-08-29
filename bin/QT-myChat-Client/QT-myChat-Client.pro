QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database/DBHelper.cpp \
    Database/UserInfo.cpp \
    Tools/filesend.cpp \
    Tools/handler.cpp \
    Tools/log.cpp \
    Tools/mymsg.cpp \
    Tools/socket.cpp \
    addfriend.cpp \
    chapage.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    qnchatmessage.cpp \
    regis.cpp


HEADERS += \
    Database/DBHelper.h \
    Database/UserInfo.h \
    Tools/filesend.h \
    Tools/handler.h \
    Tools/log.h \
    Tools/mymsg.h \
    Tools/socket.h \
    addfriend.h \
    chapage.h \
    login.h \
    mainwindow.h \
    qnchatmessage.h \
    regis.h

FORMS += \
    Tools/filesend.ui \
    addfriend.ui \
    chapage.ui \
    login.ui \
    mainwindow.ui \
    qnchatmessage.ui \
    regis.ui



TRANSLATIONS += \
    QT-myChat-Client_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/Customer Copy.png \
    images/Customer Copy.png \
    images/Customer Copy.png \
    images/CustomerService.png \
    images/a (1).jpg \
    images/a (1).jpg \
    images/a (1).jpg \
    images/a (1).jpg \
    images/a (1).jpg \
    images/a (1).png \
    images/a (1).png \
    images/a (1).png \
    images/a (1).png \
    images/a (1).png \
    images/a (10).jpg \
    images/a (10).jpg \
    images/a (10).jpg \
    images/a (10).jpg \
    images/a (10).jpg \
    images/a (11).jpeg \
    images/a (11).jpeg \
    images/a (11).jpeg \
    images/a (11).jpeg \
    images/a (11).jpeg \
    images/a (12).jpeg \
    images/a (12).jpeg \
    images/a (12).jpeg \
    images/a (12).jpeg \
    images/a (12).jpeg \
    images/a (13).jpg \
    images/a (13).jpg \
    images/a (13).jpg \
    images/a (13).jpg \
    images/a (13).jpg \
    images/a (14).jpe \
    images/a (14).jpe \
    images/a (14).jpe \
    images/a (14).jpe \
    images/a (14).jpe \
    images/a (15).jpe \
    images/a (15).jpe \
    images/a (15).jpe \
    images/a (15).jpe \
    images/a (15).jpe \
    images/a (16).jpeg \
    images/a (16).jpeg \
    images/a (16).jpeg \
    images/a (16).jpeg \
    images/a (16).jpeg \
    images/a (17).jpg \
    images/a (17).jpg \
    images/a (17).jpg \
    images/a (17).jpg \
    images/a (17).jpg \
    images/a (2).jpg \
    images/a (2).jpg \
    images/a (2).jpg \
    images/a (2).jpg \
    images/a (2).jpg \
    images/a (3).jpg \
    images/a (3).jpg \
    images/a (3).jpg \
    images/a (3).jpg \
    images/a (3).jpg \
    images/a (4).jpg \
    images/a (4).jpg \
    images/a (4).jpg \
    images/a (4).jpg \
    images/a (4).jpg \
    images/a (5).jpg \
    images/a (5).jpg \
    images/a (5).jpg \
    images/a (5).jpg \
    images/a (5).jpg \
    images/a (6).jpg \
    images/a (6).jpg \
    images/a (6).jpg \
    images/a (6).jpg \
    images/a (6).jpg \
    images/a (7).jpg \
    images/a (7).jpg \
    images/a (7).jpg \
    images/a (7).jpg \
    images/a (7).jpg \
    images/a (8).jpg \
    images/a (8).jpg \
    images/a (8).jpg \
    images/a (8).jpg \
    images/a (8).jpg \
    images/a (9).jpg \
    images/a (9).jpg \
    images/a (9).jpg \
    images/a (9).jpg \
    images/a (9).jpg \
    images/cat.jpg \
    images/ic_group.png \
    images/ic_lock.png \
    images/ic_user.png \
    images/icon_cut.png \
    images/icon_emoji.png \
    images/icon_file.png \
    images/icon_pic.png \
    images/loading4.gif \
    images/loading4.gif \
    images/a (1).jpg \
    images/a (10).jpg \
    images/a (11).jpeg \
    images/a (12).jpeg \
    images/a (13).jpg \
    images/a (14).jpe \
    images/a (15).jpe \
    images/a (16).jpeg \
    images/a (17).jpg \
    images/a (2).jpg \
    images/a (3).jpg \
    images/a (4).jpg \
    images/a (5).jpg \
    images/a (6).jpg \
    images/a (7).jpg \
    images/a (8).jpg \
    images/a (9).jpg \
    images/a18.jpg \
    images/cat.jpg \
    images/cattt.jpg \
    images/line.jpg \
    images/lonh.jpg \
    images/a (1).png \
    images/Customer Copy.png \
    images/CustomerService.png \
    images/ic_group.png \
    images/ic_lock.png \
    images/ic_user.png \
    images/icon_cut.png \
    images/icon_emoji.png \
    images/icon_file.png \
    images/icon_pic.png \
    QT-myChat-Client_zh_CN.ts

RESOURCES += \
    res.qrc \
    res.qrc \
    res.qrc \
    res.qrc \
    res.qrc

SUBDIRS += \
    QT-myChat-Client.pro
