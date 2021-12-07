#include "mainwindow.h"

#include <QApplication>
#include <QKeyboardDevice>
#include<QDebug>
#include<QSerialPort>
#include"barcodescanner.h"
//#include "ftpcontrolchannel.h"
//#include "ftpdatachannel.h"
#include"ftpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    BarcodeScanner barcodeScanner_manager;

//    QObject::connect(&w,&MainWindow::sig_barcode,&barcodeScanner_manager,&BarcodeScanner::slot_window);
//    Qt3DInput::QKeyboardDevice barcodeScanner;
//    QObject::connect(&barcodeScanner,&Qt3DInput::QKeyboardDevice::activeInputChanged,&barcodeScanner_manager,&BarcodeScanner::slot_keyboard);


//    QSerialPort* updateserial=new QSerialPort();
//    QString updateserialBuffer="";
//    updateserial->open(QIODevice::ReadOnly);
//    QObject::connect(updateserial,SIGNAL(readyRead()),&a,[&](){

//    });

    FtpClient client;
    client.Init_Url();
    return a.exec();
}
