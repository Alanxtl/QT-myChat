#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chapage.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->profilebtn->setIcon(QPixmap(QString(":/images/a (17).jpg")));
    ui->profilebtn->setIconSize(QSize(150,150));
    ui->fdsbtn->setText("好友");
    ui->fdsbtn->setIcon(QPixmap(QString(":/images/ic_user.png")));
    ui->groupbtn->setText("群组");
    ui->groupbtn->setIcon(QPixmap(QString(":/images/ic_group.png")));
    ui->fdsbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->groupbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
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
       vector.push_back(btn);
    }

    for(int i=0;i<list.size();i++){
        connect(vector[i],&QToolButton::clicked,[=](){
            chapage *chatp=new chapage();
            chatp->setWindowIcon(vector[i]->icon());
            chatp->setWindowTitle(vector[i]->text());
            chatp->show();
         });
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addfds(){

}

void MainWindow::logHandler(MyMsg *msg)
{

}

void MainWindow::deletefds(){

}



void MainWindow::on_fdsbtn_customContextMenuRequested(const QPoint &pos)
{
    QMenu *fdsmenu=new QMenu(ui->fdsbtn);
    QAction *addfdsact=new QAction(tr("添加好友"),this);
    QAction *defdsact=new QAction(tr("删除好友"),this);
    fdsmenu->addAction(addfdsact);
    fdsmenu->addAction(defdsact);
    connect(addfdsact,SIGNAL(triggred(bool)),this,SLOT(addfds()));
    connect(addfdsact,SIGNAL(triggred(bool)),this,SLOT(deletefds()));
    fdsmenu->exec(QCursor::pos());
}
