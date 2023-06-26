#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class task;
}

class task : public QWidget
{
    Q_OBJECT

public:
    explicit task(QWidget *parent = nullptr);
    ~task();

public slots:
    void slot_task_generator(QString task_number);
    //void slot_task_generator(QString task);

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::task *ui;

signals:
    void signal_mainwindow();



};

#endif // TASK_H
