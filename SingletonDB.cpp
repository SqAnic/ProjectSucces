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
    qDebug() << query_str;
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

bool SingletonDB::insertUser(const QString login, const QString name, const QString surname, const QString patronymic, const QString pass, const QString role) // Запись в таблицу пользователей
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO User(login, name, surname, patronymic, pass, role) VALUES (:login, :name, :surname, :patronymic, :pass, :role)");
    query.bindValue(":login", login);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":patronymic", patronymic);
    query.bindValue(":pass", pass);
    query.bindValue(":role", role);

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

void SingletonDB::fetchAllUsers() // Вывести таблицу ползователей
{
    QString result = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM User;");
    if (query.exec()) {
        while (query.next()) {
            result += QString("ID: %1 | Login: %2 | Name: %3 | Surname: %4 | Patronymic: %5 | Password: %6 | Role: %7 | status_online: %8")
                .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
                .arg(query.value(3).toString())
                .arg(query.value(4).toString())
                .arg(query.value(5).toString())
                .arg(query.value(6).toString())
                .arg(query.value(7).toString());
            qDebug() << result;
            result = "";
        }
    }
    else qDebug() << "Fetch all users error: " << query.lastError().text();
}

void SingletonDB::stat() // Вывести таблицу ползователей
{
    QString result = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM User;");
    if (query.exec()) {
        while (query.next()) {
            result += QString("ID: %1 | Login: %2 | Name: %3 | Surname: %4 | Patronymic: %5 | task1_stat %6, task2_stat %7, task3_stat %8, task4_stat %9);")
                .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
                .arg(query.value(3).toString())
                .arg(query.value(4).toString())
                .arg(query.value(5).toString())
                .arg(query.value(6).toString())
                .arg(query.value(7).toString())
                .arg(query.value(8).toString());
            result = "";
        }
    }
    else qDebug() << "Fetch all users error: " << query.lastError().text();
}

QString SingletonDB::authUser(const QString login, const QString pass, const int connection_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE login = :login AND pass = :pass;");
    query.bindValue(":login", login);
    query.bindValue(":pass", pass);

    query.exec();

    QString res;

    if(query.next())
        {
            res = query.value(query.record().indexOf("role")).toString();
            query.prepare("UPDATE User SET status_online = :status_online, session_id = :session_id WHERE login = :login AND pass = :pass;");
            query.bindValue(":status_online", 1);
            query.bindValue(":session_id", connection_id);
            query.bindValue(":login", login);
            query.bindValue(":pass", pass);
            query.exec();

            return "auth&"+res;
        }
    else
    {
        qDebug() << "Error auth user: " << query.lastError().text();
        return "auth&error";
    }
}

void SingletonDB::logout(int connection_id)
{
    QSqlQuery query;
    query.prepare("UPDATE User SET status_online = 0, connection_id = NULL WHERE connection_id = :connection_id;");
    query.bindValue(":connection_id", connection_id);
    query.exec();
}

void SingletonDB::update_task(const QString connection_id, const QString task, const QString ans)
{
    QSqlQuery query;
    query.prepare("UPDATE User SET task"+task+" = task"+task + ans + " WHERE connection_id = :connection_id;");
    query.bindValue(":connection_id", connection_id);
    query.exec();
}

void SingletonDB::stat(const int connection_id)
{
    QSqlQuery query;
    QString result = "";
    query.prepare("SELECT * FROM User WHERE  connection_id = :connection_id AND status_online = st;");
    query.bindValue(":connection_id", connection_id);
    query.exec();
    result += QString("ID: %1 | Login: %2 | Name: %3 | Surname: %4 | Patronymic: %5 | task1_stat: %6 | task2_stat: %7 | task3_stat: %8 | task4_stat: %9")
        .arg(query.value(0).toString())
        .arg(query.value(1).toString())
        .arg(query.value(2).toString())
        .arg(query.value(3).toString())
        .arg(query.value(4).toString())
        .arg(query.value(5).toString())
        .arg(query.value(6).toString())
        .arg(query.value(7).toString())
        .arg(query.value(8).toString());
    qDebug() << result;
}
//Qstring SingletonDB::check_task(const QString connection_id, const QString task, const QString ans)
//{


//}

SingletonDB *SingletonDB::p_instance;
SingletonDB_Destroyer SingletonDB::destroyer;


