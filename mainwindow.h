#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qdebug>
#include "task.h"
#include "statistic.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void on_pushButton_exit_clicked();

    void on_pushButton_task1_clicked();

    void on_pushButton_task2_clicked();

    void on_pushButton_task3_clicked();

    void on_pushButton_task4_clicked();

    void on_actiontask1_triggered();

    void on_actiontask2_triggered();

    void on_actiontask3_triggered();

    void on_actionexit_triggered();

    void slot_on_auth_ok(QString login, QString str);

    //void slot_task();

private:
    Ui::MainWindow *ui;
    task *TaskWindow;
    //Statistic *StatisticWindow;

signals:
    void signal_task(QString, QString);

private slots:
    void on_pushButton_stat_clicked();
    void on_pushButton_mystat_clicked();
};
#endif // MAINWINDOW_H
