#include "filesend.h"
#include "ui_filesend.h"

FileSend::FileSend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSend)
{
    ui->setupUi(this);
}

FileSend::~FileSend()
{
    delete ui;
}
