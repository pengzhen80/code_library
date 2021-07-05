#include "server_test.h"
#include<QDebug>
Server_Test::Server_Test(QObject *parent) : QObject(parent)
{

}

Server_Test::~Server_Test()
{
    set_client_->disconnectFromHost();
}

void Server_Test::Init()
{
    tcpServer_ = new QTcpServer();
    if(!tcpServer_->listen(QHostAddress("127.0.0.1"),TEST_SERVER_PORT))
    {
        qDebug()<<"Server_Test::Init failed";
        return;
    }
    connect(tcpServer_,&QTcpServer::newConnection,this,&Server_Test::slot_tcp_newClient);
}

void Server_Test::ParsingBuf(QByteArray buff)
{
    TestServer_Buff data;
    data.boxId = *(int*)buff.data();
    data.action = *(TestServer_BoxAction*)(buff.data()+sizeof(int));

    qDebug()<<"receive msg:"<<data.boxId<<data.action;
    emit sig_jobmanager_boxArrive(data.boxId,data.action);
}

void Server_Test::sendBuff(TestServer_Buff buff)
{
    //socket send buf
    char * p = (char*)(&buff);
    QByteArray sendbuf(p,sizeof(buff));

    if(set_client_ == nullptr)
    {
        qDebug()<<"no connect";
        return;
    }
    if(set_client_->state() == QAbstractSocket::ConnectedState)
    {
        //debug
        qDebug()<<"send buf: "<<buff.boxId<<buff.action;
        set_client_->write(sendbuf); //write the data itself
    }
}

void Server_Test::slot_tcp_newClient()
{
    qDebug()<<"Server_Test::slot_tcp_newClient : new connection";
    set_client_ = tcpServer_->nextPendingConnection();
    tcpServer_->close();
    connect(set_client_,&QTcpSocket::readyRead,this,[&](){
        QByteArray buf = set_client_->readAll();

        ParsingBuf(buf);
    });
    connect(set_client_, &QAbstractSocket::disconnected,set_client_, &QObject::deleteLater);
}

void Server_Test::slot_jobmanager_boxAction(int boxId,TestServer_BoxAction action)
{
    TestServer_Buff buff;
    buff.boxId = boxId;
    buff.action = action;

    sendBuff(buff);
}

//void Server_Test::slot_readData()
//{

//}
