#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <Tools/mymsg.h>
#include <Database/DBHelper.h>
#include <Database/UserInfo.h>
//#include <login.h>

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = nullptr);
    void check(MyMsg* msg);
    void registerHandler(MyMsg *msg);
    void defaultMsgHandler(MyMsg *msg);
    void groupMsgHandler(MyMsg *msg);
    void getMsg(MyMsg *msg);
    static Handler* getObj(); //单例模式
    UserInfo my;
signals:
    void loginHandler();
    void getLogMsg(MyMsg* msg);
private:
    static Handler* globleHandler;
};

#endif // HANDLER_H
