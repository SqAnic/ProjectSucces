#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TaskWindow = new task;

    connect(this,&MainWindow::signal_task, TaskWindow, &task::slot_task);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_exit_clicked()
{
    qDebug() << "exit";
}


void MainWindow::on_pushButton_task1_clicked()
{
    qDebug() << "task1";
    emit signal_task(ui -> pushButton_task1 ->text());
    TaskWindow -> show();
    this -> close();
}


void MainWindow::on_pushButton_task2_clicked()
{
    qDebug() << "task2";
    emit signal_task(ui -> pushButton_task2 ->text());
    TaskWindow -> show();
    this -> close();
}


void MainWindow::on_pushButton_task3_clicked()
{
    qDebug() << "task3";
    emit signal_task(ui -> pushButton_task3 ->text());
    TaskWindow -> show();
    this -> close();
}


void MainWindow::on_actiontask1_triggered()
{
    this -> on_pushButton_task1_clicked();
}


void MainWindow::on_actiontask2_triggered()
{
    this -> on_pushButton_task2_clicked();
}


void MainWindow::on_actiontask3_triggered()
{
    this -> on_pushButton_task3_clicked();
}


void MainWindow::on_actionexit_triggered()
{
    this -> on_pushButton_exit_clicked();
}

void MainWindow::slot_on_auth_ok(QString login)
{
    ui -> label_log -> setText(login);
}


