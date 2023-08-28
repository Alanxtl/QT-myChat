#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "regis.h"
#include "chapage.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QMessageBox>
#include <Tools/socket.h>
#include <qdebug.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QT-myChat-Client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    QString ip = "172.20.10.9";
    quint16 port = 6666;
    Socket::getObj()->socket.connectToHost(QHostAddress(ip), port);
    if (Socket::getObj()->socket.waitForConnected(3000)) {

    }
    else {
        qDebug() << "ddd";
    }
//    MainWindow w;
//   w.show();
    login log;
    log.show();
// chapage chat;
// chat.show();
    return a.exec();
}
