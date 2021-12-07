#include "ftpclient.h"

FtpClient::FtpClient(QObject *parent) : QObject(parent)
{

}

void FtpClient::Init_Url()
{
    QString ftp_url("ftp://test.rebex.net/pub/example/readme.txt");
    QString ftp_user("demo");
    QString ftp_password("password");

    QUrl url_api_ = QUrl(ftp_url);
    if (!url_api_.isValid()) {
        qDebug()<<"URL地址不合法！";
        return;
    }
    else if (url_api_.scheme() != "ftp") {
        qDebug()<<"URL地址必须以ftp开头！";
        return;
    }
    url_api_.setPort(21);
    url_api_.setUserName(ftp_user);
    url_api_.setPassword(ftp_password);

    QString folderPath("./");
    file_download_ = new QFile(folderPath + "/downloadfile.txt");
    file_download_->open(QIODevice::WriteOnly);

    //从服务器上下载文件到选中文件夹
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);



    QNetworkRequest request(url_api_);
    reply_ = accessManager->get(request);

    connect(reply_, SIGNAL(readyRead()), this, SLOT(readContent()));
    connect(accessManager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply){
        if(reply->error() == QNetworkReply::NoError)
        {
            reply->deleteLater();
            file_download_->flush();
            file_download_->close();
        }
    });
    connect(reply_, &QNetworkReply::downloadProgress, this, [&](qint64 bytesReceived,qint64 bytesTotal){
        qDebug()<<"downloading "<<bytesReceived/bytesTotal*100<<" %";
    });
    connect(reply_, &QNetworkReply::errorOccurred,this,[&](QNetworkReply::NetworkError code){
        qDebug()<<"error code is "<<code;
    });

}

void FtpClient::readContent()
{
    file_download_->write(reply_->readAll());
}
