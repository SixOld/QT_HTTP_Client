/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTextBrowser *textBrowser_receive;
    QTextEdit *textEdit_send;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_set;
    QLabel *label;
    QLineEdit *lineEdit_ip;
    QLabel *label_5;
    QLineEdit *lineEdit_router;
    QLabel *label_4;
    QLineEdit *lineEdit_port;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_user;
    QLabel *label_2;
    QLineEdit *lineEdit_userName;
    QLabel *label_3;
    QLineEdit *lineEdit_passwd;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_radio;
    QRadioButton *radioButton_post;
    QRadioButton *radioButton_get;
    QRadioButton *radioButton_put;
    QRadioButton *radioButton_delete;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_basic;
    QRadioButton *radioButton_digest;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(721, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 50, 131, 23));
        textBrowser_receive = new QTextBrowser(centralwidget);
        textBrowser_receive->setObjectName(QString::fromUtf8("textBrowser_receive"));
        textBrowser_receive->setGeometry(QRect(50, 251, 631, 311));
        textEdit_send = new QTextEdit(centralwidget);
        textEdit_send->setObjectName(QString::fromUtf8("textEdit_send"));
        textEdit_send->setGeometry(QRect(50, 110, 471, 101));
        textEdit_send->setReadOnly(false);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 90, 54, 12));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 230, 54, 12));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 491, 22));
        horizontalLayout_set = new QHBoxLayout(layoutWidget);
        horizontalLayout_set->setObjectName(QString::fromUtf8("horizontalLayout_set"));
        horizontalLayout_set->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(false);
        label->setWordWrap(false);
        label->setOpenExternalLinks(false);

        horizontalLayout_set->addWidget(label);

        lineEdit_ip = new QLineEdit(layoutWidget);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));

        horizontalLayout_set->addWidget(lineEdit_ip);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setScaledContents(false);
        label_5->setWordWrap(false);
        label_5->setOpenExternalLinks(false);

        horizontalLayout_set->addWidget(label_5);

        lineEdit_router = new QLineEdit(layoutWidget);
        lineEdit_router->setObjectName(QString::fromUtf8("lineEdit_router"));

        horizontalLayout_set->addWidget(lineEdit_router);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_set->addWidget(label_4);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));

        horizontalLayout_set->addWidget(lineEdit_port);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(18, 50, 334, 22));
        horizontalLayout_user = new QHBoxLayout(layoutWidget1);
        horizontalLayout_user->setObjectName(QString::fromUtf8("horizontalLayout_user"));
        horizontalLayout_user->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_user->addWidget(label_2);

        lineEdit_userName = new QLineEdit(layoutWidget1);
        lineEdit_userName->setObjectName(QString::fromUtf8("lineEdit_userName"));

        horizontalLayout_user->addWidget(lineEdit_userName);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_user->addWidget(label_3);

        lineEdit_passwd = new QLineEdit(layoutWidget1);
        lineEdit_passwd->setObjectName(QString::fromUtf8("lineEdit_passwd"));

        horizontalLayout_user->addWidget(lineEdit_passwd);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(590, 20, 91, 111));
        verticalLayout_radio = new QVBoxLayout(layoutWidget2);
        verticalLayout_radio->setObjectName(QString::fromUtf8("verticalLayout_radio"));
        verticalLayout_radio->setContentsMargins(0, 0, 0, 0);
        radioButton_post = new QRadioButton(layoutWidget2);
        radioButton_post->setObjectName(QString::fromUtf8("radioButton_post"));

        verticalLayout_radio->addWidget(radioButton_post);

        radioButton_get = new QRadioButton(layoutWidget2);
        radioButton_get->setObjectName(QString::fromUtf8("radioButton_get"));

        verticalLayout_radio->addWidget(radioButton_get);

        radioButton_put = new QRadioButton(layoutWidget2);
        radioButton_put->setObjectName(QString::fromUtf8("radioButton_put"));

        verticalLayout_radio->addWidget(radioButton_put);

        radioButton_delete = new QRadioButton(layoutWidget2);
        radioButton_delete->setObjectName(QString::fromUtf8("radioButton_delete"));

        verticalLayout_radio->addWidget(radioButton_delete);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(590, 150, 91, 40));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_basic = new QRadioButton(layoutWidget3);
        radioButton_basic->setObjectName(QString::fromUtf8("radioButton_basic"));

        verticalLayout->addWidget(radioButton_basic);

        radioButton_digest = new QRadioButton(layoutWidget3);
        radioButton_digest->setObjectName(QString::fromUtf8("radioButton_digest"));

        verticalLayout->addWidget(radioButton_digest);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 721, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(lineEdit_ip, lineEdit_router);
        QWidget::setTabOrder(lineEdit_router, lineEdit_port);
        QWidget::setTabOrder(lineEdit_port, lineEdit_userName);
        QWidget::setTabOrder(lineEdit_userName, lineEdit_passwd);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        label->setText(QApplication::translate("MainWindow", "IP", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\350\267\257\347\224\261", nullptr));
        lineEdit_router->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\350\264\246\345\217\267", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        radioButton_post->setText(QApplication::translate("MainWindow", "POST", nullptr));
        radioButton_get->setText(QApplication::translate("MainWindow", "GET", nullptr));
        radioButton_put->setText(QApplication::translate("MainWindow", "PUT", nullptr));
        radioButton_delete->setText(QApplication::translate("MainWindow", "DELETE", nullptr));
        radioButton_basic->setText(QApplication::translate("MainWindow", "Basic", nullptr));
        radioButton_digest->setText(QApplication::translate("MainWindow", "Digest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
