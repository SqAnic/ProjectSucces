#include <QCoreApplication>
#include "mytcpserver.h"
#include "SingletonDB.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
    QString ClearTableQuery = "DELETE FROM User;"; //Чистить заранее собранную таблицу
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS User(login TEXT NOT NULL, password TEXT NOT NULL);"; //Создать таблицу

    qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(createTableQuery); // Выполнение запросов типа Create/Delete/Drop
    qDebug() << "Create table result: " << SingletonDB::getInstance()->Query_db(ClearTableQuery); // Чищу таблицу, пока она в тестовом варианте

    // Вставка пользователей в таблицу
    qDebug() << "Insert user1 result: " << SingletonDB::getInstance()->insertUser("user1", "pass1");
    qDebug() << "Insert user2 result: " << SingletonDB::getInstance()->insertUser("user2", "pass2");

    // Извлечение всех пользователей из таблицы и вывод их на экран
    QList<QPair<QString, QString>> users = SingletonDB::getInstance()->fetchAllUsers();
    for (const auto &user : users)
    {
        qDebug() << "User: " << user.first << ", Password: " << user.second;
    }

    return a.exec();
}


// CREATE TABLE User(login VARCHAR(20) NOT NULL, password VARCHAR(20) NOT NULL)
// INSERT INTO User(login, password) VALUES (user, )
