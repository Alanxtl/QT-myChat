#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

Socket * Socket::globeSocket = nullptr;
QTcpSocket * Socket::fileSocket = nullptr;

Socket* Socket::getObj(){
    if(globeSocket == nullptr){
        globeSocket = new Socket();
    }
    return globeSocket;
}

QTcpSocket* Socket::getFileObj(){
    if(fileSocket == nullptr){
        fileSocket = new QTcpSocket();
    }
    return fileSocket;
}
