 #ifndef SERVER_H
#define SERVER_H

#include "mytcpserver.h"

#include <QWidget>
class Server : public QWidget
{
    Q_OBJECT
public:
    ~Server();
    void loadConfig();
    static Server& getInstance();
    QString m_strIP;
    QString m_strRoot;
    quint16 m_usPort;
private:
    Server(QWidget *parent = nullptr);
    Server(const Server& inctance)=delete;
    Server& operator=(const Server&)=delete;
};
#endif // SERVER_H
