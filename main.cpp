#include <QCoreApplication>
#include "mytcpserver.h"
#include "SingletonDB.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer server;

    QString ClearTableQuery = "DELETE FROM User;"; //Чистить заранее собранную таблицу
    QString CreateTableQuery = "CREATE TABLE IF NOT EXISTS User(id INTEGER PRIMARY KEY AUTOINCREMENT, login TEXT NOT NULL, name TEXT NOT NULL, surname TEXT NOT NULL, patronymic TEXT NOT NULL, pass TEXT NOT NULL, role TEXT NOT NULL, connection_id INTEGER , status_online INTEGER NOT NULL DEFAULT 0, task1_stat INTEGER, task2_stat INTEGER, task3_stat INTEGER, task4_stat INTEGER);";
    //QString DropTableQuery = "DROP TABLE User;";

    //qDebug() << "Drop table result: " << SingletonDB::getInstance()->Query_db(DropTableQuery); // Выполнение запросов типа Create/Delete/Drop
    qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(CreateTableQuery); // Выполнение запросов типа Create/Delete/Drop
    //qDebug() << "Clear table result: " << SingletonDB::getInstance()->Query_db(ClearTableQuery); // Чищу таблицу, пока она в тестовом варианте
    SingletonDB::getInstance()-> fetchAllUsers();
    return a.exec();
}


// CREATE TABLE User(login VARCHAR(20) NOT NULL, password VARCHAR(20) NOT NULL)
// INSERT INTO User(login, password) VALUES (user, )
