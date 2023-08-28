#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QThread>
#include <QObject>

class ChatThread : public QThread
{
    Q_OBJECT
public:
    explicit ChatThread(QThread *parent = nullptr);
    void run() override;
    qintptr socketDescriptor;

signals:
    void showSignal();
};

#endif // CHATTHREAD_H
