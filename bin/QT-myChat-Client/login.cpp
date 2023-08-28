#include "login.h"
#include "ui_login.h"
#include "regis.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->pwdtxt->setEchoMode(QLineEdit::Password);
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
