#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "chatwindow.h"
#include "registerdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btn_login_clicked();
    void on_btn_register_clicked();
    void onLoginSuccess();
    void onLoginFailed(const QString& reason);
    void onTcpError(const QString& err);
    void onRegisterRequest(const QString& username,const QString& password,const QString& nickname);
    void sendRegisterPacket(const QString& username,const QString& password,const QString& nickname);
    void onTcpConnected();
private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
    ChatWindow *chatWindow;
    bool isRegisterPending=false;
    QString pendingUsername;
    QString pendingPassword;
    QString pendingNickname;
    QString currentUsername;
    QString currentPassword;
};
#endif // MAINWINDOW_H
