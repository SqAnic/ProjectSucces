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
    void slot_task(QString task_number);

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::task *ui;


};

#endif // TASK_H
