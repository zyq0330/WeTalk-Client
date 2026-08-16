#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
class TcpClient : public QObject
{
        Q_OBJECT
public:
    explicit TcpClient(QObject *parent=nullptr);
    ~TcpClient();
    void connectToServer(const QString &ip,quint16 port);
    void disconnect();
    bool isConnected() const;
    void sendMessage(uint16_t cmd,const QString &body);
    void sendMessage(uint16_t cmd,const QByteArray& body);
signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& err);
    void messageReceived(uint16_t cmd,const QByteArray& body);
private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError err);
private:
    QTcpSocket *socket;
    QByteArray buffer;
    QByteArray packMessage(uint16_t cmd,const QByteArray& body);
    bool unpackMessage(const QByteArray& raw,uint16_t& cmd,QByteArray& body);
};

#endif // TCPCLIENT_H
