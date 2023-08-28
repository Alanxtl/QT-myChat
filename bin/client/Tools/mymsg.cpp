#include "mymsg.h"


/*
 * 标准QByteArray信息格式|32header|?body|
 *
 * header总共32字节包括以下内容:
 *          dataSize    : 占 4 个字节, quint32, 用于验证是否完整接收到了数据包
 *          identify    : 占 4 个字节, quint32, 用于验证是不是该程序的数据包，是一个默认的常量
 *          type        : 占 1 个字节, quint8, 用于标识数据包类型
 *                 数据包类型及代码如下：0-注册信息 1-登录信息 2-普通信息 3-图片信息 4-文件信息 6-错误
 *  不一定做 slice       : 占 1 个字节，quint8，用以指示该信息是否为切片信息，若非切片信息以下两条数据应为0
 *  不一定做 sliceTotal  : 占 4 个字节, quint32, 用以指示切片信息切片总数
 *  不一定做 sliceCount  : 占 4 个字节, quint32, 用以指示该切片信息是第几个切片
 *          senderID    : 占 4 个字节, quint32, 用于表示发送者的id
 *          receiverID  : 占 4 个字节, quint32, 用于表示接收者的id
 *          time        : 占 4 个字节, QTime, 用于表示发送的时间
 *
 *
 *
 * 接下来是正文部分：所占空间未定，由dataSize来指示
 *      但是根据type的不同定义有所不同
 *
 *      注册信息的body定义： todo
 *
 *      登录信息的body定义： todo
 *
 *      普通信息的body定义： todo
 *
 *      图片信息的body定义： todo
 *
 *      文件信息的body定义： todo
 *
 *
 */

MyMsg::MyMsg(QObject *parent)
    : QObject{parent}
{

}

MyMsg* MyMsg::setMsg(quint8 type, quint8 slice, quint32 sliceTotal, quint32 sliceCount, quint32 senderID, quint32 receiverID, QTime time, const QByteArray &content)
{
    this->type = type;
    this->slice = slice;
    this->sliceTotal = sliceTotal;
    this->sliceCount = sliceCount;
    this->senderID = senderID;
    this->receiverID = receiverID;
    this->time = time;
    this->content = content;

    return this;
}


MyMsg* MyMsg::arrayToMsg(const QByteArray &full_received)
{
    QDataStream in(full_received);
    in.setVersion(QDataStream::Qt_5_9);
    MyMsg * res = new MyMsg();

    //将数据从type_and_content中拿出来
    quint32 dataSize;
    in >> dataSize;
    //假如数据不完整, 停止读取
    if(full_received.size() - sizeof(quint32) < dataSize){

        return res->setMsg( 6, 0, 0, 0, 0, 0, QTime::currentTime(), QByteArray() );
    }

    //如果不是该程序的数据,也停止读取
    quint32 head;
    in >> head;
    if(head != IDENTIFY){
        return res->setMsg( 6, 0, 0, 0, 0, 0, QTime::currentTime(), QByteArray() );
    }

    //读取类型
    quint8 tmp_type;
    in >> tmp_type;

    //读取是否切片
    quint8 sliceOrNot;
    in >> sliceOrNot;

    //读取切片总数
    quint32 tmp_sliceTotal;
    in >> tmp_sliceTotal;

    //读取切片是第几个
    quint32 tmp_sliceCount;
    in >> tmp_sliceCount;

    //读取发送者id
    quint32 tmp_sender;
    in >> tmp_sender;

    //读取接收者id
    quint32 tmp_receiver;
    in >> tmp_receiver;

    //读取时间
    QTime tmp_time;
    in >> tmp_time;

    //读取正文
    QByteArray content;
    in >> content;

    return res->setMsg(tmp_type, sliceOrNot, tmp_sliceTotal, tmp_sliceCount, tmp_sender, tmp_receiver, tmp_time, content);
}

QByteArray MyMsg::msgToArray()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << quint32(0);
    out << quint32(IDENTIFY);
    out << quint8(type);
    out << quint8(slice);
    out << quint32(sliceTotal);
    out << quint32(sliceCount);
    out << quint32(senderID);
    out << quint32(receiverID);
    out << QTime(time);
    out << content;

    out.device()->seek(0);
    out << (quint32)(block.size()-sizeof(quint32));





    return block;
}

MyMsg* MyMsg::defaultMsg(quint32 fromID, quint32 toID, QString str)
{
    MyMsg * res = new MyMsg();
    QByteArray bytes = str.toUtf8();
    res->setMsg(1,0,0,0,fromID,toID,QTime::currentTime(),bytes);
    return res;
}

MyMsg* MyMsg::logMsg(quint32 fromID, quint32 toID, QString str)
{
    MyMsg * res = new MyMsg();
    QByteArray bytes = str.toUtf8();
    res->setMsg(7,0,0,0,fromID,toID,QTime::currentTime(),bytes);
    return res;
}

quint32 MyMsg::getDataSize()
{
    return this->dataSize;
}

quint8 MyMsg::getType()
{
    return this->type;
}

quint8 MyMsg::getSlice()
{
    return this->slice;
}

quint32 MyMsg::getSliceTotal()
{
    return this->sliceTotal;
}

quint32 MyMsg::getSliceCount()
{
    return this->sliceCount;
}

quint32 MyMsg::getSenderID()
{
    return this->senderID;
}

quint32 MyMsg::getReceiverID()
{
    return this->receiverID;
}

QTime MyMsg::getTime()
{
    return this->time;
}

QByteArray & MyMsg::getContent(){
    return content;
}
