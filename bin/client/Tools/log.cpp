#include "log.h"

Log::Log(QObject *parent)
    : QObject{parent}
{

}

Log * Log::globeLog = nullptr;

Log* Log::getLogObj(){
    if(globeLog == nullptr){
        globeLog = new Log();
    }
    return globeLog;
}

void Log::writeLog(QString log){
    emit readyShowLog(QTime::currentTime().toString() + " " + log);
}
