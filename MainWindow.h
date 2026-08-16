#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "chatwindow.h"
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
private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
    ChatWindow *chatWindow;
};
#endif // MAINWINDOW_H
