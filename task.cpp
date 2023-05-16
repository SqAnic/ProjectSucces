#include "task.h"
#include "ui_task.h"

task::task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task)
{
    ui->setupUi(this);


}

task::~task()
{
    delete ui;
}

void task::slot_task(QString task_number)
{
    ui -> label_task -> setText(task_number);
}

void task::on_pushButton_send_clicked()
{
    QString Answer = ui ->  lineEdit_answer -> text();
    QString Task = ui -> label_task -> text();
    qDebug() << "check_answer&" + Task + "&" + Answer;
}


void task::on_pushButton_exit_clicked()
{
    this -> close();
}

