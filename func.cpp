#include <QDebug>
#include <SingletonDB.h>

void auth(QString login, QString pass, QString role){
    if (SingletonDB::getInstance()->authUser(login, pass, role) == "error")
    {
        qDebug() << "error auth";
    }
    else if (SingletonDB::getInstance()->authUser(login, pass, role) == "stud")
    {
        qDebug() << "Welcome Student!";
    }
    else if (SingletonDB::getInstance()->authUser(login, pass, role) == "teach")
    {
        qDebug() << "Welcome Teacher!";
    }

}

void registration(QString login, QString name,QString surname,QString patronymic, QString pass, QString role)
{

    qDebug() << "Insert user result: " << SingletonDB::getInstance()->insertUser(login, name, surname, patronymic, pass, role);
    SingletonDB::getInstance()->fetchAllUsers();

}

void Parsing(QString message){
    QList<QString> parts = message.split('&');
    qDebug() << parts[0];
    if(parts[0] == "auth"){
        if (parts.length() != 4){
            qDebug() << "error";
        }
        else{
        QString login = parts[1];
        QString pass = parts[2];
        QString role = parts[3];
        auth(login, pass, role);
        }
    }
    else if(parts[0] == "register"){
        if (parts.length() != 7)
        {
            qDebug() << "error";
        }
        else
        {
        QString login = parts[1];
        QString name = parts[2];
        QString surname = parts[3];
        QString patromynic = parts[4];
        QString pass = parts[5];
        QString role = parts[6];
        registration(login, name, surname, patromynic, pass, role);
        }
    }
}
