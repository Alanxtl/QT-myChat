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
#include <QMessageBox>

chapage::chapage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chapage)
{
    ui->setupUi(this);
    resize(600, 800);
    ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Nickname" << "ID" << "IP");
        ui->tableWidget->setRowCount(5);

        QStringList nameList;
        nameList << "张三" << "李四" << "王五" << "赵六" << "孙七";
        QStringList sexList;
        sexList << "zhangsan123" << "lisi123" << "wangwu123" << "zhaoliu123" << "sunqi123";
        QStringList ageList;
        ageList << "22" << "30" << "12" << "55" << "90";
        for (int i=0;i<5;i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(nameList[i]));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(sexList[i]));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(ageList[i]));
        }
        QObject::connect(&Socket::getObj()->socket, &QTcpSocket::readyRead, [&](){    //设置接受信息
            QString time = QString::number(QDateTime::currentDateTime().toTime_t());
            dealMessageTime(time);
            QByteArray originMessage = Socket::getObj()->socket.readAll();
            MyMsg* msg = MyMsg::arrayToMsg(originMessage);
            quint32 id = msg->getSenderID();
//            QMessageBox::about(this, "消息", QString::fromUtf8(msg->getContent()));

            QListWidgetItem *iditem = new QListWidgetItem;
            iditem->setText(QString::number(id));
            iditem->setTextAlignment(Qt::AlignLeft);
            ui->listWidget->addItem(iditem);//显示ID

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, QString::fromUtf8(msg->getContent()), time, QNChatMessage::User_She);
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        });


}

chapage::~chapage()
{
    delete ui;
}


void chapage::on_sendbtn_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中

        MyMsg *msge = MyMsg::defaultMsg(100, 0, msg);
        qDebug() << msg;
        QByteArray data = msge->msgToArray();
        Socket::getObj()->socket.write(data);

    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            //显示群聊信息的用户名（右侧）
            QListWidgetItem *iditem = new QListWidgetItem;
            iditem->setText("YourID");
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
                iditem->setText("YourID");
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

            //显示群聊信息的用户名(左侧)
            QListWidgetItem *iditem = new QListWidgetItem;
            iditem->setText("OthersID");
            iditem->setTextAlignment(Qt::AlignRight);
            ui->listWidget->addItem(iditem);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
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
}
