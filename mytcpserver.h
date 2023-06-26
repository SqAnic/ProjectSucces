
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
    QTcpSocket* getSocket(int connection_id);
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    void server_answer(int connection_id, QString answer, QString flag);
    //void server_answer(int connection_id, QList answer);
private:
    QTcpServer * mTcpServer;
    QMap<QTcpSocket*, int> Clients;
    int server_status;
};
#endif // MYTCPSERVER_H






