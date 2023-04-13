#include <QDebug>
#include <SingletonDB.h>
#include "mytcpserver.h"

void auth(const QString login, const QString pass, const QString role){
    QString result = SingletonDB::getInstance()->authUser(login, pass, role);
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

void registration(const QString login, const QString name,const QString surname,const QString patronymic, const QString pass, const QString role)
{

    qDebug() << "Insert user result: " << SingletonDB::getInstance()->insertUser(login, name, surname, patronymic, pass, role);
    SingletonDB::getInstance()->fetchAllUsers();

}

void Parsing(MyTcpServer *mTcpServer, QTcpSocket *mTcpSocket, QString message){
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
    else if(parts[0] == "logout"){
            if(parts.length() != 1)
            {
                qDebug() << "error";
            }
            else
            {
                int connection_id = mTcpServer->getConnectionId(mTcpSocket); // получение connection_id для текущего пользователя
                SingletonDB::getInstance()->logout(connection_id);

                mTcpServer->slotClientDisconnected();
            }
        }

}
