
#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include "func.cpp"

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

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
          mTcpSocket = new QTcpSocket;
          mTcpSocket = mTcpServer->nextPendingConnection();
          //mTcpSocket->write("Hello, World!!!I am echo server!\r\n");
          connect(mTcpSocket, &QTcpSocket::readyRead,
                  this,&MyTcpServer::slotServerRead);
          connect(mTcpSocket,&QTcpSocket::disconnected,
                  this,&MyTcpServer::slotClientDisconnected);
          Sockets.push_back(mTcpSocket);
      }
}

void MyTcpServer::slotServerRead(){
    mTcpSocket = (QTcpSocket*)sender();
    QByteArray array;
    QString str;
    while(mTcpSocket->bytesAvailable()>0)
    {
        array=mTcpSocket->readAll();
        str.append(array);
    }
    //mTcpSocket->write(str.toUtf8());
    Parsing(str.toUtf8());
    //qDebug() << str;
}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
