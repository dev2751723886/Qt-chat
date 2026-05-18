#include "mytcpserver.h"
#include<QDebug>
#include <QFile>
#include"mytcpsocket.h"
MyTcpServer::MyTcpServer()
{

}

MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    qDebug()<<"新客户端连接成功";
    MyTcpSocket* PTcpSocket=new MyTcpSocket;
    PTcpSocket->setSocketDescriptor(handle);
    m_tcpSocketList.append(PTcpSocket);
    for(int i=0;i<m_tcpSocketList.size();i++){
        qDebug()<<m_tcpSocketList[i];
    }

}

void MyTcpServer::removeSocket(MyTcpSocket *mysocket)
{
    if(mysocket==NULL){
        return;
    }
     mysocket->deleteLater();
     mysocket=NULL;
     for(int i=0;i<m_tcpSocketList.size();i++){
         qDebug()<<m_tcpSocketList[i]->m_strLoginName;
     }
}

void MyTcpServer::resend(char *tarName, PDU *pdu)
{
    if(tarName==NULL||pdu==NULL){
        return;
    }
    for(int i=0;i<m_tcpSocketList.size();i++){
        if(tarName==m_tcpSocketList[i]->m_strLoginName){
            m_tcpSocketList[i]->write((char*)pdu,pdu->uiTotalLen);
            qDebug()<<"resendMsg1 pdu->uiTotaLen "<<pdu->uiTotalLen
                    <<"spdu->uiType"<<pdu->uiType
                    <<"respdu->uiMsgLen "<<pdu->uiMsgLen
                    <<"respdu->caData"<<pdu->caData
                    <<"respdu->caData"<<pdu->caData+32
                    <<"respdu->caMsg"<<pdu->caMsg;
        }

    }
}


