#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chapage.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Database/DBHelper.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(login::GetInstance(), &login::addFriendSignal, this, &MainWindow::showAllFriendship);
    ui->setupUi(this);
    ui->profilebtn->setIcon(QPixmap(QString(":/images/a (17).jpg")));
    ui->profilebtn->setIconSize(QSize(150,150));
    ui->fdsbtn->setText("好友");
    ui->fdsbtn->setIcon(QPixmap(QString(":/images/ic_user.png")));
    ui->groupbtn->setText("群组");
    ui->groupbtn->setIcon(QPixmap(QString(":/images/ic_group.png")));
    ui->fdsbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->groupbtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    this->setWindowIcon(QIcon(":/images/ab (1).jpg"));
    this->setWindowTitle("Linpop");
    
    MainWindow::showAllFriendship();

    ui->namebtn->setText(Handler::getObj()->my.getName());
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

void MainWindow::receivemyid(QString s){

    //ui->groupbtn->setText(s);
    this->myid =s;
    //ui->groupbtn->setText(this->myid);
}


void MainWindow::on_fdsbtn_customContextMenuRequested(const QPoint &pos)
{
    QMenu *fdsmenu=new QMenu(ui->fdsbtn);
    QAction *addfdsact=new QAction(tr("添加好友"),this);
    QAction *defdsact=new QAction(tr("删除好友"),this);
    fdsmenu->addAction(addfdsact);
    fdsmenu->addAction(defdsact);
    connect(addfdsact,&QAction::triggered, [=]{
        bool bOk = false;
        QString addid = QInputDialog::getText(this,
                                             "add_id",
                                             "请输入账号",
                                             QLineEdit::Normal,
                                             "11",
                                             &bOk
                                             );
    });
    connect(defdsact,&QAction::triggered, [=]{
        bool bOk = false;
        QString deleid = QInputDialog::getText(this,
                                             "delete_id",
                                             "请输入账号",
                                             QLineEdit::Normal,
                                             "11",
                                             &bOk
                                             );
    });
    fdsmenu->exec(QCursor::pos());
}

void MainWindow::showAllFriendship(){
    QVector<QToolButton*> vector;
    //好友列表
    QList<QByteArray> list = DBHelper::GetInstance()->selectAllFriendsUserInfo();
    //图片资源列表
    QStringList listIcon;
    QString str1_avatar = "a (";
    QString str2_avatar = ")";
    for(int i=0;i<list.size();i++){
        listIcon.append(str1_avatar + QString::number(i+1) + str2_avatar);
        QToolButton *btn=new QToolButton(this);
        btn->setIcon(QPixmap(QString(":/images/%1.jpg").arg(listIcon[i])));
        btn->setIconSize(QSize(80,80));
        //透明
        btn->setAutoRaise(true);
        //设置网名
        QString str1 = " ";
        QString str2 = "\r\nip：xxx.xx.xxx";
        btn->setText(QString::number(UserInfo::fromQByteArray(list[i]).getID()) + str1 + UserInfo::fromQByteArray(list[i]).getName() + str2);

        //设置显示格式
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->vlayout->addWidget(btn);
        vector.push_back(btn);
    }

    for(int i=0;i<list.size();i++){
        connect(vector[i],&QToolButton::clicked,[=](){
            chapage *chatp=new chapage();
            connect(this,&MainWindow::senddoubleid,chatp,&chapage::receivedoubleid);
            emit(senddoubleid(this->myid,QString::number(UserInfo::fromQByteArray(list[i]).getID())));
            chatp->setWindowIcon(vector[i]->icon());
            //chatp->setWindowTitle(vector[i]->text());
            chatp->show();
         });
    }
}
void MainWindow::receivemyid(QString s){

    //ui->groupbtn->setText(s);
    this->myid =s;
    //ui->groupbtn->setText(this->myid);
}

void MainWindow::on_groupbtn_clicked()
{
        chapage *chatp=new chapage();
        connect(this,&MainWindow::senddoubleid,chatp,&chapage::receivedoubleid);
        emit(senddoubleid(this->myid,NULL));
        //chatp->setWindowIcon(vector[i]->icon());
        chatp->setWindowTitle("群组聊天室");
        chatp->show();
}
