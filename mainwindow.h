#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myaddressbookmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_an_Address_Book_triggered();

    void dial(const QString&)const;

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_pound_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_star_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_del_clicked();

private:
    Ui::MainWindow *ui;
    MyAddressBookModel *myModel;
};

#endif // MAINWINDOW_H
