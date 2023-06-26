#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

public slots:
    void handleReadFromServer(const QString& str);

private slots:

    void on_pushButton_auth_clicked();

    void on_pushButton_2_reg_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::AuthForm *ui;
    AuthForm *ui_auth;
    MainWindow *slot_window;
    Statistic *slot_stat;
    task *slot_task;



    void change_mod(bool); //mode -> true for auth

signals:
    void auth_ok(QString, QString);
    void stat_signal(QString);
    void task_signal(QString);

};

#endif // AUTHFORM_H
