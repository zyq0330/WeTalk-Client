#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "tcpclient.h"
#include <QTimer>
#include <QMessageBox>
#include <QJsonObject>
ChatWindow::ChatWindow(QWidget *parent,TcpClient *client):QMainWindow(parent),tcpClient(client)
{   ui=new Ui::ChatWindow;
    ui->setupUi(this);
    this->setStyleSheet(
        "QWidget { background-color: #f5f5f5; font-family: 'Microsoft YaHei'; font-size: 12pt; }"
        "QListWidget { background: white; border: 1px solid #ddd; border-radius: 4px; }"
        "QListWidget::item { padding: 8px; }"
        "QListWidget::item:selected { background: #cce5ff; }"
        "QTextBrowser { background: white; border: 1px solid #ddd; border-radius: 4px; }"
        "QTextEdit { background: white; border: 1px solid #ddd; border-radius: 4px; }"
        "QPushButton { background: #4CAF50; color: white; border: none; padding: 8px 16px; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background: #45a049; }"
        );
    ui->listWidget->addItem("alice");
    ui->listWidget->addItem("bob");
    connect(tcpClient,&TcpClient::messageReceived,this,[=](uint16_t cmd,const QByteArray& body){
        if(cmd==302){
            QJsonDocument doc=QJsonDocument::fromJson(body);
            if(!doc.isObject())
                return;
            QJsonObject obj=doc.object();
            QString from=obj.value("from").toString();
            QString content=obj.value("content").toString();
            appendMessage(from+":"+content,Qt::AlignLeft,Qt::gray);
            if(from!=currentFriend){
                qDebug()<<"收到来自"<<from<<"的消息，但当前聊天对象是"<<currentFriend;
                unreadMap[from]=true;
                updateFriendList();
            }
        }
    });
    loadFriendList();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString name=item->data(Qt::UserRole).toString();
    if(name.isEmpty()) return;
    currentFriend=name;
    ui->stackedWidget->setCurrentIndex(1);
    if(unreadMap.contains(name)&&unreadMap[name]){
        unreadMap[name]=false;
        updateFriendList();
    }else{
        updateFriendList();
    }
}
void ChatWindow::appendMessage(const QString& text,Qt::Alignment alignment,const QColor& color){
    QTextCursor cursor(ui->textBrowser_chat->document());
    cursor.movePosition(QTextCursor::End);
    QTextBlockFormat blockFmt;
    blockFmt.setAlignment(alignment);
    QTextCharFormat chatFmt;
    chatFmt.setForeground(color);
    cursor.insertBlock(blockFmt);
    cursor.insertText(text,chatFmt);
}

void ChatWindow::on_btn_send_clicked()
{
    QString msg=ui->textEdit_input->toPlainText().trimmed();
    if(msg.isEmpty()){
        return;
    }
    if(currentFriend.isEmpty()){
        QMessageBox::warning(this,"提示","请先选择好友");
        return;
    }
    QJsonObject obj;
    obj["target"]=currentFriend;
    obj["content"]=msg;
    QByteArray body=QJsonDocument(obj).toJson();
    tcpClient->sendMessage(301,body);
    appendMessage("我："+msg,Qt::AlignRight,Qt::blue);
    ui->textBrowser_chat->moveCursor(QTextCursor::End);
    ui->textEdit_input->clear();
}
void ChatWindow::loadFriendList(){
    ui->listWidget->clear();
    TODO:
    QStringList friends;
        friends<<"alice"<<"bob";
    for(const QString &name:friends){
            //if(name==myUsername) continue;
            QListWidgetItem *item=new QListWidgetItem(name);
        item->setData(Qt::UserRole,name);
            ui->listWidget->addItem(item);
    }
}
void ChatWindow::updateFriendList(){
        for(int i=0;i<ui->listWidget->count();i++){
        QListWidgetItem *item=ui->listWidget->item(i);
            QString name=item->data(Qt::UserRole).toString();
        if(unreadMap.value(name,false)){
                item->setText(name+":未读");
            item->setForeground((Qt::red));
        }else{
            item->setText(name);
            item->setForeground(Qt::black);
        }
    }
}
