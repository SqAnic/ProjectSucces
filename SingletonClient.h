#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class SingletonClient;

class SingletonDestroyer
{
    private:
        SingletonClient * p_instance;
    public:
        ~SingletonDestroyer() { delete p_instance;}
        void initialize(SingletonClient * p){p_instance = p;}
};

class SingletonClient : public QObject
{
    Q_OBJECT
private:
    static SingletonClient * p_instance;
    static SingletonDestroyer destroyer;
    QTcpSocket * socket;
protected:
    explicit SingletonClient(QObject * parent = nullptr);
    SingletonClient(const SingletonClient&) = delete;
    SingletonClient& operator =(SingletonClient&) = delete;
    ~SingletonClient();
    friend class SingletonDestroyer;

private slots:
    void slot_readFromServer();

public:
    bool send_msg_to_server (QString query);
    static SingletonClient* getInstance() {
        if (!p_instance) {
            p_instance = new SingletonClient();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }
signals:
    void msg_from_server(QString);
    void readFromServer(const QString& str);
};




