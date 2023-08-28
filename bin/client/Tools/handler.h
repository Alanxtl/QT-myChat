#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QMessageBox>
#include "mymsg.h"


class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = nullptr);
    static Handler* getObj(); //单例模式

signals:
    void getLogMsg(MyMsg* msg);
    void loginMsg();

private:
    static Handler* globleHandler;

};

#endif // HANDLER_H
