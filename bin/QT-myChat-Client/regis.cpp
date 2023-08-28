#include "regis.h"
#include "ui_regis.h"
#include "login.h"
#include <QString>
#include <QMessageBox>
regis::regis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");
}

regis::~regis()
{
    delete ui;
}


//go to login
void regis::on_regbtn_clicked()
{
    QString str=ui->pwdtxt2->text();
    if(str.length()<1)
    {
        QMessageBox::about(this,"警告","请输入密码");
        return;
    }
    login *log=new login();
    log->show();
    this->hide();
}

//close
void regis::on_exitbtn_clicked()
{
    this->close();
}

void regis::on_checkBox_clicked()
{
    return;
}



