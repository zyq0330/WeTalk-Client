#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_btn_register_clicked()
{
    QString username=ui->lineEdit_username->text().trimmed();
    QString password=ui->lineEdit_password->text().trimmed();
    QString nickname=ui->lineEdit_nickname->text().trimmed();
    if(username.isEmpty()||password.isEmpty()||nickname.isEmpty()){
        QMessageBox::warning(this,"提示","所有字段都不能为空！");
        return;
    }
    emit doRegister(username,password,nickname);
}


void RegisterDialog::on_btn_cancel_clicked()
{
    reject();
}

