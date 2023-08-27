#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{
    QString ip = ui->lineEdit_IP->text();
    quint16 port = "6666".toUShort();
    socket.connectToHost(QHostAddress(ip), port);
    if (socket.waitForConnected(3000)) {
        qDebug() << "Connected to the Host!";
        if_connect = 1;
    }
    else {
        qDebug() << "Failed to connect ip=" << ip << "   port=" << port;
    }
}



void MainWindow::on_pushButton_Send_clicked()
{
    if (if_connect == 0) {
        QMessageBox::about(this, "提示", "请先进行测试连接");
    }
    else {
        MyMsg *msg = MyMsg::defaultMsg(message);
        QByteArray data = msg->msgToArray();
        if (socket.waitForConnected(2000)){
            socket.write(data);
            QMessageBox::about(this, "提醒", "消息发送成功");
        }
        else {
            QMessageBox::about(this, "提醒", "消息未能发送");
        }

    }
}
