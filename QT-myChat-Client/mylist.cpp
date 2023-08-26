#include "mylist.h"
#include "ui_mylist.h"

mylist::mylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mylist)
{
    ui->setupUi(this);
    QVector<QToolButton*> vector;
    this->setWindowIcon(QIcon(":/images/a (1).jpg"));
    this->setWindowTitle("Linpop");
    //好友列表
    QStringList list;
    list<<"a (1)"<<"a (2)"<<"a (3)"<<"a (4)"<<"a (5)";
    //图片资源列表
    QStringList listIcon;
    listIcon<<"a (1)"<<"a (2)"<<"a (3)"<<"a (4)"<<"a (5)";

    for(int i=0;i<list.size();i++){
       QToolButton *btn=new QToolButton(this);
       btn->setIcon(QPixmap(QString(":/images/%1.jpg").arg(listIcon[i])));
       btn->setIconSize(QSize(80,80));
      //透明
       btn->setAutoRaise(true);
        //设置网名
       btn->setText("好友 name\r\nip：xxx.xx.xxx");

       //设置显示格式
       btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
       ui->vlayout->addWidget(btn);
    }

}

mylist::~mylist()
{
    delete ui;
}
