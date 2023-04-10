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
    query.prepare("INSERT INTO User(id, login, name, surname, patronymic, pass, role) VALUES (:id, :login, :name, :surname, :patronymic, :pass, :role)");
    query.bindValue(":id", id);
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
        id += 1;
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
            result += QString("ID: %1 | Login: %2 | Name: %3 | Surname: %4 | Patronymic: %5 | Password: %6 | Role: %7")
                .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
                .arg(query.value(3).toString())
                .arg(query.value(4).toString())
                .arg(query.value(5).toString())
                .arg(query.value(6).toString());
            qDebug() << result;
            result = "";
        }
    }
    else qDebug() << "Fetch all users error: " << query.lastError().text();
}

QString SingletonDB::authUser(const QString login, const QString pass, const QString role)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE login = :login AND pass = :pass AND role = :role;");
    query.bindValue(":login", login);
    query.bindValue(":pass", pass);
    query.bindValue(":role", role);
    if (role == "stud")
    {
        query.exec();
        if(query.at() != -1){
            qDebug() << "Error auth user: " << query.lastError().text();
            //qDebug() << query.at();
            return 0;
        }
        else
        {
            //qDebug() << query.at();
            return "stud";
        }
    }
    else if(role =="teach")
    {
        query.exec();
        if(query.at() != -1){
            qDebug() << "Error auth user: " << query.lastError().text();
            //qDebug() << query.at();
            return 0;
        }
        else
        {
            //qDebug() << query.at();
            return "teach";
        }
    }
}

SingletonDB *SingletonDB::p_instance;
SingletonDB_Destroyer SingletonDB::destroyer;


