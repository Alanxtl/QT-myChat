#include "chapage.h"
#include "ui_chapage.h"
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <Tools/mymsg.h>
#include <Tools/socket.h>
#include <QFileDialog>
#include <QFileInfo>
#include <Tools/handler.h>
#include <QMessageBox>
#include <QFile>
#include "Database/DBHelper.h"
#include "Database/UserInfo.h"
#include <login.h>

chapage::chapage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chapage)
{
    ui->setupUi(this);
    resize(600, 800);
    perDataSize = 64*1024 - 32;
    totalBytes = 0;
    bytestoWrite = 0;
    bytesWritten = 0;
    bytesReceived = 0;
    filenameSize = 0;
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Nickname" << "ID" << "IP");
    //ui->tableWidget->setRowCount(5);

//    QObject::connect(&Socket::getObj()->socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
//        QString time = QString::number(QDateTime::currentDateTime().toTime_t());
//        dealMessageTime(time);
//        QByteArray originMessage = Socket::getObj()->socket.readAll();
//        MyMsg* msg = MyMsg::arrayToMsg(originMessage);
//        quint32 id = msg->getSenderID();
////            QMessageBox::about(this, "消息", QString::fromUtf8(msg->getContent()));

//    });

//    connect(Socket::getFileObj(),SIGNAL(readyRead()),this,SLOT(receiveData()));
    connect(login::GetInstance(), &login::receiveTwo, this, &chapage::receiveTypeTwoMsg);

    //connect(Socket::getFileObj(),SIGNAL(readyRead()),this,SLOT(receiveData()));
}


chapage::~chapage()
{
    delete ui;
}


void chapage::receivedoubleid(QString myid,QString othersid){
     this->myid = myid;
     this->othersid = othersid;
     this->setWindowTitle(myid + "  " + othersid);
}

void chapage::on_sendbtn_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中

        MyMsg *msge = MyMsg::defaultMsg(Handler::getObj()->my.getID(), othersid.toUInt(), msg);
        qDebug() << msg;
        QByteArray data = msge->msgToArray();
        Socket::getObj()->socket.write(data);

    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            //显示群聊信息的用户名（右侧）
            QListWidgetItem *iditem = new QListWidgetItem;
            iditem->setText(this->myid);
            iditem->setTextAlignment(Qt::AlignRight);
            ui->listWidget->addItem(iditem);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);

            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                //显示群聊信息的用户名（右侧）
                QListWidgetItem *iditem = new QListWidgetItem;
                iditem->setText(this->myid);
                iditem->setTextAlignment(Qt::AlignRight);
                ui->listWidget->addItem(iditem);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            //显示群聊信息的用户名(右侧)
            QListWidgetItem *iditem = new QListWidgetItem;
            iditem->setText(this->myid);
            iditem->setTextAlignment(Qt::AlignRight);
            ui->listWidget->addItem(iditem);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void chapage::receiveTypeTwoMsg(MyMsg* msg)
{
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());
    dealMessageTime(time);


    QString str_sid = QString::number(msg->getSenderID());
    QString str_rid = QString::number(msg->getReceiverID());
    QString str_type = QString::number(msg->getType());
    QString str_slice = QString::number(msg->getSlice());
    QString content = QString::fromUtf8(msg->getContent());

    qDebug() << "2: " + str_sid + "向" + str_rid + "发送了type为" + str_type + "slice为" + str_slice + "内容为" + content;

    quint32 id = msg->getSenderID();
//            QMessageBox::about(this, "消息", QString::fromUtf8(msg->getContent()));

    QListWidgetItem *iditem = new QListWidgetItem;
    iditem->setText(QString::number(id));
    iditem->setTextAlignment(Qt::AlignLeft);
    ui->listWidget->addItem(iditem);//显示ID

    if(msg->type == 2) {
        if(this->othersid==NULL||this->othersid.toUInt()==id)
        {//接受消息隔离
            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, QString::fromUtf8(msg->getContent()), time, QNChatMessage::User_She);
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        }
    }
}

void chapage::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width()-200);
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void chapage::dealMessageTime(QString curMsgTime)//计算消息时间差决定是否出现新时间
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width()-200, 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void chapage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


    ui->textEdit->resize(this->width() - 220, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

//   ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
//                         ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}


void chapage::on_pushButton_5_clicked()
{
    static QString s_strPath;
//    static QString s_strPath = myapp::m_strAppPath;
    QString strFileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       s_strPath,
                                                       tr("文件(*)"));

    if (strFileName.isEmpty()) return;
    s_strPath = strFileName;
    sendFile(s_strPath);
}

void chapage::sendFile(QString filename)
{


    QStringList list = filename.split("/");

    localFile = new QFile(list[list.size() - 1]);

    if(!localFile->open(QFile::ReadOnly))
    {
        QMessageBox::about(this,"错误","文件打开错误");
        return;
    }
    ///获取文件大小
    totalBytes = localFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_5_9);
    QString currentFileName = filename.right(filename.size()-filename.lastIndexOf('/')-1);

    qDebug()<<sizeof(currentFileName);
    ////保留总代大小信息空间、文件名大小信息空间、文件名
    sendout<<qint64(0)<<qint64(0)<<currentFileName;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));

    MyMsg* msg = new MyMsg;
    msg->setMsg(4,0,0,0,Handler::getObj()->my.getID(),this->othersid.toUInt(),QTime::currentTime(),filename.toUtf8());

    bytestoWrite = totalBytes - Socket::getObj()->socket.write(msg->msgToArray());
    outBlock.resize(0);
}

void chapage::updateSendedFileProgress(qint64 numBytes)
{
    ////已经发送的数据大小
    bytesWritten += (int)numBytes;

    ////如果已经发送了数据
    if(bytestoWrite > 0)
    {
        outBlock = localFile->read(qMin(bytestoWrite,perDataSize));
        ///发送完一次数据后还剩余数据的大小
        bytestoWrite -= ((int)Socket::getFileObj()->write(outBlock));
        ///清空发送缓冲区
        outBlock.resize(0);
    }
    else
        localFile->close();

    ////更新进度条
    //this->ui.progressBar->setMaximum(totalBytes);
    //this->ui.progressBar->setValue(bytesWritten);

    ////如果发送完毕
    if(bytesWritten == totalBytes)
    {
        localFile->close();
        //fileSocket->close();
    }
}

void chapage::updateReceivedFileProgress()
{
    QDataStream inFile(&Socket::getObj()->socket);
    inFile.setVersion(QDataStream::Qt_4_8);

    ///如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((Socket::getFileObj()->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((Socket::getFileObj()->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            filename = "ServerData/"+filename;
            localFile = new QFile(filename);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug()<<"Server::open file error!";
                return;
            }
        }
        else
            return;
    }
    /////如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += Socket::getFileObj()->bytesAvailable();
        inBlock = Socket::getFileObj()->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ////数据接收完成时
    if(bytesReceived == totalBytes)
    {
        QMessageBox::about(this,"成功","文件接收成功");
        //this->ui.textEdit->append("Receive file successfully!");
        bytesReceived = 0;
        totalBytes = 0;
        filenameSize = 0;
        localFile->close();
        //fileSocket->close();
    }
}

void chapage::on_cancelbt_clicked()
{
    this->hide();
}

void chapage::showRightFriendInfo(){
    if(this->othersid == NULL){
        QList<QByteArray> list;
        list = DBHelper::GetInstance()->selectAllFriendsUserInfo();
        QStringList nameList;
        QStringList idList;
        QStringList ipList;
        ui->tableWidget->setRowCount(list.size());
        for(int i = 0; i < list.size(); i++){
            nameList.append(UserInfo::fromQByteArray(list[i]).getName());
            idList.append(QString::number(UserInfo::fromQByteArray(list[i]).getID()));
        }
        ipList << "1" << "2" << "3" << "4" << "5";
        for (int i = 0; i < list.size(); i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(nameList[i]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(idList[i]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(ipList[i]));
        }
    }else{
        QStringList nameList;
        QStringList idList;
        QStringList ipList;
        ui->tableWidget->setRowCount(2);
        idList << this->myid << this->othersid;
        nameList.append(Handler::getObj()->my.getName());
        nameList.append(DBHelper::GetInstance()->selectUserInfoById(this->othersid.toUInt()).getName());
        ipList << "1" << "2";
        for(int i = 0; i < 2; i++){
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(nameList[i]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(idList[i]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(ipList[i]));
        }
    }
}
