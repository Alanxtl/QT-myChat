#include "login.h"
#include "ui_login.h"
#include "regis.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <Tools/handler.h>

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
//    QTcpSocket socket;
    QString ip = ui->iptxt->text();
    quint16 port = 6666;
    Socket::getObj()->socket.connectToHost(QHostAddress(ip), port);
    if (Socket::getObj()->socket.waitForConnected(3000)) {

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


    MainWindow *m=new MainWindow();
    m->show();
    this->hide();
}

void login::login_success()
{
    MainWindow *m=new MainWindow();
    m->show();
    this->hide();
}

//go to gegister
void login::on_regbtn_clicked()
{
    regis *re=new regis();
    re->show();
    this->hide();
}
//close
void login::on_exitbtn_clicked()
{
    this->close();
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
