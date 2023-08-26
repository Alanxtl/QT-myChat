#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{
    QTcpSocket socket;
    QString ip = ui->label_IP->text();
    long int port = ui->label_Port->text().toLong();
    socket.connectToHost(ip, port);
    if (socket.waitForConnected(3000)) {
        qDebug() << "Connected to the Host!";
    }
    else {
        qDebug() << "Failed to connect";
    }
}



void MainWindow::on_pushButton_Send_clicked()
{
    QTcpSocket socket;
    QString ip = ui->label_IP->text();
    QString port = ui->label_Port->text();
}
