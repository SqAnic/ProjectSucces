#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QFile>
#include <QUuid>

class SingletonDB;

class SingletonDB_Destroyer
{
    private:
        SingletonDB * p_instance;
    public:
        ~SingletonDB_Destroyer() { delete p_instance;}
        void initialize(SingletonDB * p){p_instance = p;}
};


class SingletonDB
{
    private:
        static SingletonDB * p_instance; // Статик - память не выделяется классом, единственный экземлпяр
        static SingletonDB_Destroyer destroyer;
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    protected:

        SingletonDB();
        SingletonDB(const SingletonDB& );
        SingletonDB& operator = (SingletonDB &);
        ~SingletonDB();
        friend class SingletonDB_Destroyer;
    public:
        QString check_task(const QString connection_id, const QString task, const QString ans);
        bool insertUser(const QString login, const QString name, const QString surname, const QString patronymic, const QString pass, const QString role);
        bool Query_db(QString query_str);
        void fetchAllUsers();
        void logout(int connection_id);
        QString authUser(const QString login, const QString pass, const QString role);
        static SingletonDB *getInstance(){
            if (!p_instance)
            {
                p_instance = new SingletonDB();
                destroyer.initialize(p_instance); // Присваивание ссылки на синглтн в Destroyer
            }
            return p_instance;
        }
        int id;
};
