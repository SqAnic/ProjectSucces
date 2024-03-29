#include <QDebug>
#include "SingletonDB.h"
#include <mytcpserver.h>

void stat(const int connection_id)
{
    SingletonDB::getInstance()->stat(connection_id);
}
void auth(const QString login, const QString pass, const int connection_id){
    QString result = SingletonDB::getInstance()->authUser(login, pass, connection_id);
    if (result  == "auth&error")
    {

    }

    else if (result == "auth&stud")
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

    qDebug() << "Inser user result: " << SingletonDB::getInstance()->insertUser(login, name, surname, patronymic, pass, role);
    SingletonDB::getInstance()->fetchAllUsers();

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
        if (parts.length() != 3){
            qDebug() << "error";
        }
        else{
        QString login = parts[1];
        QString pass = parts[2];
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
        SingletonDB::getInstance()->stat(connection_id);
    }
    else if(parts[0] == "stat"){
        SingletonDB::getInstance()->stat();
    }


}
