#ifndef SERVER_TEST_H
#define SERVER_TEST_H

#include <QObject>
#include<QTcpServer>
#include<QTcpSocket>

#include"common.h"

class Server_Test : public QObject
{
    Q_OBJECT
public:
    explicit Server_Test(QObject *parent = nullptr);
    ~Server_Test();
    void Init();
private:
    void ParsingBuf(QByteArray buff);
    void sendBuff(TestServer_Buff buff);
signals:
    void sig_jobmanager_boxArrive(int boxId,TestServer_BoxAction action);
public slots:
    void slot_tcp_newClient();
    void slot_jobmanager_boxAction(int boxId,TestServer_BoxAction action);
//    void slot_readData();
private:
    QTcpServer* tcpServer_;
    QTcpSocket* set_client_ = nullptr;
};

#endif // SERVER_TEST_H
