#include "chatbusiness.h"

ChatBusiness::ChatBusiness(qintptr handle, QObject *parent) : QObject{parent}
{
    connect(this, &ChatBusiness::startSignal, this, &ChatBusiness::mainBusiness);
    socketDescriptor = handle;
}

void ChatBusiness::mainBusiness()
{
    socket.setSocketDescriptor(socketDescriptor);
    QString originAddress = socket.peerAddress().toString();  //获取连接用户的IP
    if (originAddress.startsWith("::ffff:")) {
        QHostAddress ipv4Address(originAddress.mid(7));
        ip = ipv4Address.toString();
    }
    else {
        ip = originAddress;
    }       //获取最简的ip地址
    Log::getLogObj()->writeLog("IP地址为"+ip+"的用户已连接至服务端");


    QObject::connect(&socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
        QByteArray originMessage = socket.readAll();
        MyMsg* msg = MyMsg::arrayToMsg(originMessage);
        emit receiveSignal(msg);

    });




//        QByteArray originMessage = socket.readAll();
//        QString textMessage = QString::fromUtf8(MyMsg::arrayToMsg(originMessage)->content);

//        UserInfo user(MyMsg::arrayToMsg(originMessage)->senderID,socket.peerAddress().toString(),"1","1");

//        if(textMessage == "") {
//            //在客户端每次连接会自动发一条msg信息用于更新自己的ip和id的对应信息
//            id = user.getID();
//            DBHelper::GetInstance()->addOnlineUserInfo(user);
//            return;
//        }

//        else {

//        }

//        Log::getLogObj()->writeLog(QString::number(MyMsg::arrayToMsg(originMessage)->senderID) + "发给" +
//                                   QString::number(MyMsg::arrayToMsg(originMessage)->receiverID)+ "信息: "+textMessage);





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
