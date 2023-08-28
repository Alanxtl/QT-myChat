#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QTime>

/*
 *
 * 工具类log
 * 使用单例模式
 *
 * 想要输出日志使用以下方法即可：
 * Log::getLogObj()->writeLog("内容");
 *
 * 无其他调用方法
 *
 */

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);
    static Log* getLogObj(); //单例模式
    void writeLog(QString log);

signals:
    void readyShowLog(QString log);

private:
    static Log* globeLog;

};

#endif // LOG_H
