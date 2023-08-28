#include "chatthread.h"

ChatThread::ChatThread(QThread *parent) : QThread{parent}
{

}

void ChatThread::run()
{
    emit showSignal();
}
