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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <chatwindow.h>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
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

    void setupUi(ChatWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(976, 604);
        layoutWidget = new QWidget(ChatWindow);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(50, 40, 591, 521));
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
        label->setGeometry(QRect(120, 190, 151, 20));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        textBrowser_chat = new QTextBrowser(page_2);
        textBrowser_chat->setObjectName("textBrowser_chat");
        textBrowser_chat->setGeometry(QRect(0, 0, 381, 301));
        textEdit_input = new QTextEdit(page_2);
        textEdit_input->setObjectName("textEdit_input");
        textEdit_input->setGeometry(QRect(0, 320, 381, 121));
        btn_send = new QPushButton(page_2);
        btn_send->setObjectName("btn_send");
        btn_send->setGeometry(QRect(280, 470, 93, 28));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ChatWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(ChatWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ChatWindow", "\346\254\242\350\277\216\344\275\277\347\224\250WeTalk", nullptr));
        btn_send->setText(QCoreApplication::translate("ChatWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
