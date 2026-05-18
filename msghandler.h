#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include "protocol.h"

#include <QObject>

class MsgHandler
{
   // Q_OBJECT
public:
    PDU* pdu;//定义成员变量,以为下面函数都要用到
    MsgHandler();
    PDU* login(QString& strName);
    PDU* regist();
    PDU* findUser();
    PDU* onlineUser();
    PDU* addFriend();
    PDU* addFriendaGree();
    PDU* FlushAddfriend();
    PDU* delFriend();
    PDU* ChatFriend();
    PDU* DikerFile();
    PDU* Flushfile();
    PDU* delfile();
    PDU* Renamefile();
};

#endif // MSGHANDLER_H
