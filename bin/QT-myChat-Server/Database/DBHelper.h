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
    //登录功能数据库
    bool selectUserByIdAndPwd(const QString username, const QString pwd);//存在返回true，不存在返回false
    UserInfo selectUserInfoById(const quint32 id);//存在返回true，不存在返回false

    //查询当前全部用户的数据库操作--静态sql
    QList<QByteArray> selectAllFriendsUserInfo(quint32 UserId);
    //注册
    bool registerUserInfo(const UserInfo& user);//
    //添加好友
    bool addFriendship(quint32 Id1,quint32 Id2);//两个好友的Id
    //删除好友
    bool deleteFriendship(quint32 Id1,quint32 Id2);//两个好友的Id
    //判断好友关系是否存在
    bool friendshipExist(quint32 Id1,quint32 Id2);
    //添加聊天信息
    bool addMsg(quint32 Id1,quint32 Id2,QString Msg,QString Date);//发送者的Id，接收者的Id，聊天信息，标准日期xxxx-xx-xx xx:xx:xx使用库获取日期
    //获取最大的Id值
    quint32 selectMaxId();

    //单例设计模式--应对数据库的对象的内存使用
    static DBHelper* GetInstance();

    //是否有离线消息
    bool checkOfflineMsg(quint32 receiverID);
    //添加离线消息
    bool addOfflineMsg(ChatMessage &msg);
    //获取离线消息
    QList<ChatMessage> getOfflineMsg(quint32 SenderID, quint32 ReceiverID);
    //删除离线消息
    bool dropOfflineMsg(quint32 SenderID, quint32 ReceiverID);

    //群组操作
    //添加群聊关系
    bool addGroupship(quint32 UserID,quint32 GroupID,quint32 UserPermission = 0);
    bool registerGroupInfo(const GroupInfo& Group);
    quint32 selectMaxGroupId();
    GroupInfo selectGroupInfoByID(quint32);
    // Id1用户ID,Id2群聊ID,返回Id1是否在Id2中
    bool groupshipExist(quint32 Id1, quint32 Id2);
    QList<QByteArray> selectAllGroupInfo(quint32 ID);
    QList<quint32> selectAllGroupMember(quint32 ID);

    //修改用户名和头像
    bool updUsername(quint32 ID,QString Username);
    bool updAvatar(quint32 ID,QString Avatar);

private:
    QSqlDatabase sqldb;
    static DBHelper* db;

signals:
    void addOnlineUserInfo(const UserInfo& username);


};

#endif // DBHELPER_H
