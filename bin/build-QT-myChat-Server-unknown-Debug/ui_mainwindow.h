/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *logLabel;
    QTextBrowser *logBrowser;
    QLabel *clientLabel;
    QTextBrowser *clientBrowser;
    QLabel *clientCountLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        logLabel = new QLabel(centralwidget);
        logLabel->setObjectName(QStringLiteral("logLabel"));
        logLabel->setGeometry(QRect(530, 20, 131, 17));
        logBrowser = new QTextBrowser(centralwidget);
        logBrowser->setObjectName(QStringLiteral("logBrowser"));
        logBrowser->setGeometry(QRect(530, 50, 256, 192));
        clientLabel = new QLabel(centralwidget);
        clientLabel->setObjectName(QStringLiteral("clientLabel"));
        clientLabel->setGeometry(QRect(20, 20, 101, 17));
        clientBrowser = new QTextBrowser(centralwidget);
        clientBrowser->setObjectName(QStringLiteral("clientBrowser"));
        clientBrowser->setGeometry(QRect(20, 50, 411, 192));
        clientCountLabel = new QLabel(centralwidget);
        clientCountLabel->setObjectName(QStringLiteral("clientCountLabel"));
        clientCountLabel->setGeometry(QRect(120, 20, 67, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        logLabel->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\227\245\345\277\227", Q_NULLPTR));
        clientLabel->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\345\234\250\347\272\277\347\224\250\346\210\267", Q_NULLPTR));
        clientCountLabel->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
