#include "chatbusiness.h"

ChatBusiness::ChatBusiness(qintptr handle, QObject *parent) : QObject{parent}
{
    connect(this, &ChatBusiness::startSignal, this, &ChatBusiness::mainBusiness);
    socketDescriptor = handle;
}

void ChatBusiness::mainBusiness()
{
    QTcpSocket socket;
    if (socket.setSocketDescriptor(socketDescriptor)){
        QDebug << "Connected successful!";
    }
    else {
        QDebug << "Failed to connect!";
    }


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
