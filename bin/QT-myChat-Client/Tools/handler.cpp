#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject{parent}
{

}

bool Handler::loginHandler()
{

}


void Handler::registerHandler(MyMsg* msg)
{
    QByteArray content = msg->content;
    QDataStream in(content);
    in.setVersion(QDataStream::Qt_5_9);

    quint32 id;
    in >> id;

    quint32 pwd;
    in >> pwd;

    UserInfo user(id,QString::number(id),QString::number(pwd),"");

//    if(!DBHelper::GetInstance()->registerUserInfo(user)) {
//        //返回给客户端不成功
//    } else {
//        //返回给客户端成功
//    }
}

void Handler::loginHandler(MyMsg* msg)
{
    QByteArray content = msg->content;
    QDataStream in(content);
    in.setVersion(QDataStream::Qt_5_9);

    quint32 id;
    in >> id;

    quint32 pwd;
    in >> pwd;

    if(!DBHelper::GetInstance()->selectUserByIdAndPwd(QString::number(id), QString::number(pwd))) {
        //返回给客户端不成功
    } else {
        //返回给客户端成功
    }
}

void Handler::defaultMsgHandler(MyMsg *msg)
{

}

void Handler::groupMsgHandler(MyMsg *msg)
{

}
