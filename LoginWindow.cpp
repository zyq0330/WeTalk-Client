#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btn_login_clicked()
{
    QString username=ui->lineEdit_username->text();
    QString password=ui->lineEdit_password->text();
    if(username.isEmpty()||password.isEmpty()){
        QMessageBox::warning(this,"提示","用户名或密码不能为空!");
    }else{
        QMessageBox::information(this,"登录","登录成功!");
    }
}
void MainWindow::on_btn_register_clicked()
{
    QMessageBox::information(this,"注册","注册功能即将开放!");
}
