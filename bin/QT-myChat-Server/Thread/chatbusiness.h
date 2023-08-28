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
    void receiveSignal(MyMsg *msg);
    void startSignal();
    void updateSignal();
};

#endif // CHATBUSINESS_H
