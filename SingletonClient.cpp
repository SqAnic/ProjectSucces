#include "SingletonClient.h"
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
    if (str == '1')
    qDebug() << "Success";
    else if (str == '0')
    qDebug() << "Error";
    emit readFromServer(str);
}


bool SingletonClient::send_msg_to_server(QString query)
{
    qDebug() << query;
    socket -> write(query.toUtf8());
    return 1;
}


SingletonClient * SingletonClient::p_instance; // Выделение памяти
SingletonDestroyer SingletonClient::destroyer;
