#include "statistic.h"
#include "ui_statistic.h"
#include "SingletonClient.h"

Statistic::Statistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);
}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::on_pushButton_close_clicked()
{
    this -> close();
}

void Statistic::mystat(QString str)
{
    qDebug() << str;
    QStringList result = str.split('&', Qt::SkipEmptyParts);
    if (result[0] == "mystat")
    {
    ui -> table_statistic -> hide();
    ui -> label_name_2 -> hide();
    ui -> Filtr_1 -> hide();
    ui -> pushButton_back -> hide();
    qDebug() << result;
    ui ->label_stat_1->setText(result[1]);
    qDebug() << "result[1]" << result[1];
    ui -> label_stat_2 -> setText(result[2]);
    ui -> label_stat_3 -> setText(result[3]);
    ui -> label_stat_4 -> setText(result[4]);
    this -> show();
    }
    else if(result[0] == "stat")
    {
    result = str.split('|', Qt::SkipEmptyParts);
    if (result.last() == "%")
    {
        ui -> Filtr_1 -> hide();
        ui -> pushButton_back -> show();
        result.removeLast();
    }
    else
    {
        ui -> Filtr_1 -> show();
        ui -> pushButton_back -> hide();
    }
    qDebug() << "Stat for teacher: " <<result;
    ui -> label_stat_1 -> hide();
    ui -> label_stat_2 -> hide();
    ui -> label_stat_3 -> hide();
    ui -> label_stat_4 -> hide();
    ui -> label_task1 -> hide();
    ui -> label_task2 -> hide();
    ui -> label_task3 -> hide();
    ui -> label_task4 -> hide();
    ui -> table_statistic -> show();

    int Rows_num = result.size();
    int Colum_num = 6;

    QStandardItemModel *DataTableModel = new QStandardItemModel(Rows_num, Colum_num);

    for (int row = 0; row < Rows_num; ++row) {
                QStringList userData = result[row].split('&', Qt::SkipEmptyParts);
                qDebug() << "1 tut" <<userData;
                if (row == 0)
                    userData.removeFirst();
                qDebug() << "2 tut" <<userData;
                for (int col = 0; col < Colum_num; ++col) {
                    QStandardItem *item = new QStandardItem(userData[col]);
                    DataTableModel->setItem(row, col, item);
                }
    }

    DataTableModel->setHeaderData(0, Qt::Horizontal, "Имя");
    DataTableModel->setHeaderData(1, Qt::Horizontal, "Фамилия");
    DataTableModel->setHeaderData(2, Qt::Horizontal, "Отчество");
    DataTableModel->setHeaderData(3, Qt::Horizontal, "№1");
    DataTableModel->setHeaderData(4, Qt::Horizontal, "№2");
    DataTableModel->setHeaderData(5, Qt::Horizontal, "№3");
    DataTableModel->setHeaderData(6, Qt::Horizontal, "№4");

    SearchTableModel = new QSortFilterProxyModel(this);
    SearchTableModel->setSourceModel(DataTableModel);
    SearchTableModel->setFilterKeyColumn(-1);

    ui->table_statistic->setModel(SearchTableModel);
    ui->table_statistic->verticalHeader()->setVisible(false);
    ui->table_statistic->resizeRowsToContents();
    ui->table_statistic->resizeColumnsToContents();
    ui->table_statistic->setSortingEnabled(true);
    ui->table_statistic->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this -> show();
    }
}

void Statistic::on_Filtr_1_clicked()
{
    SingletonClient::getInstance()->send_msg_to_server("Filter_1");
    this -> close();
}


void Statistic::on_pushButton_back_clicked()
{
    SingletonClient::getInstance()->send_msg_to_server("stat");
    this -> close();
}

