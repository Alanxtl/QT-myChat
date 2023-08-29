#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <Tools/mymsg.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString *string);
    ~MainWindow();
    QString myid;
public slots:
    void receivemyid(QString s);
signals:
    void senddoubleid(QString myid,QString othersid);


private slots:
    void on_fdsbtn_customContextMenuRequested(const QPoint &pos);
    void deletefds();
    void addfds();
    void logHandler(MyMsg* msg);


    void on_groupbtn_clicked();

private:
    Ui::MainWindow *ui;
    QString *string;
};
#endif // MAINWINDOW_H
