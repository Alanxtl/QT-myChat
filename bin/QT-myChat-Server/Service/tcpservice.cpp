#include "tcpservice.h"

TcpService::TcpService(QObject *parent) : QTcpServer(parent){
    onlineUserMap.insert(1, "172.20.10.10");
    onlineUserMap.insert(0, "172.20.10.9");
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
    connect(chatBusiness, &ChatBusiness::receiveSignal, this, &TcpService::judgeMessage);
    //connect(chatBusiness, &ChatBusiness::updateSignal, this, &TcpService::updateMap);
}

void TcpService::judgeMessage(MyMsg *msg, ChatBusiness *chatbusiness) {
    quint8 type = msg->getType();
    switch (type) {
    case 0:
        if (!Handler::getObj()->loginHandler(msg)) {
            QString text = "登录失败";
            QByteArray byte = text.toUtf8();
            MyMsg* send_msg = new MyMsg();
            send_msg->setMsg(8, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            QByteArray data = send_msg->msgToArray();
            chatbusiness->socket.write(data);
        }
        else {
            QString text = "登陆成功";
            QByteArray byte = text.toUtf8();
            MyMsg* send_msg = new MyMsg();
            quint32 id = msg->getSenderID();
            updateMap(id, chatbusiness->ip);
            send_msg->setMsg(0, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            TcpService::sendMessage(send_msg);
        }
        break;

    case 1:
        if (!Handler::getObj()->registerHandler(msg)) {
            QString text = "注册失败";
            QByteArray byte = text.toUtf8();
            MyMsg *send_msg = new MyMsg();
            send_msg->setMsg(8, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            QByteArray data = send_msg->msgToArray();
            chatbusiness->socket.write(data);
        }
        else {
            QString text = "注册成功";
            QByteArray byte = text.toUtf8();
            MyMsg *send_msg = new MyMsg();
            send_msg->setMsg(1, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            QByteArray data = send_msg->msgToArray();
            chatbusiness->socket.write(data);
        }

    case 2:
        updateMap(msg->getSenderID(), chatbusiness->ip);
        TcpService::sendMessage(msg);
        break;
    default:
        break;
    }
}

void TcpService::updateMap (quint32 id, QString ip) {
    //insert函数可以实现存在则更新，不存在则创建
    onlineUserMap.insert(id, ip);
}

void TcpService::sendMessage(MyMsg *msg) {
    // 查找接收人ip
    QString targetIP = TcpService::searchOnMap(msg->getReceiverID());
    if (targetIP == "") {
        // 目标用户不存在，直接退出
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

//QString TcpService::getPeerIP (MyMsg *msg, QTcpSocket socket) {
//    originAddress = socket.peerAddress().toString();  //获取连接用户的IP
//    if (originAddress.startsWith("::ffff:")) {
//        QHostAddress ipv4Address(originAddress.mid(7));
//        ip = ipv4Address.toString();
//    }
//    else {
//        ip = originAddress;
//    }       //获取最简的ip地址
//    emit updateSignal(id, ip);
//}
