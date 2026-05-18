#include "protocol.h"
#include"stdlib.h"
#include"string.h"
PDU *mkPDU(uint uiMsgLen)
{
    uint uiTOtalLen=sizeof(PDU)+uiMsgLen;
    PDU* pdu= (PDU*)malloc(uiTOtalLen);
    if(pdu==NULL){
        exit(1);
    }
    memset(pdu,0,uiTOtalLen);
    pdu->uiMsgLen=uiMsgLen;
    pdu->uiTotalLen=uiTOtalLen;
    return pdu;
}
