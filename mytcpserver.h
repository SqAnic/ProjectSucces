
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
    //void server_answer(bool answer);
private:
    QTcpServer * mTcpServer;
    QMap<QTcpSocket*, int> Clients;
    int server_status;
};
#endif // MYTCPSERVER_H






