#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include<QUrl>
#include<QDebug>
#include<QFile>
#include<QNetworkAccessManager>
#include<QNetworkReply>

class FtpClient : public QObject
{
    Q_OBJECT
public:
    explicit FtpClient(QObject *parent = nullptr);
    void Init_Url();
    void SetDownloadFolder();
public slots:
    void readContent();
signals:

private:
    QUrl* url_api_;
    QFile* file_download_;
    QNetworkReply* reply_;
};

#endif // FTPCLIENT_H
