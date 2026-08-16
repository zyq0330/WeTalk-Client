#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QMessageBox>
#include<QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient=new TcpClient(this);
    connect(tcpClient,&TcpClient::connected,this,[=](){
        QString username=ui->lineEdit_username->text().trimmed();
        QString password=ui->lineEdit_password->text().trimmed();
        QJsonObject obj;
        obj["username"]=username;
        obj["password"]=password;
        QByteArray body=QJsonDocument(obj).toJson();
        tcpClient->sendMessage(201,body);
    });
    connect(tcpClient,&TcpClient::messageReceived,this,[=](uint16_t cmd,const QByteArray& body){
        if(cmd==202){
            QJsonDocument doc=QJsonDocument::fromJson(body);
            if(!doc.isObject())  return;
            QJsonObject obj=doc.object();
            if(obj.value("result").toString()=="ok"){
                onLoginSuccess();
            }else{
                onLoginFailed("用户名或者密码错误");
            }
        }
    });
    connect(tcpClient,&TcpClient::errorOccurred,this,&MainWindow::onTcpError);
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
        tcpClient->connectToServer("127.0.0.1",8888);
    }
}
void MainWindow::on_btn_register_clicked()
{
    QMessageBox::information(this,"注册","注册功能即将开放!");
}
void MainWindow::onLoginSuccess(){
    chatWindow=new ChatWindow(tcpClient,this);
    chatWindow->show();
    this->hide();
}
void MainWindow::onLoginFailed(const QString& reason){
    QMessageBox::warning(this,"登录失败",reason);
}
void MainWindow::onTcpError(const QString& err){
    QMessageBox::critical(this,"网络错误",err);
}
