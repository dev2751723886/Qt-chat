#include "mytcpsocket.h"
#include "protocol.h"
#include "operatedb.h"
#include "mytcpserver.h"
#include "msghandler.h"
MyTcpSocket::MyTcpSocket()
{
    connect(this,&QTcpSocket::readyRead,this,&MyTcpSocket::recvMsg);
    connect(this,&QTcpSocket::disconnected,this,&MyTcpSocket::clientOffline);
    m_pmh=new MsgHandler;
}

MyTcpSocket::~MyTcpSocket()
{
    delete m_pmh;
}

void MyTcpSocket::sendMsg(PDU *respdu)
{
    qDebug() << 444444;
    if(respdu==NULL){
        return;
    }
    this->write((char*)respdu,respdu->uiTotalLen);
    qDebug()<<"sendMsg pdu->uiTotaLen "<<respdu->uiTotalLen
            <<"spdu->uiType"<<respdu->uiType
            <<"respdu->uiMsgLen "<<respdu->uiMsgLen
            <<"respdu->caData"<<respdu->caData
            <<"respdu->caData"<<respdu->caData+32
            <<"respdu->caMsg"<<respdu->caMsg;
    free(respdu);
    respdu=NULL;
}



PDU *MyTcpSocket::handleMsg(PDU *pdu)
{
    qDebug()<<"handleMsg->uiTotaLen "<<pdu->uiTotalLen
             <<"pdu->uiType"<<pdu->uiType
             <<"pdu->uiMsgLen "<<pdu->uiMsgLen
             <<"pdu->caData"<<pdu->caData
             <<"pdu->caData"<<pdu->caData+32
             <<"pdu->caMsg"<<pdu->caMsg;
    PDU* respdu=NULL;
    m_pmh->pdu=pdu;
    switch (pdu->uiType) {
    case ENUM_MSG_TYPE_REGIST_REQUEST:{
       respdu=m_pmh->regist();
        break;
    }
    case ENUM_MSG_TYPE_LOGIN_REQUEST:{
        respdu=m_pmh->login(m_strLoginName);
        break;
    }
    case  ENUM_MSG_TYPE_FINDUSER_REQUEST:{
        respdu=m_pmh->findUser();
        break;

    }
    case ENUM_MSG_TYPE_ONLINEUSER_REQUEST:{
        respdu=m_pmh->onlineUser();
        break;
    }
    case ENUM_MSG_TYPE_ADDFRIEND_REQUEST:{
        respdu=m_pmh->addFriend();
        break;
    }
    case  ENUM_MSG_TYPE_ADDFRIEND_AGREE_REQUEST:{
        respdu=m_pmh->addFriendaGree();
        break;
    }
    case ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST:{
        respdu=m_pmh->FlushAddfriend();
        break;
    }
    case  ENUM_MSG_TYPE_DEL_FRIEND_REQUEST:{
        respdu=m_pmh->delFriend();
        break;
    }
    case  ENUM_MSG_TYPE_CHAT_FRIEND_REQUEST:{
        respdu=m_pmh->ChatFriend();
        break;
    }
    case ENUM_MSG_TYPE_DIKER_FILE_REQUEST:{
        respdu=m_pmh->DikerFile();
        break;
    }
    case ENUM_MSG_TYPE_FLUSH_FILE_REQUEST:{
        respdu=m_pmh->Flushfile();
        break;
    }
    case ENUM_MSG_TYPE_DEL_FILE_REQUEST:{
        respdu=m_pmh->delfile();
        break;
    }
    case ENUM_MSG_TYPE_RENAME_FILE_REQUEST:{
        respdu=m_pmh->Renamefile();
        break;
    }
        default:
            break;
     }
    return respdu;
}

void MyTcpSocket::recvMsg()
{
    readMsg();
}

void MyTcpSocket::clientOffline()
{
  OperateDB::getInstance().handleOffline(m_strLoginName.toStdString().c_str());
  MyTcpServer::getInstance().removeSocket(this);
}

void MyTcpSocket::readMsg()
{
    qDebug()<<"recvMsg 接受消息长度"<<this->bytesAvailable();
    QByteArray data =this->readAll();
    buffer.append(data);
    while(buffer.size()>=int(sizeof (PDU))){
        PDU* pdu=(PDU*)buffer.data();
        if(buffer.size()<int(pdu->uiTotalLen)){
            break;
        }
        PDU* respdu=handleMsg(pdu);
        sendMsg(respdu);
        buffer.remove(0,pdu->uiTotalLen);
    }
}

