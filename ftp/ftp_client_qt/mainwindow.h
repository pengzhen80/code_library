#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>
#include<QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#define PAGE_1 0
#define PAGE_2 1

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void keyPressEvent(QKeyEvent  *event);
signals:
    void sig_barcode(QString str);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * table_store_multi_model_;
};
#endif // MAINWINDOW_H
