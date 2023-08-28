#include "tcpservice.h"

TcpService::TcpService(QObject *parent) : QTcpServer(parent){
    //connect()
    onlineUserMap.insert(1, "192.168.122.129");
    onlineUserMap.insert(0, "192.168.34.129");
}

void TcpService::incomingConnection(qintptr socketDescriptor){
    QThread *thread = new QThread(this);
    ChatBusiness *chatBusiness = new ChatBusiness(socketDescriptor);
    chatBusiness->moveToThread(thread);
    //def handle of start
    thread->start();
    //send the SocketDescriptor
    emit chatBusiness->startSignal();
    business.append(chatBusiness);
    connect(chatBusiness, &ChatBusiness::receiveSignal, this, &TcpService::sendMessage);
}

void TcpService::updateMap (quint32 id, QString ip) {
    //insert函数可以实现存在则更新，不存在则创建
    onlineUserMap.insert(id, ip);
}

void TcpService::sendMessage(MyMsg *msg) {
    // 查找接收人ip
    QString targetIP = TcpService::searchOnMap(msg->getReceiverID());
    if (targetIP == "") {
        // 目标用户存在，直接退出
        return;
    }
    else {
        for (ChatBusiness *chatbusiness : business){
            if (chatbusiness->ip == targetIP) {
                QByteArray data = msg->msgToArray();
                chatbusiness->socket.write(data);
            }
        }
    }

}

QString TcpService::searchOnMap(quint32 id) {
    QString defalutString = "";
    if (onlineUserMap.value(id, defalutString) == "") {
        return defalutString;
    }
    else {
        return onlineUserMap.value(id);
    }
}
