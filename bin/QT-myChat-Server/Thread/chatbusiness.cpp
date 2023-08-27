#include "chatbusiness.h"

ChatBusiness::ChatBusiness(qintptr handle, QObject *parent) : QObject{parent}
{
    connect(this, &ChatBusiness::startSignal, this, &ChatBusiness::mainBusiness);
    socketDescriptor = handle;
}

void ChatBusiness::mainBusiness()
{
    socket.setSocketDescriptor(socketDescriptor);
    QString peerAddress = socket.peerAddress().toString();
    Log::getLogObj()->writeLog("IP地址为"+peerAddress+"的用户已连接至服务端");
    QObject::connect(&socket, &QTcpSocket::readyRead, [&](){
        QByteArray originMessage = socket.readAll();
        QString textMessage = QString::fromUtf8(originMessage);
        Log::getLogObj()->writeLog("一个用户发来信息:"+textMessage);
    });
    //QObject::connect(socket, &QTcpSocket::readyRead, this, &ChatBusiness::handleMessage);
    //调用TCP业务
}


/*
 *  创建该线程基本示例：
 * 	ChatBusiness *chatBusiness = new chatBusiness();
 ×  QThread *thread = new thread();
 ×	chatBusiness->moveToThread(thread);
 ×	emit chatBusiness->startSignal();
 *
 *
 *  一个链接创建一个线程的代码：
 *  这一点可以通过继承QTcpServer，实现自己的MyTcpServer并重写incomingConnection(qintptr handle)来实现
 *  void MyTcpServer::incomingConnection(qintptr handle)
 ×  {
 ×     //基本示例
 ×     QThread *thread = new QThread(this);
 ×     ChatBusiness *chatBusiness = new ChatBusiness();
 ×     chatBusiness->moveToThread(thread);
 ×     //def handle of start
 ×     connect(chatBusiness, &ChatBusiness::startSignal, chatBusiness, &ChatBusiness::mainBusiness);
 ×     thread->start();
 ×     //send the SocketDescriptor
 ×     emit chatBusiness->startSignal();
 ×  }
 *
 *
 */
