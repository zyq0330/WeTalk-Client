#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT
signals:
    void doRegister(const QString& username,const QString& password,const QString& nickname);

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_btn_register_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
