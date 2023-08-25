#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //链接日志类
    connect(Log::getLogObj(), &Log::readyShowLog, this, &MainWindow::showLog);
    //日志自动滚动
    connect(ui->logBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));

    //todo用户端登录监听
    //connect(, , this, updateClinetMonitor);

    //todo 数据库交互
    //DataDB::GetInstance();

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
