#include "tcpclient.h"
#include <QDataStream>
TcpClient::TcpClient(QObject* parent):QObject(parent){
    socket_=new QTcpSocket(this);
    connect(socket_,&QTcpSocket::connected,this,&TcpClient::onConnected);
    connect(socket_,&QTcpSocket::disconnected,this,&TcpClient::onDisconnected);
    connect(socket_,&QTcpSocket::readyRead,this,&TcpClient::onReadyRead);
    connect(socket_,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this,&TcpClient::onError);
    heartbeatTimer=new QTimer(this);
    heartbeatTimer->setInterval(15000);
    connect(heartbeatTimer,&QTimer::timeout,this,&TcpClient::sendHeartbeat);
    heartbeatMissCount_=0;
}
TcpClient::~TcpClient(){
    disconnect();
}
//连接到指定服务器，ip（服务器ip地址），（port)服务器端口
void TcpClient::connectToServer(const QString& ip,quint16 port){
    if(socket_->state()==QAbstractSocket::ConnectedState){
        emit errorOccurred("Already connected");
        return;
    }
    socket_->connectToHost(ip,port);
}
void TcpClient::disconnect(){
    if(socket_->state()!=QAbstractSocket::UnconnectedState){
        socket_->disconnectFromHost();
    }
}
bool TcpClient::isConnected() const{
    return socket_->state()==QAbstractSocket::ConnectedState;
}
//发送消息，cmd命令码，body消息包体，json格式
void TcpClient::sendMessage(uint16_t cmd,const QByteArray& body){
    if(!isConnected()){
        emit errorOccurred("Not connected");
        return;
    }
    QByteArray packet=packMessage(cmd,body);
    socket_->write(packet);
}
QByteArray TcpClient::packMessage(uint16_t cmd,const QByteArray& body){
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    uint32_t bodyLen=body.size();
    stream<<bodyLen;
    stream<<cmd;
    stream.writeRawData(body.data(),body.size());
    return data;
}
bool TcpClient::unpackMessage(const QByteArray& raw,uint16_t& cmd,QByteArray& body){
    if(raw.size()<6) return false;
    QDataStream stream(raw);
    stream.setByteOrder(QDataStream::BigEndian);
    uint32_t bodyLen;
    stream>>bodyLen;
    if(raw.size()!=4+2+bodyLen) return false;
    stream>>cmd;
    body=raw.mid(6,bodyLen);
    return true;
}
void TcpClient::onConnected(){
    heartbeatTimer->start();
    emit connected();
}
void TcpClient::onDisconnected(){
    heartbeatTimer->stop();
    emit disconnected();
}
void TcpClient::onError(QAbstractSocket::SocketError err){
    Q_UNUSED(err);
    emit errorOccurred(socket_->errorString());
}
void TcpClient::onReadyRead(){
    buffer_.append(socket_->readAll());
    while(true){
        uint16_t cmd;
        QByteArray body;
        bool ok=unpackMessage(buffer_,cmd,body);
        if(!ok){
            break;
        }
        if(cmd==402){
            heartbeatMissCount_=0;
        }else{
        emit messageReceived(cmd,body);
        }
        buffer_.remove(0,4+2+body.size());
    }
}
void TcpClient::sendHeartbeat(){
    if(!isConnected()){
        return;
    }
    sendMessage(401,QByteArray());
    heartbeatMissCount_++;
    if(heartbeatMissCount_>=3){
        emit errorOccurred("心跳超时，连接断开");
        disconnect();
    }
}



