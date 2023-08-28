#include "login.h"
#include "ui_login.h"
#include "regis.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->pwdtxt->setEchoMode(QLineEdit::Password);

    QTcpSocket socket;
    QString ip = "192.168.34.129";
    quint16 port = 6666;
    socket.connectToHost(QHostAddress(ip), port);
    if (socket.waitForConnected(5000)) {
        QMessageBox::about(this, "警告", "网络连接不成功");
    }
}

login::~login()
{
    delete ui;
}


//go to mainwindow
void login::on_loginbth_clicked()
{
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
