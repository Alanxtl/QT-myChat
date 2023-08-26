#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMysql");
    db.setHostName("localhost");
    db.setDatabaseName("newdb");
    db.setUserName("linuxuser");
    db.setPassword("linux123456");

    if (db.open()) {
        qDebug() << "Connected to Database";
    }
    else {
        qDebug() << "Failed to connect";
    }


    return a.exec();
}
