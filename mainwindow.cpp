#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>



QString formatPhoneNumber(const QString& str){
    QString retVal, temp;

    // clear dashes
    for(int i = 0; i < str.size(); i++) {
        if(str.at(i).isDigit()) temp += str.at(i);
      }


    if(temp.size() > 10){
        std::cerr << "ERROR: String size too big";
        return str;
    }

    //add dashes
    for(int i = 0; i < temp.size(); i++){
        if(i > 0 && i%3 == 0 && i < 9) {
            retVal = retVal + "-";}
        retVal = retVal + temp.at(i);
    }

    return retVal;
}

// method handle all neccessarily model updates
void MainWindow::dial(const QString& str) const{
    QString nameSearch;
    ui->pushButton_del->setHidden(false); //delete btn

    if(ui->label_name->text().size() > 0){
        ui->label_name->clear();
        ui->label->clear();
    }

    if(ui->label->text().size() > 11) return;


    for(int i = 0; i < str.size(); i++) {
        if(!str.at(i).isDigit() && str.at(i).isLetter()) nameSearch += str.at(i);
      }

    ui->label->setText(formatPhoneNumber(ui->label->text() + str));
    std::cout << " search string " << str.toStdString() << std::endl;
//    myModel->setFilterString(ui->label->text()); //filter by phone
    myModel->setFilterString(nameSearch, ui->label->text()); //filter by phone
//    myModel->setFilterString(ui->label->text()); //filter by phone
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    myModel(new MyAddressBookModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(myModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setColumnWidth(2, 150);

    ui->pushButton_call->setIcon(QIcon("call_icon.png"));
    ui->pushButton_call->setIconSize(QSize(65, 65));

    ui->pushButton_del->setHidden(true); //delete btn

    on_actionOpen_an_Address_Book_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_an_Address_Book_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.csv);;All Files (*)"));

//    QString fileName = "/Users/tannerphan/Downloads/us-500.csv";
    std::cout << fileName.toStdString() << std::endl;


    myModel->openFile(fileName);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButton_del->setHidden(false); //delete btn
    std::cout << index.row() << "," << index.column() << std::endl;
    ui->label->setText(formatPhoneNumber(myModel->getPhoneNumber(index.row())));
    ui->label_name->setText(myModel->getName(index.row()));
}

void MainWindow::on_pushButton_1_clicked()
{
  dial("1");
}

void MainWindow::on_pushButton_2_clicked()
{
    dial("2ABC");
}

void MainWindow::on_pushButton_pound_clicked()
{

}

void MainWindow::on_pushButton_0_clicked()
{
    dial("0");
}

void MainWindow::on_pushButton_star_clicked()
{

}

void MainWindow::on_pushButton_9_clicked()
{
    dial("9WXYZ");
}

void MainWindow::on_pushButton_8_clicked()
{
    dial("8TUV");
}

void MainWindow::on_pushButton_7_clicked()
{
    dial("7PQRS");
}

void MainWindow::on_pushButton_6_clicked()
{
    dial("6MNO");
}

void MainWindow::on_pushButton_5_clicked()
{
    dial("5JKL");
}

void MainWindow::on_pushButton_4_clicked()
{
    dial("4GHI");
}

void MainWindow::on_pushButton_3_clicked()
{
    dial("3DEF");
}

void MainWindow::on_pushButton_del_clicked()
{
    ui->label->clear();
    ui->label_name->clear();
    ui->pushButton_del->setHidden(true);

    myModel->clearFilter();
}
