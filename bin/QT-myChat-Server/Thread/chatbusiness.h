#ifndef CHATBUSINESS_H
#define CHATBUSINESS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <Tools/log.h>
#include <QDebug>

class ChatBusiness : public QObject
{
    Q_OBJECT
public:
    explicit ChatBusiness(qintptr handle, QObject *parent = nullptr);
    void mainBusiness();
    qintptr socketDescriptor;
signals:
    void startSignal();
};

#endif // CHATBUSINESS_H
