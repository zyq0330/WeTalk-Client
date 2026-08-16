#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QTimer>
ChatWindow::ChatWindow(TcpClient *client,QWidget *parent)
    : QMainWindow(parent),tcpClient(client)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("张三");
    ui->listWidget->addItem("李四");
    ui->listWidget->addItem("王五");
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
    if(msg.isEmpty())  return;
    appendMessage("我:"+msg,Qt::AlignRight,Qt::blue);
    ui->textEdit_input->clear();
    QTimer::singleShot(1000,[=](){
        if(!currentFriend.isEmpty()){
            appendMessage(currentFriend+":自动回复",Qt::AlignLeft,Qt::gray);
        }
    });
}

