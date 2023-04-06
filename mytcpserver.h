
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
public slots:
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
    //void slotReadClient();
private:
    QVector <QTcpSocket*> Sockets;
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    int server_status;
    int k = 0;
};
#endif // MYTCPSERVER_H






