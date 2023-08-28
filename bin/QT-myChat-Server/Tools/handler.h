#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include "mymsg.h"
#include "Database/DBHelper.h"

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = nullptr);
    void registerHandler(MyMsg* msg);
    void loginHandler(MyMsg* msg);
    void defaultMsgHandler(MyMsg* msg);
    void groupMsgHandler(MyMsg* msg);
    void fileHandler();
    void picHandler();
    void check(MyMsg* msg);
    static Handler* getObj(); //单例模式
private:
    static Handler* globeHandler;
signals:

};

#endif // HANDLER_H
