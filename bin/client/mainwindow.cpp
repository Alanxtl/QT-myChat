#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(Handler::getObj(), &Handler::getLogMsg, this, &MainWindow::logHandler);
    connect(Handler::getObj(), &Handler::loginMsg, this, &MainWindow::loginHandler);
    QObject::connect(&socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
        QByteArray originMessage = socket.readAll();
        MyMsg* msg = MyMsg::arrayToMsg(originMessage);
        QMessageBox::about(this, "消息", QString::fromUtf8(msg->getContent()));

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{
    QString ip = "172.20.10.9";
    quint16 port = 6666;
    socket.connectToHost(QHostAddress(ip), port);
    if (socket.waitForConnected(3000)) {
        QMessageBox::about(this,"提示","连接成功!");
//        在连接时传递id，暂不决定用不用
//        QString selfID = ui->lineEdit_SelfID->text();
//        QByteArray data = selfID.toUtf8();
//        socket.write(data);
        if_connect = 1;
    }
    else {
        QMessageBox::about(this,"提示","连接失败!");
    }
}



void MainWindow::on_pushButton_Send_clicked()
{
    if (if_connect == 0) {
        QMessageBox::about(this, "提示", "请先进行测试连接");
    }
    else {
        QString message = ui->textEdit_Message->toPlainText();
        QByteArray byte = message.toUtf8();
        MyMsg *msg;
        msg->setMsg(2, 0, 0, 0, ui->lineEdit_SelfID->text().toUInt(), ui->lineEdit_TargetIP->text().toUInt(), QTime::currentTime(), byte);
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
