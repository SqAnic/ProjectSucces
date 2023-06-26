#ifndef STATISTIC_H
#define STATISTIC_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class Statistic;
}

class Statistic : public QWidget
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = nullptr);
    ~Statistic();

public slots:
    void mystat(QString str);

private slots:
    void on_pushButton_close_clicked();

    void on_Filtr_1_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::Statistic *ui;
    QSortFilterProxyModel *SearchTableModel;
};

#endif // STATISTIC_H
