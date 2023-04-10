#include <QCoreApplication>
#include "mytcpserver.h"
#include "SingletonDB.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer server;
    QString ClearTableQuery = "DELETE FROM User;"; //Чистить заранее собранную таблицу
    QString CreateTableQuery = "CREATE TABLE IF NOT EXISTS User(id INT NOT NULL, login TEXT NOT NULL, name TEXT NOT NULL, surname TEXT NOT NULL, patronymic TEXT NOT NULL, pass TEXT NOT NULL, role TEXT NOT NULL);"; //Создать таблицу
    QString DropTableQuery = "DROP TABLE User;";

    //qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(DropTableQuery); // Выполнение запросов типа Create/Delete/Drop
    qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(CreateTableQuery); // Выполнение запросов типа Create/Delete/Drop
    //qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(ClearTableQuery); // Чищу таблицу, пока она в тестовом варианте
    SingletonDB::getInstance()-> fetchAllUsers();
    return a.exec();
}


// CREATE TABLE User(login VARCHAR(20) NOT NULL, password VARCHAR(20) NOT NULL)
// INSERT INTO User(login, password) VALUES (user, )
