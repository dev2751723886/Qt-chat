#include "operatedb.h"
#include<QDebug>
#include<QSqlError>
#include <QSqlQuery>
OperateDB::OperateDB(QObject *parent) : QObject(parent)
{
    m_db=QSqlDatabase::addDatabase("QMYSQL");
}

OperateDB::~OperateDB()
{
    m_db.close();
}

void OperateDB::connect()
{
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.setDatabaseName("test");
    if(m_db.open()){
        qDebug()<<"数据库连接成功";
    }
    else{
        qDebug()<<"数据库连接失败"<<m_db.lastError();
    }
}

OperateDB &OperateDB::getInstance()
{
    static OperateDB instance;
    return instance;
}

bool OperateDB::hanleRegist(char *caName, char *caPwd)
{
    if(caName==NULL||caPwd==NULL){
        return false;
    }
    QString sql=QString("select * from user_info where name='%1'").arg(caName);
    qDebug()<<"查询sql语句"<<sql;
    QSqlQuery q;
    if(!q.exec(sql)){
        return false;
    }
    if(q.next()){
        return false;
    }
    sql=QString("insert into user_info(name,pwd) values('%1','%2')").arg(caName).arg(caPwd);
    qDebug()<<"插入sql语句"<<sql;
    return q.exec(sql);
}

bool OperateDB::hanleLongin(char *caName, char *caPwd)
{
    if(caName==NULL||caPwd==NULL){
        return false;
    }
    QString sql=QString("select * from user_info where name='%1'and pwd='%2'").arg(caName).arg(caPwd);
    qDebug()<<"查询sql语句"<<sql;
    QSqlQuery q;
    if(!q.exec(sql)){
        return false;
    }
    if(!q.next()){
        return false;
    }
     sql=QString("update user_info set online=1 where name='%1'and pwd='%2'").arg(caName).arg(caPwd);
    qDebug()<<"更新sql语句"<<sql;
    return q.exec(sql);
}

void OperateDB::handleOffline(const char *caName)
{
    if(caName==NULL){
        return;
    }
   QSqlQuery q;
   QString sql=QString("update user_info set online=0 where name='%1'").arg(caName);
   qDebug()<<"更新sql语句"<<sql;
   q.exec(sql);
}

int OperateDB::handleFindUser(const char *caName)
{
    if(caName==NULL){
        return 3;
    }
    QString sql=QString("select online from user_info where name='%1'").arg(caName);
    qDebug()<<"查询sql语句"<<sql;
    QSqlQuery q;
    q.exec(sql);
    if(q.next()){
       return q.value(0).toInt();
    }
    return 2;
}

QStringList OperateDB::handleOnlineUser()
{
    QString sql=QString("select name from user_info where online=1");
    QSqlQuery q;
    q.exec(sql);
    QStringList restult ;
    restult.clear();
    while(q.next()){
        restult.append(q.value(0).toString());
    }
    return restult;
}

int OperateDB::handleaddFriend(const char *caName, const char *turCame)
{
    if(caName==NULL||turCame==NULL){
        return -3;
    }
    QString sql = QString(R"(select * from friend
    where
    (
    user_id=(select id from user_info where name='%1')
    and
    friend_id=(select id from user_info where name='%2')
    )
    or
    (
    user_id=(select id from user_info where name='%2')
    and
    friend_id=(select id from user_info where name='%1')
    );)").arg(caName).arg(turCame);
    qDebug()<<"查询好友"<<sql;
    QSqlQuery q;
    q.exec(sql);
    if(q.next()){
        return -2;
    }
    sql=QString("select online from user_info where name='%1'").arg(turCame);
    q.exec(sql);
    if(q.next()){
        return q.value(0).toInt();
    }
    return -1;
}

bool OperateDB::handleaddFriend_agree(const char *caName, const char *turCame)
{
    if(caName==NULL||turCame==NULL){
        return false;
    }
    QString sql = QString(R"(
                 insert into friend(user_id, friend_id)
                 select u1.id, u2.id
                 from user_info u1, user_info u2
                 where u1.name='%1' and u2.name='%2';
                 )").arg(caName).arg(turCame);
    QSqlQuery q;
    return q.exec(sql);
}

QStringList OperateDB::handleFlushFriend(const char *caName)
{
    QStringList res;
    if(caName==NULL){
        return res;
    }
    QString sql=QString(R"(select name from user_info
                        where id in (
                            select user_id from friend where friend_id=
                            (select id from user_info where name='%1')
                            union
                            select friend_id from friend where user_id=
                            (select id from user_info where name='%1')
                        )and online=1)").arg(caName);
    QSqlQuery q;
    q.exec(sql);
    while(q.next()){
        res.append(q.value(0).toString());
    }
    qDebug()<<res;
    return res;
}

bool OperateDB::handldelFriend(const char *caName, const char *turCame)
{
    if(caName==NULL||turCame==NULL){
        return false;
    }
    QString sql = QString(R"(delete from friend
    where
    (
    user_id=(select id from user_info where name='%1')
    and
    friend_id=(select id from user_info where name='%2')
    )
    or
    (
    user_id=(select id from user_info where name='%2')
    and
    friend_id=(select id from user_info where name='%1')
    );)").arg(caName).arg(turCame);
    qDebug()<<"删除好友"<<sql;
    QSqlQuery q;
   return q.exec(sql);

}


