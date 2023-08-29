#include "addfriend.h"
#include "ui_addfriend.h"

addFriend::addFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addFriend)
{
    ui->setupUi(this);
}

addFriend::~addFriend()
{
    delete ui;
}
