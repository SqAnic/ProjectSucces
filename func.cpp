#include <QDebug>

void login(QByteArray username, QByteArray password){
    qDebug() << username << password;
}

void registration(QByteArray username, QByteArray mail, QByteArray password){
    qDebug() << username << mail << password;
}

void Parsing(QByteArray message){
    QList<QByteArray> parts = message.split('&');
    qDebug() << parts[0];
    if(parts[0] == "login"){
        if (parts.length() != 3){
            qDebug() << "error";
        }
        else{
        QByteArray username = parts[1];
        QByteArray password = parts[2];
        login(username, password);
        }
    }
    else if(parts[0] == "register"){
        if (parts.length() != 4){
            qDebug() << "error";
        }
        else{
        QByteArray username = parts[1];
        QByteArray mail = parts[2];
        QByteArray password = parts[3];
        registration(username, mail, password);
        }
    }
}
