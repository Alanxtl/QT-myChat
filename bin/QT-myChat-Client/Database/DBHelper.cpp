#include "DBHelper.h"

//静态成员变量的类外初始化
DBHelper* DBHelper::db = NULL;

//构造函数
DBHelper::DBHelper()

{
    //连接数据库操作
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName("server");
	if (!sqldb.open()) {
        QMessageBox::warning(NULL, "错误", "打开数据库时出现错误!", QMessageBox::Yes);
	}

	//初始化建表
	QSqlQuery query;
    //好友信息表(Id设置为5位)
    query.exec("DROP TABLE FriendInfo");
    if(!query.exec("CREATE TABLE IF NOT EXISTS FriendInfo ("
                  "Id INTEGER PRIMARY KEY, "
                  "Username VARCHAR(40) NOT NULL, "
                  "Avatar VARCHAR(512) )")){
        qDebug()<<query.lastError();
    }
	//建表完成

     //初始化好友列表
    if(!query.exec("INSERT INTO FriendInfo VALUES "
                  "(10001, 'xiaoming', ''), "
                  "(10002, 'xiaoli', ''), "
                  "(10003, 'xiaozhang', ''), "
                  "(10004, 'xiaohong', ''), "
                  "(10005, 'xiaohua', ''), "
                  "(10006, 'xiaosong', '')")){
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
//查询好友列表
QStringList DBHelper::selectAllFriendsUserInfo(){
    QSqlQuery query;
    query.exec("SELECT Id, Username FROM FriendInfo");
    QStringList list;
    list.clear();
    while(query.next()){
        list.append(QString(query.value("Id").toString())+QString(query.value("Username").toString()));
    }
    return list;
}

//获得不含密码的基本信息（返回UserInfo类型）
UserInfo DBHelper::selectUserInfoById(const quint32 id){
    QSqlQuery query;
    query.prepare("select * from FriendInfo where Id =:Id");
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
bool DBHelper::addFriendship(quint32 Id, QString name){
	QSqlQuery query;
    query.prepare("insert into FriendInfo values(:Id, :Username)");
    query.bindValue(":Id", QVariant(Id));
    query.bindValue(":Username", QVariant(name));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}

//删除好友
bool DBHelper::deleteFriendship(quint32 Id){
	QSqlQuery query;
    query.prepare("delete from FriendInfo where Id =:Id");
    query.bindValue(":Id", QVariant(Id));
    if(query.exec()){
        return true;
    }else{
        return false;
    }
}
//end对外功能接口
