#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "regis.h"
#include "chapage.h"
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
    MainWindow w;
   w.show();
    login log;
    log.show();
 chapage chat;
 chat.show();
    return a.exec();
}
