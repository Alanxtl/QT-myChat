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
#include <screenwidget.h>
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

//    MainWindow w;
//   w.show();
login::GetInstance()->show();
 //chapage chat;
 //chat.show();


    //ScreenWidget::Instance()->showFullScreen();   //直接调用实例

    return a.exec();
}
