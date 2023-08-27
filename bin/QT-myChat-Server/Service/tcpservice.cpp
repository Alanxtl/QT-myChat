#include "tcpservice.h"

TcpService::TcpService(QObject *parent) : QTcpServer(parent){
    //connect()
}

void TcpService::incomingConnection(qintptr socketDescriptor){
    QThread *thread = new QThread(this);
    ChatBusiness *chatBusiness = new ChatBusiness(socketDescriptor);
    chatBusiness->moveToThread(thread);
    //def handle of start
    thread->start();
    //send the SocketDescriptor
    emit chatBusiness->startSignal();
    //business.append(chatBusiness);
}

void TcpService::sendMessage() {

}
