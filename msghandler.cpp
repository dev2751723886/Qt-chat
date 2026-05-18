#include "msghandler.h"
#include "operatedb.h"
#include<QDebug>
#include <QDir>
#include "mytcpserver.h"
#include "server.h"
#include "protocol.h"
MsgHandler::MsgHandler()
{

}

PDU *MsgHandler::login(QString &strName)
{
    char caName[32]={'\0'};
    char caPwd[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    memcpy(caPwd,pdu->caData+32,32);
    bool ret=OperateDB::getInstance().hanleLongin(caName,caPwd);
    qDebug()<<"login ret"<<ret;
    if(ret){
        strName=caName;
    }
    PDU* respdu=mkPDU();
    memcpy(respdu->caData,&ret,sizeof(bool));
    respdu->uiType=ENUM_MSG_TYPE_LOGINT_RESPOND;
    return respdu;
}

PDU *MsgHandler::regist()
{
    char caName[32]={'\0'};
    char caPwd[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    memcpy(caPwd,pdu->caData+32,32);
    bool ret=OperateDB::getInstance().hanleRegist(caName,caPwd);
    qDebug()<<"redgist ret"<<ret;
    if(ret){
      QDir dir;
      dir.mkdir(QString("%1/%2").arg(Server::getInstance(). m_strRoot).arg(caName));
      qDebug()<<"创建目录"<<QString("%1/%2").arg(Server::getInstance(). m_strRoot).arg(caName);
    }
    PDU* respdu=mkPDU();
    memcpy(respdu->caData,&ret,sizeof(bool));
    respdu->uiType=ENUM_MSG_TYPE_REGIST_RESPOND;
    return respdu;
}

PDU *MsgHandler::findUser()
{
    char caName[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    int ret=OperateDB::getInstance().handleFindUser(caName);
    PDU* respdu=mkPDU();
    memcpy(respdu->caData,&ret,sizeof(int));
    respdu->uiType=ENUM_MSG_TYPE_FINDUSERT_RESPOND;
    return respdu;
}

PDU *MsgHandler::onlineUser()
{
    QStringList ret=OperateDB::getInstance().handleOnlineUser();
    qDebug()<<"ret size"<<ret.size();
    PDU* respdu=mkPDU(ret.size()*32);
    for(int i=0;i<ret.size();i++){
        qDebug()<<"name"<<ret[i];
        memcpy(respdu->caMsg+i*32,ret[i].toStdString().c_str(),32);

    }
    respdu->uiType=ENUM_MSG_TYPE_ONLINEUSER_RESPOND;
    return respdu;
}

PDU *MsgHandler::addFriend()
{
    char caName[32]={'\0'};
    char turname[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    memcpy(turname,pdu->caData+32,32);
    int ret=OperateDB::getInstance().handleaddFriend(caName,turname);
    qDebug()<<"addfriend ret"<<ret;
    if(ret==1){
        MyTcpServer::getInstance().resend(caName,pdu);
        qDebug()<<"ccc";
        return NULL;
    }
    PDU* respdu=mkPDU();
    respdu->uiType= ENUM_MSG_TYPE_ADDFRIEND_RESPOND;
    memcpy(respdu->caData,&ret,sizeof (int));
    return respdu;

}

PDU *MsgHandler::addFriendaGree()
{
    char caName[32]={'\0'};
    char turname[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    memcpy(turname,pdu->caData+32,32);
    bool ret=OperateDB::getInstance().handleaddFriend_agree(caName,turname);
    qDebug()<<"ADDFRIEND AGREE ret "<<ret;
    PDU* respdu=mkPDU();
    respdu->uiType=ENUM_MSG_TYPE_ADDFRIEND_AGREE_RESPOND;
    memcpy(respdu->caData,&ret,sizeof (bool));
    MyTcpServer::getInstance().resend(caName,respdu);
    return respdu;

}

PDU *MsgHandler::FlushAddfriend()
{
    char caName[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    QStringList List=OperateDB::getInstance().handleFlushFriend(caName);
    qDebug()<<"List size"<<List.size();
    PDU* respdu=mkPDU(List.size()*32);
    for(int i=0;i<List.size();i++){
        qDebug()<<"name"<<List[i];
        memcpy(respdu->caMsg+i*32,List[i].toStdString().c_str(),32);

    }
    respdu->uiType=ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND;
    return respdu;

}

PDU *MsgHandler::delFriend()
{
    char caName[32]={'\0'};
    char turname[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    memcpy(turname,pdu->caData+32,32);
    bool ret=OperateDB::getInstance().handldelFriend(caName,turname);
    qDebug()<<"delfriend ret"<<ret;
    PDU* respdu=mkPDU();
    respdu->uiType=ENUM_MSG_TYPE_DEL_FRIEND_RESPOND;
    memcpy(respdu->caData,&ret,sizeof (bool));
    return respdu;
}

PDU *MsgHandler::ChatFriend()
{
    char turname[32]={'\0'};
    memcpy(turname,pdu->caData+32,32);
    MyTcpServer::getInstance().resend(turname,pdu);
    return NULL;
}

PDU *MsgHandler::DikerFile()
{
     char File_name[32]={'\0'};
     memcpy(File_name,pdu->caData,32);
     QString File_Path=QString("%1/%2").arg(pdu->caMsg).arg(File_name);
     qDebug()<<"File_path"<<File_Path;
     QDir dir;
     bool ret=dir.mkdir(File_Path);
     PDU* respdu=mkPDU();
     memcpy(respdu->caData,&ret,sizeof(int));
     respdu->uiType=ENUM_MSG_TYPE_DIKER_FILE_RESPOND;
     return respdu;
}

PDU *MsgHandler::Flushfile()
{
    QDir dir(pdu->caMsg);
    QFileInfoList fileInfoList=dir.entryInfoList();
    PDU* respdu=mkPDU(sizeof(FileInfo)*(fileInfoList.size()-2));
    respdu->uiType=ENUM_MSG_TYPE_FLUSH_FILE_RESPOND;
    for(int i=0,j=0;i<fileInfoList.size();i++){
        if(fileInfoList[i].fileName()==QString(".")||fileInfoList[i].fileName()==QString("..")){
            continue;
        }
        FileInfo* pFileInfo=(FileInfo*)respdu->caMsg+j++;
        memcpy(pFileInfo->caName,fileInfoList[i].fileName().toStdString().c_str(),32);
        if(fileInfoList[i].isDir()){
            pFileInfo->uiType=0;
        }
        else{
          pFileInfo->uiType=1;
        }
        qDebug()<<"caName"<<pFileInfo->caName<<"uiType"<<pFileInfo->uiType;
    }
    return respdu;
}

PDU *MsgHandler::delfile()
{
    char* path=pdu->caMsg;
    uint uiType=0;
    memcpy(&uiType,pdu->caData,sizeof(uint));
    bool ret;
    if(uiType==0){
        QDir dir(path);
        ret=dir.removeRecursively();
    }
    else{
        QFile file(path);
        ret=file.remove();

    }
    PDU* respdu=mkPDU();
    memcpy(respdu->caData,&ret,sizeof(int));
    respdu->uiType=ENUM_MSG_TYPE_DEL_FILE_RESPOND;
    return respdu;
}

PDU *MsgHandler::Renamefile()
{
    char caOldName[32]={'\0'};
    char caNewName[32]={'\0'};
    memcpy(caOldName,pdu->caData,32);
    memcpy(caNewName,pdu->caData+32,32);
    char* pPach=pdu->caMsg;
    QString oldPath=QString("%1/%2").arg(pPach).arg(caOldName);
    QString newPath=QString("%1/%2").arg(pPach).arg(caNewName);
    PDU* respdu=mkPDU(0);
    respdu->uiType= ENUM_MSG_TYPE_RENAME_FILE_RESPOND;
    QDir dir;
    bool ret=dir.rename(oldPath,newPath);
    memcpy(respdu->caData,&ret,sizeof(bool));
    return respdu;
}
