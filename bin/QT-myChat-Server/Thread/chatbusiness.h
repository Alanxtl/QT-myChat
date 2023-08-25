#ifndef CHATBUSINESS_H
#define CHATBUSINESS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class ChatBusiness : public QObject
{
    Q_OBJECT
public:
    explicit ChatBusiness(QObject *parent = nullptr);
    void mainBusiness();
signals:
    void startSignal();
};

#endif // CHATBUSINESS_H
