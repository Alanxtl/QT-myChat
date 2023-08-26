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
    QStringList header;
    header<<"id"<<"username"<<"ip";

    ui->tableWidget->setHorizontalHeaderLabels(header);

    QSqlQuery query;
    query.exec("select Id, Username, Ip from OnlineUser");

    int i=0;

    while(query.next()){
        ui->tableWidget->setRowCount(i+1);//设置表格行数
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        i++;
    }
}
