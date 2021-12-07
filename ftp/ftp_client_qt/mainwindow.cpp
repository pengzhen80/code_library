#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->menubar->hide();
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    //for page store multi's table view
    table_store_multi_model_ = new QStandardItemModel();
    table_store_multi_model_->setColumnCount(3);
    table_store_multi_model_->setHeaderData(0,Qt::Horizontal,QString(tr("姓名")));
    table_store_multi_model_->setHeaderData(1,Qt::Horizontal,QString(tr("手機")));
    table_store_multi_model_->setHeaderData(2,Qt::Horizontal,QString(tr("選取")));

    ui->tableView->setModel(table_store_multi_model_);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //hide the row count
    ui->tableView->verticalHeader()->hide();

    QList<QStandardItem *> table_items;
    QStandardItem *Item_name = new QStandardItem("name");
    Item_name->setTextAlignment(Qt::AlignCenter);
    table_items.append(Item_name);
    QStandardItem *Item_phone = new QStandardItem("123");
    Item_phone->setTextAlignment(Qt::AlignCenter);
    table_items.append(Item_phone);
    QStandardItem *Item_flag = new QStandardItem(tr("✓"));
    Item_flag->setTextAlignment(Qt::AlignCenter);
    table_items.append(Item_flag);
    table_store_multi_model_->appendRow(table_items);
//    ui->tableView_store_multi->resizeRowToContents(vec_tmp_item_.size()-1);
    ui->tableView->resizeRowsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent  *event)
{
//    qDebug()<<event->count();
    emit sig_barcode(event->text());
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_2);
}
