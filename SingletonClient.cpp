#include "SingletonClient.h"
#include "authform.h"
//#include "mytcpserver.h"

SingletonClient::SingletonClient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;

    socket->connectToHost("127.0.0.1", 34576);

    connect(socket, &QTcpSocket::readyRead, this, &SingletonClient::slot_readFromServer);

    if(socket->isOpen())
             qDebug()<<"open";

}

SingletonClient::~SingletonClient()
{
    socket->close();
}

void SingletonClient::slot_readFromServer()
{
    QByteArray array;
    QString str = "";
    while(socket->bytesAvailable() > 0)
    {
        array = socket->readAll();
        str.append(array);
    }
    QList<QString> new_str = str.split('&');
    if (new_str[0] == '1')
    emit readFromServer("1");
    else if (new_str[0] == '0')
    emit readFromServer("0");
    else if(new_str[0] == "2")
    emit readFromServer("2");
    else if (new_str[0] == "mystat")
    {
    qDebug() << str << "   stroka statistick";
    qDebug() << "mystat -> readFromServer";
    emit readFromServer(str);
    }
    else if(new_str[0] == "stat")
    {
    qDebug() << "stat -> readFromServer";
    emit readFromServer(str);
    }
    else if(new_str[0] == "task")
    {
    qDebug() << "task -> readfromServer: " << str;
    emit readFromServer(str);
    }
}


bool SingletonClient::send_msg_to_server(QString query)
{
    qDebug() << query;
    socket -> write(query.toUtf8());
    return 1;
}




SingletonClient * SingletonClient::p_instance; // Выделение памяти
SingletonDestroyer SingletonClient::destroyer;
