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

