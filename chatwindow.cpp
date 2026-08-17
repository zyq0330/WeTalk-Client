#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "tcpclient.h"
#include <QTimer>
#include <QMessageBox>
#include <QJsonObject>
ChatWindow::ChatWindow(TcpClient *client,QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ChatWindow),tcpClient(client)
{
    ui->setupUi(this);
    ui->listWidget->addItem("alice");
    ui->listWidget->addItem("bob");
    //ui->listWidget->addItem("王五");
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
            }
        }
    });
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->stackedWidget->setCurrentIndex(1);
    currentFriend=item->text();
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
    ui->textEdit_input->clear();
}

