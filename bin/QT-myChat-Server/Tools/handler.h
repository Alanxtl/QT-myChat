#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <Tools/mymsg.h>
#include <Database/UserInfo.h>
#include <Database/DBHelper.h>

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = nullptr);

    void check(MyMsg* msg);
    static Handler* getObj(); //单例模式
    bool registerHandler(MyMsg *msg);
    bool loginHandler(MyMsg *msg);
    void defaultMsgHandler(MyMsg *msg);
    void groupMsgHandler(MyMsg *msg);
signals:

private:
    static Handler* globeHandler;

};

#endif // HANDLER_H
