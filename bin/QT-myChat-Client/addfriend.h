#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

namespace Ui {
class addFriend;
}

class addFriend : public QWidget
{
    Q_OBJECT

public:
    explicit addFriend(QWidget *parent = nullptr);
    ~addFriend();
    void on_add_clicked();

private:
    Ui::addFriend *ui;
};

#endif // ADDFRIEND_H
