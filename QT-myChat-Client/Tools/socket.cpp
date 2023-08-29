#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

Socket * Socket::globeSocket = nullptr;

Socket* Socket::getObj(){
    if(globeSocket == nullptr){
        globeSocket = new Socket();
    }
    return globeSocket;
}
