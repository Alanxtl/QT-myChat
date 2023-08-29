#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);
    static Socket* getObj(); //单例模式
    QTcpSocket socket;
signals:

public slots:

private:
    static Socket* globeSocket;
};

#endif // SOCKET_H
