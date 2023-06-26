#include "SingletonDB.h"

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

bool SingletonDB::insertUser(const QString login, const QString name, const QString surname, const QString patronymic, const QString pass, const QString role, const int connection_id) // Запись в таблицу пользователей
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO User(login, name, surname, patronymic, pass, role, connection_id) VALUES (:login, :name, :surname, :patronymic, :pass, :role, :connection_id)");
    query.bindValue(":login", login);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":patronymic", patronymic);
    query.bindValue(":pass", pass);
    query.bindValue(":role", role);
    query.bindValue(":connection_id", connection_id);

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
            result += QString("ID: %1 | Login: %2 | Name: %3 | Surname: %4 | Patronymic: %5 | Password: %6 | Role: %7 | connection_id: %8")
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

QString SingletonDB::stat() // Вывести таблицу ползователей
{
    QString result = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE  role != :role");
    query.bindValue(":role", "teach");
    bool isFirst = true;  // Добавляем флаг
    if (query.exec()) {
        while (query.next()) {
            QString prefix = isFirst ? "stat" : "";  // Если это первый цикл, добавляем 'stat', иначе добавляем пустую строку
            result += QString("%1&%2&%3&%4&%5&%6&%7")  // Обновляем строку формата, чтобы включить префикс
                    .arg(prefix.isEmpty() ? "" : prefix + "&")  // Если префикс пуст, добавляем пустую строку, иначе добавляем 'stat&'
                    .arg(query.value(query.record().indexOf("name")).toString())
                    .arg(query.value(query.record().indexOf("surname")).toString())
                    .arg(query.value(query.record().indexOf("patronymic")).toString())
                    .arg(query.value(query.record().indexOf("task1_stat")).toString())
                    .arg(query.value(query.record().indexOf("task2_stat")).toString())
                    .arg(query.value(query.record().indexOf("task3_stat")).toString())
                    .arg(query.value(query.record().indexOf("task4_stat")).toString());
            isFirst = false;  // Обновляем флаг
            qDebug() << result;
            result += QString("|");
        }
        result.chop(1);
        qDebug() << result;
        return result;
    }
    else qDebug() << "Fetch all users error: " << query.lastError().text();

}

QString SingletonDB::Filter_1() // Вывести таблицу ползователей
{
    QString result = "";
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE  role != :role");
    query.bindValue(":role", "teach");
    bool isFirst = true;  // Добавляем флаг
    if (query.exec()) {
        while (query.next()) {
            int task1_stat = query.value(query.record().indexOf("task1_stat")).toInt();
            int task2_stat = query.value(query.record().indexOf("task2_stat")).toInt();
            int task3_stat = query.value(query.record().indexOf("task3_stat")).toInt();
            int task4_stat = query.value(query.record().indexOf("task4_stat")).toInt();

            if (task1_stat > 1 && task2_stat > 1 && task3_stat > 1 && task4_stat > 1) {  // Проверяем, что все задания > 1
                QString prefix = isFirst ? "stat" : "";  // Если это первый цикл, добавляем 'stat', иначе добавляем пустую строку
                result += QString("%1&%2&%3&%4&%5&%6&%7&%8")  // Обновляем строку формата, чтобы включить префикс
                        .arg(prefix.isEmpty() ? "" : prefix + "&")  // Если префикс пуст, добавляем пустую строку, иначе добавляем 'stat&'
                        .arg(query.value(query.record().indexOf("name")).toString())
                        .arg(query.value(query.record().indexOf("surname")).toString())
                        .arg(query.value(query.record().indexOf("patronymic")).toString())
                        .arg(task1_stat)
                        .arg(task2_stat)
                        .arg(task3_stat)
                        .arg(task4_stat);
                isFirst = false;  // Обновляем флаг
                qDebug() << result;
                result += QString("|");
            }
        }
        result += "%";
        qDebug() << result;
        return result;
    }
    else qDebug() << "Fetch all users error: " << query.lastError().text();

}

QString SingletonDB::authUser(const QString &login, const QString &pass, int connection_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE login = :login AND pass = :pass");
    query.bindValue(":login", login);
    query.bindValue(":pass", pass);
    query.exec();

    if(query.next())
    {
        QString role = query.value(query.record().indexOf("role")).toString();

        // Update the connection_id for the logged in user
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE User SET connection_id = :connection_id WHERE login = :login AND pass = :pass");
        updateQuery.bindValue(":connection_id", connection_id);
        updateQuery.bindValue(":login", login);
        updateQuery.bindValue(":pass", pass);

        if(!updateQuery.exec())
        {
            qDebug() << "Unable to update connection_id for user:" << updateQuery.lastError();
        }

        if (role == "stud")
            return "auth&stud";
        else if (role == "teach")
            return "auth&teach";
    }
    else
    {
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

QString SingletonDB::stat(const int connection_id)
{
    QSqlQuery query;
    QString result = "";
    query.prepare("SELECT * FROM User WHERE connection_id = :connection_id");
    query.bindValue(":connection_id", connection_id);
    query.exec();

    if (query.next())
    {
        result += QString("mystat&%1&%2&%3&%4")
                   .arg(query.value(query.record().indexOf("task1_stat")).toString())
                   .arg(query.value(query.record().indexOf("task2_stat")).toString())
                   .arg(query.value(query.record().indexOf("task3_stat")).toString())
                   .arg(query.value(query.record().indexOf("task4_stat")).toString());
    }
    else
    {
        qDebug() << "No user found with connection_id = " << connection_id;
    }
    qDebug() << result;
    return result;
}
void SingletonDB::task_result(const int connection_id, const QString variant, bool flag)
{
    QSqlQuery query;
    QString task_number = variant + "_stat";
    if (flag == true)
    {
        QString query_string = QString("UPDATE User SET %1 = %1 + 1 WHERE connection_id = :connection_id;").arg(task_number);
        query.prepare(query_string);
        query.bindValue(":connection_id", connection_id);
        query.exec();
    }
    else if (flag == false)
    {
        QString query_string = QString("UPDATE User SET %1 = %1 - 1 WHERE connection_id = :connection_id;").arg(task_number);
        query.prepare(query_string);
        query.bindValue(":connection_id", connection_id);
        query.exec();
    }
}



SingletonDB *SingletonDB::p_instance;
SingletonDB_Destroyer SingletonDB::destroyer;


