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
    QString ip = "192.168.34.129";
    quint16 port = 6666;
    Socket::getObj()->socket.connectToHost(QHostAddress(ip), port);
//    MainWindow w;
//   w.show();
    login log;
    log.show();
// chapage chat;
// chat.show();
    return a.exec();
}
