#include "handler.h"

Handler::Handler(QObject *parent)
    : QObject{parent}
{

}

Handler * Handler::globleHandler = nullptr;

Handler* Handler::getObj(){
    if(globleHandler == nullptr){
        globleHandler = new Handler();
    }
    return globleHandler;
}

void Handler::defaultMsgHandler(MyMsg *msg)
{

}

void Handler::groupMsgHandler(MyMsg *msg)
{

}

void Handler::getMsg(MyMsg *msg)
{
    switch(msg->type) {
    case 1:{emit Handler::loginHandler();}
    }
}
