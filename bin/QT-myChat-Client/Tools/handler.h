#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <Tools/mymsg.h>

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(QObject *parent = nullptr);
    bool loginHandler();
    void check(MyMsg* msg);
    static Handler* getObj(); //单例模式
signals:

private:
    static Handler* globeHandler;

};

#endif // HANDLER_H
