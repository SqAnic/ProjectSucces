#include <SingletonDB.h>


SingletonDB::SingletonDB()
{
    db.setDatabaseName("myDB.db");


    if(!db.open())
        qDebug()<<db.lastError().text();
    else
        qDebug() << "Succes";
}

SingletonDB::~SingletonDB()
{
    db.close();
}

bool SingletonDB::Query_db(const QString query_str) // Запросы типа Create/Dealete
{
    QSqlQuery query(db);
    query.prepare(query_str);
    //qDebug() << query_str;
    if (!query.exec())
    {
        qDebug() << "Error executing query: " << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool SingletonDB::insertUser(const QString &login, const QString &password) // Запись в таблицу пользователей
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO User(login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec())
    {
        qDebug() << "Error inserting user: " << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

QList<QPair<QString, QString>> SingletonDB::fetchAllUsers() // Вывести таблицу ползователей
{
    QSqlQuery query(db);
    query.prepare("SELECT login, password FROM User");

    if (!query.exec())
    {
        qDebug() << "Error fetching users: " << query.lastError().text();
        return QList<QPair<QString, QString>>();
    }
    else
    {
        QList<QPair<QString, QString>> users;
        while (query.next())
        {
            users.append(QPair<QString, QString>(query.value(0).toString(), query.value(1).toString()));
        }
        return users;
    }
}

SingletonDB *SingletonDB::p_instance;
SingletonDB_Destroyer SingletonDB::destroyer;


