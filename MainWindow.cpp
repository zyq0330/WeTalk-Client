#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<QMessageBox>
#include<QJsonObject>
#include<QTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient=new TcpClient(this);
    connect(tcpClient,&TcpClient::connected,this,&MainWindow::onTcpConnected);
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
        }else if(cmd==102){
            QJsonDocument doc=QJsonDocument::fromJson(body);
            if(!doc.isObject()){
                return;
            }
            QJsonObject obj=doc.object();
            QString result=obj.value("result").toString();
            if(result=="ok"){
                QMessageBox::information(this,"注册成功","账号已创建，请登录");
            }else{
                QMessageBox::warning(this,"注册失败","用户名可能已经被占用");
            }
        }
    });
    connect(tcpClient,&TcpClient::errorOccurred,this,[=](const QString& err){
        if(err.contains("remote host closed")||err.contains("连接被远程主机关闭")){
            return;
        }
            QMessageBox::critical(this,"网络错误",err);
    });
    connect(tcpClient,&TcpClient::disconnected,this,[=](){
        QMessageBox::warning(this,"提示","与服务器断开连接，请重新登录!");
        if(chatWindow){
            chatWindow->close();
            chatWindow=nullptr;
        }
        this->show();
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btn_login_clicked()
{
     currentUsername=ui->lineEdit_username->text();
     currentPassword=ui->lineEdit_password->text();
    if(currentUsername.isEmpty()||currentPassword.isEmpty()){
        QMessageBox::warning(this,"提示","用户名或密码不能为空!");
        return;
    }
    if(tcpClient->isConnected()){
        tcpClient->disconnect();
    }
    tcpClient->connectToServer("127.0.0.1",8888);
}
void MainWindow::on_btn_register_clicked()
{
    RegisterDialog *regDlg=new RegisterDialog(this);
    connect(regDlg,&RegisterDialog::doRegister,this,&MainWindow::onRegisterRequest);
    regDlg->exec();
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
void MainWindow::onRegisterRequest(const QString& username,const QString& password,const QString& nickname){
    if(!tcpClient->isConnected()){
        /*QEventLoop loop;
        QTimer::singleShot(500,&loop,&QEventLoop::quit);
        loop.exec();*/
        pendingUsername=username;
        pendingPassword=password;
        pendingNickname=nickname;
        isRegisterPending=true;
        tcpClient->connectToServer("127.0.0.1",8888);
    }else{
        sendRegisterPacket(username,password,nickname);
    }
}
void MainWindow::sendRegisterPacket(const QString& username,const QString& password,const QString& nickname){
    QJsonObject obj;
    obj["username"]=username;
    obj["password"]=password;
    obj["nickname"]=nickname;
    QByteArray body=QJsonDocument(obj).toJson();
    tcpClient->sendMessage(101,body);
}
void MainWindow::onTcpConnected(){
    if(isRegisterPending){
        sendRegisterPacket(pendingUsername,pendingPassword,pendingNickname);
        isRegisterPending=false;
    }else{
        QJsonObject obj;
        obj["username"]=currentUsername;
        obj["password"]=currentPassword;
        QByteArray body=QJsonDocument(obj).toJson();
        tcpClient->sendMessage(201,body);
    }
}