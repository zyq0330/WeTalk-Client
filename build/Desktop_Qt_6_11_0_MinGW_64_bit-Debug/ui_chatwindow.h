/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *page_2;
    QTextBrowser *textBrowser_chat;
    QTextEdit *textEdit_input;
    QPushButton *btn_send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(1187, 714);
        centralwidget = new QWidget(ChatWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 641, 641));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(layoutWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(200, 0));
        listWidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(listWidget);

        stackedWidget = new QStackedWidget(layoutWidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 270, 181, 51));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        textBrowser_chat = new QTextBrowser(page_2);
        textBrowser_chat->setObjectName("textBrowser_chat");
        textBrowser_chat->setGeometry(QRect(0, 0, 411, 461));
        textEdit_input = new QTextEdit(page_2);
        textEdit_input->setObjectName("textEdit_input");
        textEdit_input->setGeometry(QRect(0, 484, 411, 91));
        btn_send = new QPushButton(page_2);
        btn_send->setObjectName("btn_send");
        btn_send->setGeometry(QRect(310, 610, 93, 28));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        ChatWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChatWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1187, 25));
        ChatWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChatWindow);
        statusbar->setObjectName("statusbar");
        ChatWindow->setStatusBar(statusbar);

        retranslateUi(ChatWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ChatWindow", "\346\254\242\350\277\216\344\275\277\347\224\250WeTalk-Client", nullptr));
        btn_send->setText(QCoreApplication::translate("ChatWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
