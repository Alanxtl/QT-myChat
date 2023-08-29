#include "login.h"
#include "ui_login.h"
#include "regis.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <Tools/handler.h>
#include <qdebug.h>
#include <Database/UserInfo.h>
#include <QTime>
#include <QMessageBox>

//静态成员变量的类外初始化
login* login::log = NULL;

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->pwdtxt->setEchoMode(QLineEdit::Password);

    //    QTcpSocket socket;
    //    QString ip = "192.168.34.129";
    //    quint16 port = 6666;
    //    socket.connectToHost(QHostAddress(ip), port);
    //    if (socket.waitForConnected(5000)) {
    //        QMessageBox::about(this, "警告", "网络连接不成功");
    //    }
    connect(Handler::getObj(), &Handler::loginHandler, this, &login::login_success);
    connect(Handler::getObj(), &Handler::getLogMsg, this, &login::logHandler);


    QObject::connect(&Socket::getObj()->socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
        QString time = QString::number(QDateTime::currentDateTime().toTime_t());
        QByteArray originMessage = Socket::getObj()->socket.readAll();
        MyMsg* msg = MyMsg::arrayToMsg(originMessage);

        if (msg->type == 0) {
            QString str=ui->nametxt->text();
            QString str2=ui->pwdtxt->text();
            UserInfo user(str.toUInt(),QString::fromUtf8(msg->content),str2," ");
            Handler::getObj()->my = user;
            qDebug() << "return 0";
            login_success();
        } else if (msg->type == 8) {
            qDebug() << "return 8";
            logHandler(msg);
        } else if (msg->type == 1) {
            emit toBeContinued();
        } else if (msg->type == 9 && msg->slice == 2) {
            QString str = "添加好友失败";
            QMessageBox::about(this,"注意",str);
        } else if (msg->type == 9 && msg->slice == 1) {
            QString str = "添加好友成功";
            QMessageBox::about(this,"注意",str);
            if(DBHelper::GetInstance()->addFriendship(msg->senderID, QString::fromUtf8(msg->content))) {
                qDebug() << "success";
            } else {

                qDebug() << "add fail";
            }

            addFriendSignal();
        } else if (msg->type == 9 && msg->slice == 0) {
            QString str = QString::fromUtf8(msg->content) + "请求添加您好友";
            QMessageBox::about(this,"注意",str);
            if (true/*弹出窗口确认*/) {
                QString str = " ";
                MyMsg * msge = new MyMsg();
                QByteArray bytes = str.toUtf8();
                msge->setMsg(9,1,0,0,msg->receiverID,msg->senderID,QTime::currentTime(),bytes);

                QByteArray data = msge->msgToArray();
                Socket::getObj()->socket.write(data);
            } else {
                QString str = " ";
                MyMsg * msge = new MyMsg();
                QByteArray bytes = str.toUtf8();
                msge->setMsg(9,2,0,0,msg->receiverID,msg->senderID,QTime::currentTime(),bytes);

                QByteArray data = msge->msgToArray();
                Socket::getObj()->socket.write(data);
            }
        }
    });



}

//单例模式
login* login::GetInstance(){
    if (log == NULL) {
        log = new login;
    }
    return log;
}

login::~login()
{
    delete ui;
}

void login::logHandler(MyMsg *msg)
{
    QMessageBox::about(this, "注意", QString::fromUtf8(msg->content));
}

//go to mainwindow
void login::on_loginbth_clicked()
{
//        MainWindow *m=new MainWindow();
//        m->show();
//        this->hide();
    QString ip = ui->iptxt->text();

    Socket::getObj()->socket.connectToHost(QHostAddress(ip), 6666);
    Socket::getFileObj()->connectToHost(QHostAddress(ip),6667);

    if (Socket::getObj()->socket.waitForConnected(3000)/* && Socket::getFileObj()->waitForConnected(1000)*/) {

    }
    else {
        QMessageBox::about(this,"警告","服务器连接失败");
        return;

    }


    QString str=ui->pwdtxt->text();
    QString str2=ui->nametxt->text();
    if(str2.length()<1){
        QMessageBox::about(this,"警告","请输入用户名");
        return;
    }
    else if(str.length()<1)
    {
        QMessageBox::about(this,"警告","请输入密码");
        return;
    }

    MyMsg *msge = MyMsg::loginMsg(ui->nametxt->text().toUInt(), ui->pwdtxt->text().toUInt());
    QByteArray data = msge->msgToArray();
    Socket::getObj()->socket.write(data);

//    MainWindow *m=new MainWindow();
//    m->show();
//    this->hide();
}

void login::login_success()
{
    MainWindow *m=new MainWindow();
    connect(this,&login::sendmyid,m,&MainWindow::receivemyid);
    QString str=ui->pwdtxt->text();
    QString str2=ui->nametxt->text();
    emit this->sendmyid(str2);
    m->show();
    this->hide();
}

//go to gegister
void login::on_regbtn_clicked()
{
    QString ip = ui->iptxt->text();
    quint16 port = 6666;
    Socket::getObj()->socket.connectToHost(QHostAddress(ip), port);
    if (Socket::getObj()->socket.waitForConnected(3000)) {

    }
    else {
        QMessageBox::about(this,"警告","服务器连接失败");
        return;
    }

    regis *re=new regis();

    connect(this, &login::toBeContinued, re, &regis::register_success);

    re->show();
    this->hide();
}
//close
void login::on_exitbtn_clicked()
{
    this->close();
}

void login::on_jump_clicked()
{
    login_success();
}

void login::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        //显示Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->pwdtxt->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        //密
        ui->pwdtxt->setEchoMode(QLineEdit::Password);
    }
}
