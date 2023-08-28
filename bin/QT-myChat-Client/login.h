#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_loginbth_clicked();
    void login_success();

    void on_regbtn_clicked();

    void on_exitbtn_clicked();

    //void on_checkBox_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::login *ui;
};

#endif // LOGIN_H
