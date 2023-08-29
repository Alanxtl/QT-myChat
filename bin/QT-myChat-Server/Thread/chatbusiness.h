#ifndef CHATBUSINESS_H
#define CHATBUSINESS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <Tools/log.h>
#include <QHostAddress>
#include <Tools/mymsg.h>
#include <Database/DBHelper.h>


class ChatBusiness : public QObject
{
    Q_OBJECT


public:
    explicit ChatBusiness(qintptr handle, QObject *parent = nullptr);
    void mainBusiness();
    qintptr socketDescriptor;
    QTcpSocket socket;
    QString ip;
    quint32 id;

signals:
    void receiveSignal(MyMsg *msg, ChatBusiness *chatbusiness);
    void startSignal();
    void updateSignal(quint32 id, QString ip);
};

#endif // CHATBUSINESS_H
