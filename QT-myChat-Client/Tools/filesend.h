#ifndef FILESEND_H
#define FILESEND_H

#include <QWidget>

namespace Ui {
class FileSend;
}

class FileSend : public QWidget
{
    Q_OBJECT

public:
    explicit FileSend(QWidget *parent = nullptr);
    ~FileSend();

private:
    Ui::FileSend *ui;
};

#endif // FILESEND_H
