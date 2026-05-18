#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include "msghandler.h"
#include "protocol.h"

#include <QObject>
#include <QTcpSocket>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket();
    ~MyTcpSocket();
    QString m_strLoginName;
    void sendMsg(PDU* respdu);
    void readMsg();
    QByteArray buffer;
    MsgHandler* m_pmh;
    PDU* handleMsg(PDU* pdu);
public slots:
    void recvMsg();
    void clientOffline();

};

#endif // MYTCPSOCKET_H
