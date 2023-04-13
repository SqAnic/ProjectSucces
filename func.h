#include <QDebug>
#include "SingletonDB.h"

void stat(const int connection_id)
{
    SingletonDB::getInstance()->stat(connection_id);
}
void auth(const QString login, const QString pass, const int connection_id){
    QString result = SingletonDB::getInstance()->authUser(login, pass, connection_id);
    if (result  == "error")
    {
        qDebug() << "error auth";
    }

    else if (result == "stud")
    {
        qDebug() << "Welcome Student!";
    }
    else if (result == "teach")
    {
        qDebug() << "Welcome Teacher!";
    }

}

void registration(const QString login, const QString name,const QString surname,const QString patronymic, const QString pass, const QString role, int connection_id)
{

    qDebug() << "Insert user result: " << SingletonDB::getInstance()->insertUser(login, name, surname, patronymic, pass, role);


    //SingletonDB::getInstance()->fetchAllUsers();

}

void logout(int connection_id)
{
    SingletonDB::getInstance()->logout(connection_id);
}

void Parsing(int connection_id, QString message){
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
        auth(login, pass, connection_id);
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
        registration(login, name, surname, patromynic, pass, role, connection_id);
        }
    }

    else if(parts[0] == "mystat"){
        stat(connection_id);
    }
    else if(parts[0] == "stat"){
        //stat();
    }


}
