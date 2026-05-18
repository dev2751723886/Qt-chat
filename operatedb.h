#ifndef OPERATEDB_H
#define OPERATEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QWidget>

class OperateDB : public QObject
{
    Q_OBJECT
public:

    QSqlDatabase m_db;
    ~OperateDB();
    void connect();
    static OperateDB& getInstance();
    bool hanleRegist(char*caName,char*caPwd);
    bool hanleLongin(char*caName,char*caPwd);
    void handleOffline(const char *caName);
    int handleFindUser(const char *caName);
    QStringList handleOnlineUser();
    int handleaddFriend(const char *caName,const char*turCame);
    bool handleaddFriend_agree(const char *caName,const char*turCame);
    QStringList handleFlushFriend(const char *caName);
    bool handldelFriend(const char *caName,const char* turCame);

private:
    explicit OperateDB(QObject *parent = nullptr);
    OperateDB(const OperateDB& instance)=delete;
    OperateDB& operator=(const OperateDB&)=delete;

signals:

};

#endif // OPERATEDB_H
