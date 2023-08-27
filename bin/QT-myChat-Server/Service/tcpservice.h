#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include <QTcpServer>
#include <QDebug>
#include <Tools/log.h>
#include "Thread/chatbusiness.h"
#include "Thread/chatthread.h"
#include <QList>

class TcpService : public QTcpServer
{
        Q_OBJECT

public:
    explicit TcpService(QObject *parent = nullptr);
    void sendMessage();

    QList <ChatBusiness> business;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};



#endif // TCPSERVICE_H
