#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::Init()
{
    socket_ = new QTcpSocket();
    socket_->connectToHost("127.0.0.1",27015);
    if(socket_->waitForConnected(1000)) {
        qDebug()<<"cann't connect server\n";
//        QThread::sleep(1);
//        socket_->connectToHost("127.0.0.1",27015);
    }

    qDebug()<<"state is"<< socket_->state();

    connect(socket_,&QTcpSocket::readyRead,this,[&](){
        QByteArray buff = socket_->readAll();
        qDebug()<<"get msg:"<<buff.size();
        ParsingBuf(buff);
    });

    connect(socket_, &QAbstractSocket::disconnected,socket_, &QObject::deleteLater);

    connect(socket_, &QAbstractSocket::errorOccurred,this,[&](QAbstractSocket::SocketError socketError){
        switch (socketError) {
            case QAbstractSocket::RemoteHostClosedError:
                break;
            case QAbstractSocket::HostNotFoundError:
                qDebug()<<"The host was not found. Please check the host name and port settings.";
                break;
            case QAbstractSocket::ConnectionRefusedError:
                qDebug()<<"The connection was refused by the peer. "
                                            "Make sure the fortune server is running, "
                                            "and check that the host name and port "
                                            "settings are correct.";
                break;
            default:
                qDebug()<<tr("The following error occurred: %1.").arg(socket_->errorString());
            }
    });
}

void Client::ParsingBuf(QByteArray buff)
{
    qDebug()<<"get msg:"<<buff.size();
    TestServer_Buff data;
    data = *(TestServer_Buff*)(buff.data()+sizeof(TestServer_Buff));

    emit sig_mainwindow_box(data.boxId,data.action);
}

void Client::SendBuff(TestServer_Buff buff)
{
    //socket send buf
    char * p = (char*)(&buff);
    QByteArray sendbuf(p,sizeof(buff));

    if(socket_ == nullptr)
    {
        qDebug()<<"no connect";
        return;
    }
    if(socket_->state() == QAbstractSocket::ConnectedState)
    {
        //debug
        qDebug()<<"send buf: "<<sizeof(sendbuf);
        socket_->write(sendbuf); //write the data itself
    }
}

void Client::slot_mainwindow_sendbuff()
{
    TestServer_Buff buff;
    buff.boxId = 1;
    buff.action = TestServer_BoxAction_UP;
    SendBuff(buff);
}
