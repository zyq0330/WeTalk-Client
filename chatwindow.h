#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    void appendMessage(const QString &text, Qt::Alignment alignment, const QColor &color);
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_btn_send_clicked();

private:
    Ui::ChatWindow *ui;
    QString currentFriend;
};

#endif // CHATWINDOW_H
