
#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include "func.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

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
        QTcpSocket *mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        int connection_id = mTcpSocket->socketDescriptor();
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
    mTcpSocket = (QTcpSocket*)sender();
    QByteArray array;
    QString str;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array=mTcpSocket->readAll();
        str.append(array);
    }
    //mTcpSocket->write(str.toUtf8());
    qDebug()<< "recieve:"<<str;
    Parsing(this->getConnectionId(mTcpSocket), str.toUtf8());
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

//void MyTcpServer::server_answer(bool answer)
//{
//    QTcpSocket * mTcpSocket;
//    mTcpSocket = (QTcpSocket*)sender();
////  if (answer == 1)
////      mTcpSocket->write("1");
////  else if (answer == 0)
////      mTcpSocket->write("0");
//}
