#include "tcpservice.h"

TcpService::TcpService(QObject *parent) : QTcpServer(parent){


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
            UserInfo user = DBHelper::GetInstance()->selectUserInfoById(msg->getSenderID());
            QString text = user.getName();
            QByteArray byte = text.toUtf8();
            MyMsg* send_msg = new MyMsg();
            quint32 id = msg->getSenderID();
            chatbusiness->id = msg->getSenderID();
            updateMap(id, chatbusiness->ip);
            send_msg->setMsg(0, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            TcpService::sendMessage(send_msg);
            DBHelper::GetInstance()->addOnlineUserInfo(user);
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
            UserInfo user = DBHelper::GetInstance()->selectUserInfoById(msg->getSenderID());
            QString text = "注册成功";
            QByteArray byte = text.toUtf8();
            MyMsg *send_msg = new MyMsg();
            send_msg->setMsg(1, 0, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
            QByteArray data = send_msg->msgToArray();
            chatbusiness->id = msg->getSenderID();
            TcpService::updateMap(chatbusiness->id, chatbusiness->ip);
            chatbusiness->socket.write(data);
            DBHelper::GetInstance()->addOnlineUserInfo(user);
        }
        break;

    case 2:
        updateMap(msg->getSenderID(), chatbusiness->ip);
        TcpService::sendMessage(msg);
        break;

    case 9:{
        quint8 slice = msg->getSlice();
        // 0 代表请求； 1 代表同意， 2代表不同意
        if (slice == 0) {
            updateMap(msg->getSenderID(), chatbusiness->ip);
            if (TcpService::searchOnMap(msg->getReceiverID()) == "") {
                MyMsg *send_msg = new MyMsg();
                QString text = "查无此人";
                QByteArray byte = text.toUtf8();
                send_msg->setMsg(8, 2, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
                TcpService::sendMessage(send_msg);
            }
            else {
                TcpService::sendMessage(msg);
            }
            break;
        }
        else if (slice == 1) {
            // 同意请求，服务期开始操作
            updateMap(msg->getSenderID(), chatbusiness->ip);
            if (Handler::getObj()->addFriend(msg)) {
                //添加成功
                MyMsg *send_msg = new MyMsg();
                UserInfo user = DBHelper::GetInstance()->selectUserInfoById(msg->getReceiverID());
                QString name = user.getName();
                QByteArray byte = name.toUtf8();
                send_msg->setMsg(9, 1, 0, 0, msg->getReceiverID(), msg->getSenderID(), QTime::currentTime(), byte);
                TcpService::sendMessage(send_msg);

                user = DBHelper::GetInstance()->selectUserInfoById(msg->getSenderID());
                name = user.getName();
                byte = name.toUtf8();
                send_msg->setMsg(9, 1, 0, 0, msg->getSenderID(), msg->getReceiverID(), QTime::currentTime(), byte);
                TcpService::sendMessage(send_msg);
                break;
            }
            else {
                //添加失败
                MyMsg *send_msg = new MyMsg;
                QString text = " ";
                QByteArray byte = text.toUtf8();
                send_msg->setMsg(8, 2, 0, 0, 0, msg->getSenderID(), QTime::currentTime(), byte);
                TcpService::sendMessage(send_msg);
                send_msg->setMsg(8, 2, 0, 0, 0, msg->getReceiverID(), QTime::currentTime(), byte);
                TcpService::sendMessage(send_msg);
                break;
            }
            break;
        }
        else {
            // 不同意请求，返回拒绝
            TcpService::sendMessage(msg);
            break;
        }
        break;
    }

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
