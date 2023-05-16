#include "authform.h"
#include "ui_authform.h"
#include "SingletonClient.h"

AuthForm::AuthForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    slot_window = new MainWindow;
    this -> show();
    ui -> label_name-> setVisible(false);
    ui -> lineEdit_name -> setVisible(false);
    ui -> label_surname -> setVisible(false);
    ui -> lineEdit_surname -> setVisible(false);
    ui -> label_patronymic -> setVisible(false);
    ui -> lineEdit_patronymic -> setVisible(false);


    connect(this, &AuthForm::auth_ok, slot_window, &MainWindow::slot_on_auth_ok);
    connect(SingletonClient::getInstance(), &SingletonClient::readFromServer,
            this, &AuthForm::handleReadFromServer);

}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::change_mod(bool mode)
{
    QString Login, Name, Surname, Patronymic, Password;
    ui -> pushButton_auth -> setVisible(!mode);
    ui -> label_name-> setVisible(mode);
    ui -> lineEdit_name -> setVisible(mode);
    ui -> label_surname -> setVisible(mode);
    ui -> lineEdit_surname -> setVisible(mode);
    ui -> label_patronymic -> setVisible(mode);
    ui -> lineEdit_patronymic -> setVisible(mode);

    if(!mode)
    {
        Login = ui -> lineEdit_login->text();
        Name = ui -> lineEdit_name->text();
        Surname = ui -> lineEdit_surname->text();
        Patronymic = ui -> lineEdit_patronymic->text();
        Password = ui -> lineEdit_password ->text();
        SingletonClient::getInstance()->send_msg_to_server("register&" + Login + "&" + Name + "&" + Surname + "&" + Patronymic + "&" + Password + "&stud");
        ui -> pushButton_2_reg -> setText("to reg");
    }

}

void AuthForm::on_pushButton_2_reg_clicked()
{
    this -> change_mod(ui -> pushButton_auth -> isVisible());
}


void AuthForm::on_pushButton_auth_clicked()
{
    QString Login, Password;
    qDebug() << "auth " + ui -> lineEdit_login -> text() +
              " " + ui->lineEdit_password->text();
    Login = ui -> lineEdit_login->text();
    Password = ui -> lineEdit_password ->text();
    SingletonClient::getInstance()->send_msg_to_server("auth&" + Login + "&" + Password);
}


void AuthForm::handleReadFromServer(const QString& str) {
    if (str == '1') {
        qDebug() << "Success";
        emit auth_ok(ui -> lineEdit_login->text());
        slot_window->show();
        this -> close();
    } else if (str == '0') {
        qDebug() << "Error";
    }
}

void AuthForm::on_pushButton_exit_clicked()
{
    exit(0);
}

