#include "server.h"

#include <QFile>
#include <QDebug>
Server::Server(QWidget *parent)
    : QWidget(parent)

{
    loadConfig();
    MyTcpServer::getInstance().listen(QHostAddress(m_strIP),m_usPort);
}

Server::~Server()
{
}

void Server::loadConfig()
{

    QFile file(":/client.config");
    if(file.open(QIODevice::ReadOnly)){
         QString strData=QString(file.readAll());
         //qDebug()<<"strData"<<strData;
         QStringList List=strData.split("\r\n");
         m_strIP=List[0];
         m_usPort=List[1].toUShort();
         m_strRoot=List[2];
         qDebug()<<"loadConfig"<<m_strIP<<"m_usPort"<<m_usPort<<"mstrRoot"<<m_strRoot;
         file.close();
    }
    else{
        qDebug()<<"文件打开失败";
    }

}

Server &Server::getInstance()
{
    static Server instance;
    return instance;
}

