#include "tcpclient.h"
#include <QDataStream>
TcpClient::TcpClient(QObject* parent):QObject(parent){
    socket=new QTcpSocket(this);
    connect(socket,&QTcpSocket::connected,this,&TcpClient::onConnected);
    connect(socket,&QTcpSocket::disconnected,this,&TcpClient::onDisconnected);
    connect(socket,&QTcpSocket::readyRead,this,&TcpClient::onReadyRead);
    connect(socket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this,&TcpClient::onError);
}
TcpClient::~TcpClient(){
    disconnect();
}
void TcpClient::connectToServer(const QString& ip,quint16 port){
    if(socket->state()==QAbstractSocket::ConnectedState){
        emit errorOccurred("Already connected");
        return;
    }
    socket->connectToHost(ip,port);
}
void TcpClient::disconnect(){
    if(socket->state()!=QAbstractSocket::UnconnectedState){
        socket->disconnectFromHost();
    }
}
bool TcpClient::isConnected() const{
    return socket->state()==QAbstractSocket::ConnectedState;
}
void TcpClient::sendMessage(uint16_t cmd,const QByteArray& body){
    if(!isConnected()){
        emit errorOccurred("Not connected");
        return;
    }
    QByteArray packet=packMessage(cmd,body);
    socket->write(packet);
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
    emit connected();
}
void TcpClient::onDisconnected(){
    emit disconnected();
}
void TcpClient::onError(QAbstractSocket::SocketError err){
    Q_UNUSED(err);
    emit errorOccurred(socket->errorString());
}
void TcpClient::onReadyRead(){
    buffer.append(socket->readAll());
    while(true){
        uint16_t cmd;
        QByteArray body;
        bool ok=unpackMessage(buffer,cmd,body);
        if(!ok){
            break;
        }
        emit messageReceived(cmd,body);
        buffer.remove(0,4+2+body.size());
    }
}



