#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获得日志并写入 todo 日志类
    //connect(Log::GetLogObj(), &Log::readyShowLog, this, &Widget::showLog);
    //自动滚动日志区域
    connect(ui->logBrowser, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
    this->showLog("服务端初始化成功");

    //用户端登录监听
    //connect(, , this, updateClinetMonitor);

    //todo 数据库交互
    //DataDB::GetInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLog(QString str){
    ui->logBrowser->append(QTime::currentTime().toString() + " " + str);
}

void MainWindow::autoScroll() {
    QTextCursor cursor =  ui->logBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logBrowser->setTextCursor(cursor);
}

void MainWindow::updateClinetMonitor()
{



    ui->clientCountLabel->setText(QString::number(clientCount));
    ui->clientCountLabel->setText(QString::number(clientCount));
}
