#ifndef REGIS_H
#define REGIS_H

#include <QMainWindow>

namespace Ui {
class regis;
}

class regis : public QMainWindow
{
    Q_OBJECT

public:
    explicit regis(QWidget *parent = nullptr);
    ~regis();

private slots:
    void on_regbtn_clicked();

    void on_exitbtn_clicked();

    void on_checkBox_clicked();

private:
    Ui::regis *ui;
};

#endif // REGIS_H
