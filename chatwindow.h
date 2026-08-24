#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include "tcpclient.h"
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr,TcpClient *client=nullptr);
    ~ChatWindow();
    void loadFriendList();
    void appendMessage(const QString &text, Qt::Alignment alignment, const QColor &color);
    void updateFriendList();
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_btn_send_clicked();

private:
    Ui::ChatWindow *ui;
    QString currentFriend_;
    TcpClient *tcpClient;
    QMap<QString,bool> unreadMap_;
};

#endif // CHATWINDOW_H
