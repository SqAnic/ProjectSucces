#include <QDebug>
#include <QCoreApplication>
#include "func.h"
#include "mytcpserver.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 34576)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "started";
    }
}

void MyTcpServer::slotNewConnection() {
    if (server_status == 1) {
        qDebug() << "New client connected";
        QTcpSocket *mTcpSocket = mTcpServer->nextPendingConnection(); // Для многопользовательского сервера
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        int connection_id = mTcpSocket->socketDescriptor(); // Генерация id
        mTcpSocket->write("Your connection ID: ");
        mTcpSocket->write(QString::number(connection_id).toUtf8());
        mTcpSocket->write("\r\n");
        mTcpSocket->flush(); // Добавьте эту строку
        Clients.insert(mTcpSocket, connection_id);
        connect(mTcpSocket, &QTcpSocket::readyRead,
                this, &MyTcpServer::slotServerRead);
        connect(mTcpSocket, &QTcpSocket::disconnected,
                this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket * mTcpSocket;
    mTcpSocket = (QTcpSocket*)sender(); // Для многопользовательского сервера
    QByteArray array;
    QString str;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array=mTcpSocket->readAll();
        str.append(array);
    }
    //mTcpSocket->write(str.toUtf8());
    qDebug()<< "recieve:"<<str;
    Parsing(this->getConnectionId(mTcpSocket), str.toUtf8(), *this);
    //qDebug() << str;
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *mTcpSocket = (QTcpSocket*)sender();
    int connection_id = this->getConnectionId(mTcpSocket);
    logout(connection_id);
    qDebug() << "Client disconnected";
    //QString connection_id = QString::number(Clients.value(mTcpSocket));
    Clients.remove(mTcpSocket);
    mTcpSocket->close();
}

int MyTcpServer::getConnectionId(QTcpSocket *socket)
{
    return Clients.value(socket);
}

QTcpSocket* MyTcpServer::getSocket(int connection_id)
{
        QMap<QTcpSocket*, int>::iterator i;
        for (i = Clients.begin(); i != Clients.end(); ++i) {
            if (i.value() == connection_id) {
                return i.key();
            }
        }
        return nullptr;  // возвращает nullptr, если не найден
}

void MyTcpServer::server_answer(int connection_id, QString answer, QString flag)
{
    QTcpSocket *mTcpSocket = MyTcpServer::getSocket(connection_id);
    if (flag == "0")
    {
        QList<QString> result = answer.split('&');

        if (result[0] == "1")
            mTcpSocket->write("1");
        else if (result[0] == "0")
            mTcpSocket->write("0");
        else if (result[0] == "mystat")
        {
            QString mystat = result[0] + "&" + result[1] + "&" + result[2] + "&" + result[3] + "&" + result[4];
            mTcpSocket->write(mystat.toUtf8());
        }
        else if(result[0] == "2")
            mTcpSocket->write("2");
    }
    else if (flag == "1")
    {
        mTcpSocket->write(answer.toUtf8());
    }
    else if (flag == "2")
    {
        qDebug() << answer << "Edu na client";
        mTcpSocket -> write(answer.toUtf8());
    }
}

