#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <Tools/log.h>
#include <Tools/mymsg.h>
#include <Thread/chatbusiness.h>
#include <Thread/chatthread.h>
#include <Service/tcpservice.h>
#include <QHostAddress>
#include <Database/DBHelper.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    quint32 clientCount;
    TcpService tcpservice;


public slots:
    void showLog(QString str);
    void autoScroll();
    void updateClinetMonitor();
    void showAllOnlineUserInfo(const UserInfo&);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
