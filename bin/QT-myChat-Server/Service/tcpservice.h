#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include <QTcpServer>
#include <QDebug>
#include <Tools/log.h>

class TcpService : public QTcpServer
{
        Q_OBJECT

public:
    TcpService(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // TCPSERVICE_H
