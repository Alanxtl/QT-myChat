#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>
#include <Tools/mymsg.h>
#include "Tools/handler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket socket;
    int if_connect = 0;

private slots:

    void on_pushButton_test_clicked();
    void on_pushButton_Send_clicked();
    void logHandler(MyMsg* msg);
    void loginHandler();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
