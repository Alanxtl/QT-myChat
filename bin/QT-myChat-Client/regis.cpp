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

    QObject::connect(&Socket::getObj()->socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
        QByteArray originMessage = Socket::getObj()->socket.readAll();
        MyMsg* msg = MyMsg::arrayToMsg(originMessage);

        if (msg->type == 0) {
            register_success();
        } else if (msg->type == 8) {
            logHandler(msg);
        }
    });


}

regis::~regis()
{
    delete ui;
}

void regis::register_success()
{
    QMessageBox::about(this,"成功","注册成功已自动登录");
    MainWindow *m=new MainWindow();
    connect(this,&regis::sendmyid,m,&MainWindow::receivemyid);
    emit this->sendmyid(id);
    m->show();
    this->hide();
}

void regis::logHandler(MyMsg *msg)
{
    QMessageBox::about(this, "注意", QString::fromUtf8(msg->content));
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

    MyMsg *msge = MyMsg::loginMsg(ui->pwdtxt1->text().toUInt(), ui->pwdtxt2->text().toUInt(), ui->nametxt1->text());
    QByteArray data = msge->msgToArray();
    Socket::getObj()->socket.write(data);

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



