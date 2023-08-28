#ifndef CHAPAGE_H
#define CHAPAGE_H

#include <QMainWindow>
#include "qnchatmessage.h"
#include <QListWidgetItem>

namespace Ui {
class chapage;
}

class chapage : public QMainWindow
{
    Q_OBJECT

public:
    explicit chapage(QWidget *parent = nullptr);
    ~chapage();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    //void on_pushButton_clicked();

    void on_sendbtn_clicked();

private:
    Ui::chapage *ui;
};

#endif // CHAPAGE_H
