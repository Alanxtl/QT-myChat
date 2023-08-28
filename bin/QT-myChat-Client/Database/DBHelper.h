#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include <QtNetwork>
#include <QSqlDatabase>
#include <QSqlError>

#include "ChatMessage.h"
#include "GroupInfo.h"
#include "UserInfo.h"
#include "Tools/mymsg.h"
#include "Tools/log.h"


class DBHelper : public QObject
{
    Q_OBJECT
public:
    explicit DBHelper(QObject *parent = nullptr);
    ~DBHelper();
    //查找好友
    UserInfo selectUserInfoById(const quint32 id);//存在返回true，不存在返回false
    //查询好友列表
    QList<QByteArray> selectAllFriendsUserInfo();
    //添加好友
    bool addFriendship(quint32 Id, QString name);//两个好友的Id
    //删除好友
    bool deleteFriendship(quint32 Id);//两个好友的Id

    //单例设计模式--应对数据库的对象的内存使用
    static DBHelper* GetInstance();

private:
    QSqlDatabase sqldb;
    static DBHelper* db;
};

#endif // DBHELPER_H
