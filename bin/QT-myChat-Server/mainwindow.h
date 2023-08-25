#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <Tools/log.h>
#include <Thread/chatbusiness.h>
#include <Thread/chatthread.h>
#include <QCoreApplication>


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

public slots:
    void showLog(QString str);
    void autoScroll();
    void updateClinetMonitor();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
