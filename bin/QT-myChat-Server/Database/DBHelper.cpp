#include "DBHelper.h"

//静态成员变量的类外初始化
DBHelper* DBHelper::db = NULL;

//构造函数
DBHelper::DBHelper(QObject *parent)
    : QObject{parent}
{
    //连接数据库操作
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("server.db");
	if (!sqldb.open()) {
        QMessageBox::warning(NULL, "错误", "打开数据库时出现错误!", QMessageBox::Yes);
	}

	//初始化建表
	QSqlQuery query;
    //用户信息表(Id设置为5位)
    query.exec("DROP TABLE UserInfo");
    if(!query.exec("CREATE TABLE IF NOT EXISTS UserInfo ("
                  "Id INTEGER PRIMARY KEY, "
                  "Username VARCHAR(40) NOT NULL, "
                  "Pwd VARCHAR(40) NOT NULL, "
                  "Avatar VARCHAR(512) )")){
        qDebug()<<query.lastError() << "UserInfo";
    }

	//好友关系表
    query.exec("DROP TABLE Friendship");
    if(!query.exec("CREATE TABLE IF NOT EXISTS Friendship ("
                  "MyId INTEGER, "
                  "FriendId INTEGER, "
                  "FOREIGN KEY (MyId) REFERENCES UserInfo(Id),"
                  "FOREIGN KEY (FriendId) REFERENCES UserInfo(Id))")){
        qDebug()<<query.lastError() << "Friendship";
    }

	//离线消息列表（添加Group）
    query.exec("DROP TABLE OfflineMsg");
    if(!query.exec("CREATE TABLE IF NOT EXISTS OfflineMsg ("
                  "Sender INTEGER, "
                  "Reciever INTEGER, "
                  "Msg VARCHAR(512),"
                  "DT datetime NOT NULL,"
                  "FOREIGN KEY (Sender) REFERENCES UserInfo(Id),"
                  "FOREIGN KEY (Reciever) REFERENCES UserInfo(Id))")){
        qDebug()<<query.lastError() << "OfflineMsg";
    }

    //消息表（添加Group）
    query.exec("DROP TABLE Msg");
    if(!query.exec("CREATE TABLE IF NOT EXISTS Msg ("
                  "Sender INTEGER,"
                  "Reciever INTEGER,"
                  "Msg VARCHAR(512),"
                  "DT datetime NOT NULL,"
                  "FOREIGN KEY (Sender) REFERENCES UserInfo(Id),"
                  "FOREIGN KEY (Reciever) REFERENCES UserInfo(Id))")){
        qDebug()<<query.lastError() << "Msg";
    }

    //群聊信息表（Id设置为7位）
    query.exec("DROP TABLE GroupInfo");
    if(!query.exec("CREATE TABLE IF NOT EXISTS GroupInfo ("
                  "ID INTEGER PRIMARY KEY,"
                  "GroupName VARCHAR(40),"
                  "GroupAvatar VARCHAR(512))")){
        qDebug()<<query.lastError() << "GroupInfo";
    }

    //群聊成员表，包含用户权限：0代表普通群员，1代表管理员，2代表群主
    query.exec("DROP TABLE Groupship");
    if(!query.exec("CREATE TABLE IF NOT EXISTS Groupship("
                  "UserID INTEGER,"
                  "GroupID INTEGER,"
                  "UserPermission INTEGER NOT NULL,"
                  "FOREIGN KEY (UserID) REFERENCES UserInfo(Id),"
                  "FOREIGN KEY (GroupID) REFERENCES GroupInfo(ID))")){
        qDebug()<<query.lastError() << "Groupship";
    }

    //在线用户表
    query.exec("DROP TABLE OnlineUser");
    if(!query.exec("CREATE TABLE IF NOT EXISTS OnlineUser("
        "Id int PRIMARY KEY, "
        "Username varchar NOT NULL) ")){
        qDebug()<<query.lastError() << "OnlineUser";
    }
	//建表完成

    //初始用户表
    if(!query.exec("INSERT INTO UserInfo VALUES "
                      "(10001, 'xiaoming', 10001, ''), "
                      "(10002, 'xiaoli', 10002, ''), "
                      "(10003, 'xiaozhang', 10003, ''), "
                      "(10004, 'xiaohong', 10004, ''), "
                      "(10005, 'xiaohua', 10005, ''), "
                      "(10006, 'xiaosong', 10006, '')")){
            qDebug()<<query.lastError();

    }
}//构造函数

//析构函数
DBHelper::~DBHelper() {
    if (db != NULL) {
        delete db;
    }
}

//单例模式
DBHelper* DBHelper::GetInstance(){
	if (db == NULL) {
		db = new DBHelper;
	}
	return db;
}



//下面是该数据库对外提供的功能接口
//查询好友列表（返回一个包含User Info的QList）
QList<QByteArray> DBHelper::selectAllFriendsUserInfo(quint32 UserId){
	QSqlQuery query;
    query.prepare("select Id, Username, Avatar from UserInfo where Id in (select FriendId from Friendship where MyId =:UserId)");
	query.bindValue(":UserId", QVariant(UserId));
	query.exec();
	QList<QByteArray> ListUserInfo;
	ListUserInfo.clear();
	while (query.next()){
        ListUserInfo.append(UserInfo(query.value("Id").toInt(), query.value("Username").toString(),"",query.value("Avatar").toString()).toQByteArray());
	}
	return ListUserInfo;
}

//注册信息（注册检验）
bool DBHelper::registerUserInfo(const UserInfo& user){
    QSqlQuery query;
    query.prepare("select Username from UserInfo where Username = :Username");
    query.bindValue(":Username", user.getName());
    query.exec();
    if(query.next()){
        //QMessageBox::warning(NULL, "错误", "该用户名已存在", QMessageBox::Yes);
        return false;
    }else{
        query.clear();
        query.prepare("insert into UserInfo values(:Id,:Username,:pwd,:avatar)");
        query.bindValue(":Id", user.getID());
        query.bindValue(":Username", user.getName());
        query.bindValue(":pwd", user.getPwd());
        query.bindValue(":avatar", user.getAvatarName());
        if(query.exec()){
            //qDebug()<<query.lastError();
            return true;
        }else{
            qDebug()<<query.lastError();
            return false;
        }
    }
}

//登录验证(返回true/false)
bool DBHelper::selectUserByIdAndPwd(const QString id, const QString pwd){
	QSqlQuery query;
    query.prepare("select * from UserInfo where Id =:Id and pwd =:pwd");
    query.bindValue(":Id", QVariant(id));
	query.bindValue(":pwd", QVariant(pwd));
	query.exec();
	bool flag = query.next();
	return flag;
}

//获得不含密码的基本信息（返回UserInfo类型）
UserInfo DBHelper::selectUserInfoById(const quint32 id){
    QSqlQuery query;
    query.prepare("select * from UserInfo where Id =:Id");
    query.bindValue(":Id", QVariant(id));
    query.exec();
    UserInfo tmp;
    while(query.next()){
        tmp = UserInfo(query.value("Id").toUInt(),
                       query.value("Username").toString(),
                       "",
                       query.value("Avatar").toString()
                       );
    }
    return tmp;
}

//添加好友
bool DBHelper::addFriendship(quint32 Id1, quint32 Id2){
	QSqlQuery query;
	query.prepare("insert into Friendship values(:Id1,:Id2)");
	query.bindValue(":Id1", QVariant(Id1));
	query.bindValue(":Id2", QVariant(Id2));
    if(query.exec()){
        return true;
    }else{
        qDebug()<<query.lastError();
        return false;
    }
}

//删除好友
bool DBHelper::deleteFriendship(quint32 Id1, quint32 Id2){
	QSqlQuery query;
	query.prepare("delete from Friendship where MyId =:Id1 and FriendId =:Id2");
	query.bindValue(":Id1", QVariant(Id1));
	query.bindValue(":Id2", QVariant(Id2));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//添加消息
bool DBHelper::addMsg(quint32 Id1, quint32 Id2, QString Msg, QString Date){
	QSqlQuery query;
	query.prepare("insert into Msg values(:Id1,:Id2,:Msg,:Date)");
	query.bindValue(":Id1", QVariant(Id1));
	query.bindValue(":Id2", QVariant(Id2));
	query.bindValue(":Msg", Msg);
	query.bindValue(":Date", Date);
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//搜索最大Id并调用log输出
quint32 DBHelper::selectMaxId() {
	QSqlQuery query;
	query.exec("select MAX(Id) as Id from UserInfo");
    quint32 maxId = quint32(10000);
	while (query.next()) {
        maxId = query.value("Id").toUInt();
	}
    Log::getLogObj()->writeLog("[CurrentMaxID]" + QString::number(maxId));
    if(maxId>=quint32(10000)) return maxId;
    else return quint32(10000);
}

//添加群聊列表
bool DBHelper::addGroupship(quint32 UserID,quint32 GroupID,quint32 UserPermission){
    QSqlQuery query;
    query.prepare("insert into Groupship values(:UserID,:GroupID,:UserPermission)");
    query.bindValue(":UserID", QVariant(UserID));
    query.bindValue(":GroupID", QVariant(GroupID));
    query.bindValue(":UserPermission",QVariant(UserPermission));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//新建群聊
bool DBHelper::registerGroupInfo(const GroupInfo& GroupInfo){
    QSqlQuery query;
    query.prepare("insert into GroupInfo values(:Id,:Username,:avatar)");
    query.bindValue(":Id", QVariant(GroupInfo.getID()));
    query.bindValue(":Username", QVariant(GroupInfo.getName()));
    query.bindValue(":avatar", QVariant(GroupInfo.getAvatarName()));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//是否有离线信息
bool DBHelper::checkOfflineMsg(quint32 receiverID){
    QSqlQuery query;

}

//添加离线消息
bool DBHelper::addOfflineMsg(ChatMessage &msg){
    QSqlQuery query;
    query.prepare("insert into OfflineMsg values(:Sender,:Reciever,:Msg,:DT)");
    query.bindValue(":Sender",QVariant(msg.getSender()));
    query.bindValue(":Reciever",QVariant(msg.getReceiver()));
    query.bindValue(":Msg",QVariant(msg.getContent()));
    query.bindValue(":DT",QVariant(msg.getTimeStamp()));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//获取离线消息
QList<ChatMessage> DBHelper::getOfflineMsg(quint32 SenderID, quint32 ReceiverID){
    QList<ChatMessage> msg;
    msg.clear();
    QSqlQuery query;
    query.prepare("select * from OfflineMsg where Sender = :senderID and Reciever = :receiverID order by DT");
    query.bindValue(":senderID",QVariant(SenderID));
    query.bindValue(":receiverID",QVariant(ReceiverID));
    query.exec();
    while (query.next()) {
        ChatMessage nowmsg(query.value("Sender").toUInt(),query.value("Reciever").toUInt()
                           ,query.value("Msg").toString());
        nowmsg.getTimeStamp() = query.value("DT").toString();
        msg.append(nowmsg);
    }
    DBHelper::GetInstance()->dropOfflineMsg(SenderID, ReceiverID);
    return msg;
}

//删除离线消息
bool DBHelper::dropOfflineMsg(quint32 SenderID, quint32 ReceiverID){
    QSqlQuery query;
    query.prepare("delete from OfflineMsg where Sender = :sendid and Reciever = :receiveid");
    query.bindValue(":sendid",QVariant(SenderID));
    query.bindValue(":receiveid",QVariant(ReceiverID));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//查找最大群聊Id
quint32 DBHelper::selectMaxGroupId() {//群聊7位数
    QSqlQuery query;
    query.exec("select MAX(Id) as Id from GroupInfo");
    quint32 maxId = quint32(1000000);
    while (query.next()) {
        maxId = query.value("Id").toUInt();
    }
    Log::getLogObj()->writeLog("[CurrentMaxID]" + QString::number(maxId));
    if(maxId>=quint32(1000000)) return maxId;
    else return quint32(1000000);
}

//修改用户姓名
bool DBHelper::updUsername(quint32 ID, QString Username){
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Username = :Username WHERE ID = :ID");
    query.bindValue(":ID",QVariant(ID));
    query.bindValue(":Username",QVariant(Username));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//修改用户头像
bool DBHelper::updAvatar(quint32 ID, QString Avatar){
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET Avatar = :Avatar WHERE ID = :ID");
    query.bindValue(":ID",QVariant(ID));
    query.bindValue(":Avatar",QVariant(Avatar));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//根据Id查找群聊
GroupInfo DBHelper::selectGroupInfoByID(quint32 ID){
    QSqlQuery query;
    query.prepare("select * from GroupInfo where ID = :ID");
    query.bindValue(":ID",QVariant(ID));
    query.exec();
    GroupInfo tmp;
    while(query.next()){
        tmp = GroupInfo(query.value("Id").toUInt(),
                       query.value("GroupName").toString(),
                       "",
                       query.value("GroupAvatar").toString()
                       );
    }
    return tmp;
}

//查找朋友关系是否存在
bool DBHelper::friendshipExist(quint32 Id1,quint32 Id2){
    QSqlQuery query;
    //向数据库发送一个预编译语句
    query.prepare("select * from Friendship where MyId =:Id1 and FriendId =:Id2");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));
    query.exec();
    bool flag = query.next();
    return flag;
}

//查找群聊关系是否存在
bool DBHelper::groupshipExist(quint32 Id1, quint32 Id2){
    QSqlQuery query;
    //向数据库发送一个预编译语句
    query.prepare("select * from Groupship where UserId =:Id1 and GroupId =:Id2");
    query.bindValue(":Id1", QVariant(Id1));
    query.bindValue(":Id2", QVariant(Id2));
    query.exec();
    bool flag = query.next();
    return flag;
}

//查找全部的群聊信息
QList<QByteArray> DBHelper::selectAllGroupInfo(quint32 ID){
    QSqlQuery query;
    query.prepare("select Id,GroupName,GroupAvatar from GroupInfo where Id in (select GroupID from Groupship where UserId =:UserId)");
    query.bindValue(":UserId", QVariant(ID));
    query.exec();
    QList<QByteArray> ListGroupInfo;
    ListGroupInfo.clear();
    while (query.next()) {
        ListGroupInfo.append(UserInfo(query.value("Id").toInt(), query.value("GroupName").toString(),"",query.value("GroupAvatar").toString()).toQByteArray());
    }
    return ListGroupInfo;
}

//查找全部的群成员
QList<quint32> DBHelper::selectAllGroupMember(quint32 ID){
    QSqlQuery query;
    query.prepare("select UserId from Groupship where GroupID = :ID");
    query.bindValue(":ID",QVariant(ID));
    QList<quint32> ListGroupMember;
    ListGroupMember.clear();
    query.exec();
    while(query.next()){
        ListGroupMember.append(query.value("UserId").toUInt());
    }

    return ListGroupMember;
}
//end对外功能接口
