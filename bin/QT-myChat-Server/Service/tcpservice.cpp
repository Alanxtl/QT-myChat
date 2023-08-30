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
    QString str_sid = QString::number(msg->getSenderID());
    QString str_rid = QString::number(msg->getReceiverID());
    QString str_type = QString::number(msg->getType());
    QString str_slice = QString::number(msg->getSlice());
    QString content = QString::fromUtf8(msg->getContent());
    qDebug()  << "服务器接受信息" + str_sid + "向" + str_rid + "发送了type为" + str_type + "slice为" + str_slice + "内容为" + content;
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
            //UserInfo user(text,ip,"","");
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

    case 2:{
        updateMap(msg->getSenderID(), chatbusiness->ip);
        TcpService::sendMessage(msg);
        ChatMessage message(msg->getSenderID(), msg->getReceiverID(), QString::fromUtf8(msg->getContent()));
        if (!DBHelper::GetInstance()->addOfflineMsg(message)) {
            quint32 SenderID = msg->getReceiverID();
            quint32 ReceiverID = msg->getSenderID();
            QString text = "离线信息存储失败";
            msg->setMsg(8, 0, 0, 0, SenderID, ReceiverID, QTime::currentTime(), text.toUtf8());
            TcpService::sendMessage(msg);
        }


        break;
    }
    case 4:{
        updateMap(msg->getSenderID(), chatbusiness->ip);
        TcpService::sendMessage(msg);
    }

    case 7:{
        for (ChatBusiness* chat : business) {
            if (chat->id != msg->getSenderID()) {
                MyMsg *newmsg = new MyMsg();
                newmsg->setMsg(2, 0, 0, 0, msg->getSenderID(), chat->id, QTime::currentTime(), msg->getContent());
                TcpService::sendMessage(newmsg);
            }
        }
        break;
    }

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
    case 10:{
        QList <ChatMessage> chatList;
        chatList = DBHelper::GetInstance()->getOfflineMsg(msg->getReceiverID(), msg->getSenderID());
        for (ChatMessage chat : chatList) {
            qDebug() << QString::number(chatList.size());
            MyMsg *message = new MyMsg();
//            QString fulltime = chat->getTimeStamp();
//            qDebug() << fulltime;
//            QString parttime = fulltime.mid(10, 8);
//            qDebug() << parttime;
//            QTime time = QTime::fromString(parttime, "hh:mm:ss");
//            qDebug() << "time ok";
            QString text = chat.getContent();
            message->setMsg(2, 0, 0, 0, chat.getSender() , chat.getReceiver(), QTime::currentTime(), text.toUtf8());
            TcpService::sendMessage(message);
            qDebug() << "send ok";
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

                quint64 check = chatbusiness->socket.write(data);
                QString str_sid = QString::number(msg->getSenderID());
                QString str_rid = QString::number(msg->getReceiverID());
                QString str_type = QString::number(msg->getType());
                QString str_slice = QString::number(msg->getSlice());
                QString content = QString::fromUtf8(msg->getContent());
                qDebug() << QString::number(check);
                Log::getLogObj()->writeLog("服务器进行转发和发送" + str_sid + "向" + str_rid + chatbusiness->ip + "发送了type为" + str_type + "slice为" + str_slice + "内容为" + content);
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
