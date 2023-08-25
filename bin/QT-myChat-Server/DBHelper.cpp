#include "DBHelper.h"

DBHelper::DBHelper(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Server.db");
}

DBHelper::~DBHelper()
{
    closeDatabase();
}

bool DBHelper::openDatabase()
{
    if (!m_db.open())
    {
        qDebug() << "Failed to open database.";
        return false;
    }
    return true;
}

void DBHelper::closeDatabase()
{
    m_db.close();
}

bool DBHelper::executeQuery(const QString &query)
{
    QSqlQuery sqlQuery;
    if (!sqlQuery.exec(query))
    {
        qDebug() << "Failed to execute query:" << query;
        qDebug() << "Error detail:" << sqlQuery.lastError().text();
        return false;
    }
    return true;
}

bool DBHelper::addUser(const QString &username, const QString &password, const QString &email, const QString &avatar)
{
    QString query = QString("INSERT INTO User (username, password, email, avatar) "
                            "VALUES ('%1', '%2', '%3', '%4');")
                        .arg(username).arg(password).arg(email).arg(avatar);
    return executeQuery(query);
}

bool DBHelper::addFriend(int userId, int friendId)
{
    QString query = QString("INSERT INTO Friend (user_id, friend_id) "
                            "VALUES (%1, %2);").arg(userId).arg(friendId);
    return executeQuery(query);
}

bool DBHelper::addGroup(const QString &groupName, int creatorId)
{
    QString query = QString("INSERT INTO Group (group_name, creator_id) "
                            "VALUES ('%1', %2);").arg(groupName).arg(creatorId);
    return executeQuery(query);
}

bool DBHelper::addGroupMember(int groupId, int userId)
{
    QString query = QString("INSERT INTO GroupMember (group_id, user_id) "
                            "VALUES (%1, %2);").arg(groupId).arg(userId);
    return executeQuery(query);
}

bool DBHelper::addMessage(int senderId, int receiverId, int groupId, const QString &messageContent)
{
    QString query = QString("INSERT INTO Message (sender_id, receiver_id, group_id, message_content) "
                            "VALUES (%1, %2, %3, '%4');")
                        .arg(senderId).arg(receiverId).arg(groupId).arg(messageContent);
    return executeQuery(query);
}

bool DBHelper::deleteUser(int userId)
{
    QString query = QString("DELETE FROM User WHERE id = %1;").arg(userId);
    return executeQuery(query);
}

bool DBHelper::deleteFriend(int userId, int friendId)
{
    QString query = QString("DELETE FROM Friend WHERE (user_id = %1 AND friend_id = %2) OR (user_id = %2 AND friend_id = %1);")
                        .arg(userId).arg(friendId);
    return executeQuery(query);
}

bool DBHelper::deleteGroup(int groupId)
{
    QString query = QString("DELETE FROM Group WHERE id = %1;").arg(groupId);
    return executeQuery(query);
}

bool DBHelper::deleteGroupMember(int groupId, int userId)
{
    QString query = QString("DELETE FROM GroupMember WHERE group_id = %1 AND user_id = %2;").arg(groupId).arg(userId);
    return executeQuery(query);
}

bool DBHelper::deleteMessage(int messageId)
{
    QString query = QString("DELETE FROM Message WHERE id = %1;").arg(messageId);
    return executeQuery(query);
}

int DBHelper::getUserIdByUsername(const QString &username)
{
    int userId = -1;
    QString query = QString("SELECT id FROM User WHERE username = '%1';").arg(username);
    QSqlQuery sqlQuery(query);
    if (sqlQuery.next())
    {
        userId = sqlQuery.value(0).toInt();
    }
    return userId;
}

QString DBHelper::getUsernameById(int userId)
{
    QString username;
    QString query = QString("SELECT username FROM User WHERE id = %1;").arg(userId);
    QSqlQuery sqlQuery(query);
    if (sqlQuery.next())
    {
        username = sqlQuery.value(0).toString();
    }
    return username;
}

QString DBHelper::getUserAvatarById(int userId)
{
    QString avatar;
    QString query = QString("SELECT avatar FROM User WHERE id = %1;").arg(userId);
    QSqlQuery sqlQuery(query);
    if (sqlQuery.next())
    {
        avatar = sqlQuery.value(0).toString();
    }
    return avatar;
}

// 用户注册
bool DBHelper::registerUser(const QString &username, const QString &password)
{
    // 检查用户名是否已存在
    QString checkQuery = QString("SELECT id FROM User WHERE username = '%1';").arg(username);
    QSqlQuery sqlQuery(checkQuery);
    if (sqlQuery.next())
    {
        qDebug() << "Username already exists.";
        return false;
    }

    // 执行插入操作，注册新用户
    QString insertQuery = QString("INSERT INTO User (username, password) VALUES ('%1', '%2');").arg(username).arg(password);
    return executeQuery(insertQuery);
}

// 用户登录检查
bool DBHelper::checkUserLogin(const QString &username, const QString &password)
{
    QString query = QString("SELECT id FROM User WHERE username = '%1' AND password = '%2';").arg(username).arg(password);
    QSqlQuery sqlQuery(query);
    return sqlQuery.next();
}

// 信息存储
bool DBHelper::storeMessage(int senderId, int receiverId, int groupId, const QString &messageContent)
{
    QString query = QString("INSERT INTO Message (sender_id, receiver_id, group_id, message_content) "
                            "VALUES (%1, %2, %3, '%4');")
                    .arg(senderId).arg(receiverId).arg(groupId).arg(messageContent);
    return executeQuery(query);
}

// 检查是否有离线信息
QList<QString> DBHelper::checkOfflineMessages(int userId)
{
    QList<QString> offlineMessages;

    // 查询离线消息
    QString query = QString("SELECT message_content FROM Message WHERE receiver_id = %1;").arg(userId);
    QSqlQuery sqlQuery(query);
    while (sqlQuery.next())
    {
        QString messageContent = sqlQuery.value(0).toString();
        offlineMessages.append(messageContent);
    }

    // 删除已读的离线消息
    QString deleteQuery = QString("DELETE FROM Message WHERE receiver_id = %1;").arg(userId);
    executeQuery(deleteQuery);

    return offlineMessages;
}