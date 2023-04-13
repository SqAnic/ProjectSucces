
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QAbstractSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
    int getConnectionId(QTcpSocket *socket);
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    //QString check_task(QString const connection_id, QString const task, QString cans);
    //void slotReadClient();
private:
    //QVector <QTcpSocket*> Sockets;
    QTcpServer * mTcpServer;
    //QTcpSocket * mTcpSocket;
    QMap<QTcpSocket*, int> Clients;
    int server_status;
};
#endif // MYTCPSERVER_H






