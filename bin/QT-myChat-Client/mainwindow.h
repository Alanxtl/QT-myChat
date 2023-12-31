#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <Tools/mymsg.h>
#include <QToolButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<QByteArray> list;
    QStringList listIcon;
    QVector<QToolButton*> vector;

    QString myid;

    void iAmOnline(quint32 toID);
public slots:
    void receivemyid(QString s);
    void showAllFriendship();

signals:
    void senddoubleid(QString myid,QString othersid);

private slots:
    void on_fdsbtn_customContextMenuRequested(const QPoint &pos);
    void deletefds();
    void addfds(QString addid);
    void logHandler(MyMsg* msg);
    void on_groupbtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
