#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(Handler::getObj(), &Handler::getLogMsg, this, &MainWindow::logHandler);
    connect(Handler::getObj(), &Handler::loginMsg, this, &MainWindow::loginHandler);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{
    QString ip = ui->lineEdit_IP->text();
    quint16 port = 6666;
    socket.connectToHost(QHostAddress(ip), port);
    if (socket.waitForConnected(3000)) {
        qDebug() << "Connected to the Host!";
        MyMsg *msg = MyMsg::defaultMsg(ui->lineEdit_SelfID->text().toInt(), ui->lineEdit_TargetIP->text().toInt(), "");
        QByteArray data = msg->msgToArray();
        socket.write(data);

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
        QString message = ui->textEdit_Message->toPlainText();
        MyMsg *msg = MyMsg::defaultMsg(ui->lineEdit_SelfID->text().toInt(), ui->lineEdit_TargetIP->text().toInt(), message);
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

void MainWindow::logHandler(MyMsg *msg)
{
    QMessageBox::about(this, "注意", QString::fromUtf8(msg->content));
}

void MainWindow::loginHandler()
{
    //登录成功页面跳转
}
