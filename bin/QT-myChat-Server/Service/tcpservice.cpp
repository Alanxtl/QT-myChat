#include "tcpservice.h"
#include "Thread/chatbusiness.h"
#include "Thread/chatthread.h"

TcpService::TcpService(QObject *parent) : QTcpServer(parent){}

void TcpService::incomingConnection(qintptr socketDescriptor){
    Log::getLogObj()->writeLog("Incoming connection, creating threads");
    QThread *thread = new QThread(this);
    ChatBusiness *chatBusiness = new ChatBusiness(socketDescriptor);
    chatBusiness->moveToThread(thread);
    //def handle of start
    connect(chatBusiness, &ChatBusiness::startSignal, chatBusiness, &ChatBusiness::mainBusiness);
    thread->start();
    //send the SocketDescriptor
    emit chatBusiness->startSignal();
}
