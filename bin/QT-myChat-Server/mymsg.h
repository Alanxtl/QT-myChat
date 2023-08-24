#ifndef MYMSG_H
#define MYMSG_H

#include <QObject>
#define identify 0xAA112233

/*
 * 标准QByteArray信息格式|header|body|
 *
 * header总共32字节包括以下内容:
 *     dataSize    : 占 4 个字节, quint32, 用于验证是否完整接收到了数据包
 *     identify    : 占 4 个字节, quint32, 用于验证是不是该程序的数据包，是一个默认的常量
 *     type        : 占 1 个字节, quint8, 用于标识数据包类型
 *          数据包类型及代码如下：0-注册信息 1-登录信息 2-普通信息 3-图片信息 4-文件信息
 *     slice       : 占 1 个字节，quint8，用以指示该信息是否为切片信息，若非切片信息以下两条数据应为0
 *     sliceTotal  : 占 4 个字节, quint32, 用以指示切片信息切片总数
 *     sliceCount  : 占 4 个字节, quint32, 用以指示该切片信息是第几个切片
 *     senderID    : 占 4 个字节, quint32, 用于表示发送者的id
 *     receiverID  : 占 4 个字节, quint32, 用于表示接收者的id
 *     time        : 占 4 个字节, quint32, 用于表示发送的时间
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

class myMsg : public QObject
{
    Q_OBJECT
public:
    explicit myMsg(QObject *parent = nullptr);

signals:

};

#endif // MYMSG_H
