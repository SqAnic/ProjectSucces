#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SingletonClient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TaskWindow = new task;
    //StatisticWindow = new Statistic;

    connect(this, &MainWindow::signal_task, TaskWindow, &task::slot_task_generator);
    //connect(TaskWindow, &task::signal_mainwindow, this, &MainWindow::slot_task);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_exit_clicked()
{
    qDebug() << "exit";
    exit(0);
}


void MainWindow::on_pushButton_task1_clicked()
{
    qDebug() << "task1";
    //QString taskNumber = ui -> pushButton_task1 ->text();
    SingletonClient::getInstance()->send_msg_to_server("generator&1");
}

void MainWindow::on_pushButton_task2_clicked()
{
    qDebug() << "task2";
    //QString taskNumber = ui -> pushButton_task2 ->text();
    SingletonClient::getInstance()->send_msg_to_server("generator&2");
}


void MainWindow::on_pushButton_task3_clicked()
{
    qDebug() << "task3";
    //QString taskNumber = ui -> pushButton_task3 ->text();
    SingletonClient::getInstance()->send_msg_to_server("generator&3");
}


void MainWindow::on_pushButton_task4_clicked()
{
    qDebug() << "task4";
    //QString taskNumber = ui -> pushButton_task4 ->text();
    SingletonClient::getInstance()->send_msg_to_server("generator&4");
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

void MainWindow::slot_on_auth_ok(QString login, QString str)
{
    if (str == "2")
    {
        ui ->pushButton_task1 ->setVisible(false);
        ui ->pushButton_task2 ->setVisible(false);
        ui ->pushButton_task3 ->setVisible(false);
        ui ->pushButton_task4 ->setVisible(false);
        ui ->pushButton_mystat ->setVisible(false);
    }
    if (str == "1")
    {
    ui -> label_log -> setText(login);
    ui ->pushButton_stat ->setVisible(false);
    }
}

//void MainWindow::slot_task()
//{
//    qDebug() << "back сработал";
//    this -> show();
//    TaskWindow -> close();
//}

void MainWindow::on_pushButton_stat_clicked()
{
    SingletonClient::getInstance()->send_msg_to_server("stat");
    qDebug() << "Statistic";
}


void MainWindow::on_pushButton_mystat_clicked()
{
    SingletonClient::getInstance()->send_msg_to_server("mystat");
    qDebug() << "My Statistic";
}

