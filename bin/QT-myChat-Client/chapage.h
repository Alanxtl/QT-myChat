#ifndef CHAPAGE_H
#define CHAPAGE_H

#include <QMainWindow>
#include "qnchatmessage.h"
#include <QListWidgetItem>
#include <QFile>
#include <Tools/mymsg.h>

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
    void sendFile(QString filename);
    void updateSendedFileProgress(qint64 numBytes);
    void updateReceivedFileProgress();
    QString myid;
    QString othersid;
    void showRightFriendInfo();
public slots:
    void receivedoubleid(QString myid,QString othersid);
    void receiveTypeTwoMsg(MyMsg *msg);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    //void on_pushButton_clicked();

    void on_sendbtn_clicked();

    void on_pushButton_5_clicked();

    void on_cancelbt_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::chapage *ui;
    QFile *localFile;
    ///文件大小
    qint64 totalBytes;      //文件总字节数
    qint64 bytesWritten;    //已发送的字节数
    qint64 bytestoWrite;    //尚未发送的字节数
    qint64 filenameSize;    //文件名字的字节数
    qint64 bytesReceived;   //接收的字节数
    ///每次发送数据大小
    qint64 perDataSize;
    QString filename;
    ///数据缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

};

#endif // CHAPAGE_H
