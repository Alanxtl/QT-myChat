#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject{parent}
{

}

Handler * Handler::globeHandler = nullptr;

Handler* Handler::getObj(){
    if(globeHandler == nullptr){
        globeHandler = new Handler();
    }
    return globeHandler;
}

bool Handler::loginHandler(MyMsg *msg)
{
    quint32 id = msg->getSenderID();
    quint32 pwd = msg->getReceiverID();

    if(!DBHelper::GetInstance()->selectUserByIdAndPwd(QString::number(id),QString::number(pwd))) {
        //返回给客户端不成功
        return false;

    } else {
        //返回给客户端成功
        return true;
    }
}


bool Handler::registerHandler(MyMsg* msg)
{
    QByteArray content = msg->content;
    quint32 id = msg->getSenderID();
    quint32 pwd = msg->getReceiverID();
    QString name = QString::fromUtf8(content);

    UserInfo user(id, name,QString::number(pwd),"");

    if(!DBHelper::GetInstance()->registerUserInfo(user)) {
        return false;
        //返回给客户端注册不成功
    } else {
        return true;
        //返回给客户端注册成功
    }
}


void Handler::defaultMsgHandler(MyMsg *msg)
{

}

void Handler::groupMsgHandler(MyMsg *msg)
{

}
