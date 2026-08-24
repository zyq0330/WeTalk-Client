/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_nickname;
    QPushButton *btn_register;
    QPushButton *btn_cancel;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(899, 605);
        widget = new QWidget(RegisterDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(160, 70, 391, 401));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_username = new QLineEdit(widget);
        lineEdit_username->setObjectName("lineEdit_username");

        verticalLayout->addWidget(lineEdit_username);

        lineEdit_password = new QLineEdit(widget);
        lineEdit_password->setObjectName("lineEdit_password");

        verticalLayout->addWidget(lineEdit_password);

        lineEdit_nickname = new QLineEdit(widget);
        lineEdit_nickname->setObjectName("lineEdit_nickname");

        verticalLayout->addWidget(lineEdit_nickname);

        btn_register = new QPushButton(widget);
        btn_register->setObjectName("btn_register");

        verticalLayout->addWidget(btn_register);

        btn_cancel = new QPushButton(widget);
        btn_cancel->setObjectName("btn_cancel");

        verticalLayout->addWidget(btn_cancel);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        btn_register->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214", nullptr));
        btn_cancel->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
