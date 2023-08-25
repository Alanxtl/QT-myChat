#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

class DBHelper : public QObject
{
    Q_OBJECT

public:
    DBHelper(QObject *parent = nullptr);
    ~DBHelper();

    bool openDatabase();
    void closeDatabase();

    bool addUser(const QString &username, const QString &password, const QString &email, const QString &avatar);
    bool addFriend(int userId, int friendId);
    bool addGroup(const QString &groupName, int creatorId);
    bool addGroupMember(int groupId, int userId);
    bool addMessage(int senderId, int receiverId, int groupId, const QString &messageContent);

    bool deleteUser(int userId);
    bool deleteFriend(int userId, int friendId);
    bool deleteGroup(int groupId);
    bool deleteGroupMember(int groupId, int userId);
    bool deleteMessage(int messageId);


    int getUserIdByUsername(const QString &username);
    QString getUsernameById(int userId);
    QString getUserAvatarById(int userId);

    bool registerUser(const QString &username, const QString &password);
    bool checkUserLogin(const QString &username, const QString &password);
    bool storeMessage(int senderId, int receiverId, int groupId, const QString &messageContent);
    QList<QString> checkOfflineMessages(int userId);



private:
    QSqlDatabase m_db;

    bool executeQuery(const QString &query);
};

#endif // DBHELPER_H
