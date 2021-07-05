#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<QThread>
#include<QTimer>

#include"common.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client()
    {
        if(socket_ == nullptr)
        {
            return;
        }
        if(socket_->state() == QAbstractSocket::ConnectedState)
        {
            socket_->close();
            socket_ = nullptr;
        }
    }
    void Init();
private:
    void ParsingBuf(QByteArray buff);
    void SendBuff(TestServer_Buff buff);
public slots:
    void slot_mainwindow_sendbuff();
signals:
    void sig_mainwindow_box(int boxId,TestServer_BoxAction action);
private:
    QTcpSocket* socket_;
};

#endif // CLIENT_H
