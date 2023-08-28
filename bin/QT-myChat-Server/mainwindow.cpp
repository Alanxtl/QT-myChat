#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQuery"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //链接日志类
    connect(Log::getLogObj(), &Log::readyShowLog, this, &MainWindow::showLog);
    //日志自动滚动
    connect(ui->logBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
    //显示在线用户信息
    connect(DBHelper::GetInstance(), &DBHelper::addOnlineUserInfo,
            this, &MainWindow::showAllOnlineUserInfo);
    //todo用户端登录监听
    //connect(, , this, updateClinetMonitor);
    //todo 数据库交互
    //DataDB::GetInstance();
    tcpservice.listen(QHostAddress::Any, 6666);
    Log::getLogObj()->writeLog("服务端初始化成功");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showLog(QString str){
    ui->logBrowser->append(str);
}

void MainWindow::autoScroll() {
    QTextCursor cursor =  ui->logBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logBrowser->setTextCursor(cursor);
}

void MainWindow::updateClinetMonitor()
{
    ui->clientCountLabel->setText(QString::number(clientCount));
    //ui->clientBrowser->append()
}

//显示全部在线用户
void MainWindow::showAllOnlineUserInfo(const UserInfo& user){

    if(tcpservice.onlineUserMap.contains(user.getID())) {
        Log::getLogObj()->writeLog("用户" + QString::number(user.getID()) + "已链接过");
        return;
    }

    Log::getLogObj()->writeLog("用户连接成功 ID: " + QString::number(user.getID()) + " NAME: " + user.getName());

    QSqlQuery query;

    query.prepare("insert into OnlineUser values(:Id, :Username)");
    query.bindValue(":Id", user.getID());
    query.bindValue(":Username", user.getName());
    tcpservice.onlineUserMap[user.getID()] = user.getName();

    if(!query.exec())
    {
        qDebug()<<query.lastError();
        //Log::getLogObj()->writeLog(query.lastError());
    }


    QStringList horizontalHeaders;
    horizontalHeaders << QStringLiteral("id") << QStringLiteral("username");
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaders);
    ui->tableWidget->setColumnCount(2);

    int i=0;

    query.exec("select Id, Username from OnlineUser");

    if(!query.exec())
    {
        qDebug()<<query.lastError();
    } else {
        while(query.next()){
           ui->tableWidget->setRowCount(i+1);//设置表格行数
           ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
           ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
           ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
           i++;
       }
    }

    ui->clientCountLabel->setText(QString::number(i));

    ui->tableWidget->show();

    ui->tableWidget->resizeColumnsToContents();
}

