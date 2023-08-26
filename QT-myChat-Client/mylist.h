#ifndef MYLIST_H
#define MYLIST_H

#include <QWidget>

namespace Ui {
class mylist;
}

class mylist : public QWidget
{
    Q_OBJECT

public:
    explicit mylist(QWidget *parent = nullptr);
    ~mylist();

private:
    Ui::mylist *ui;
};

#endif // MYLIST_H
