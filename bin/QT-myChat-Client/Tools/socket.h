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
    static QTcpSocket* getFileObj(); //单例模式
    QTcpSocket socket;
signals:

public slots:

private:
    static Socket* globeSocket;
    static QTcpSocket *fileSocket;
};

#endif // SOCKET_H
