#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include <QTcpServer>
#include <QDebug>
#include <Tools/log.h>
#include "Thread/chatbusiness.h"
#include "Thread/chatthread.h"
#include "Database/ChatMessage.h"
#include <QList>
#include <Tools/mymsg.h>
#include <Tools/handler.h>
#include <Database/UserInfo.h>
#include <Database/DBHelper.h>
#include <QTime>
#include <QThread>

class TcpService : public QTcpServer
{
        Q_OBJECT

public:
    explicit TcpService(QObject *parent = nullptr);
    QList <ChatBusiness*> business;
    QMap<quint32, QString> onlineUserMap;
    void updateMap(quint32 id, QString ip);
    QString searchOnMap(quint32 id);
    void sendMessage(MyMsg *msg) ;
    void judgeMessage(MyMsg *msg, ChatBusiness *chatbusiness);
    QString getPeerIP (MyMsg *msg, QTcpSocket socket);


protected:
    void incomingConnection(qintptr socketDescriptor) override;

};



#endif // TCPSERVICE_H
