#include "myaddressbookmodel.h"

#include <regex>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

MyAddressBookModel::MyAddressBookModel(QObject *parent)
    :QAbstractTableModel (parent)
{

}

int MyAddressBookModel::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}

int MyAddressBookModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MyAddressBookModel::data(const QModelIndex &index, int role) const
{
    //    std::cout << index.row() << " first Names size: " << firstNames.size()
    //              << " last Names size: " << lastNames.size() << " phone number size: " << phoneNumbers.size()
    //              << std::endl;

    if (role == Qt::DisplayRole && index.row() < filteredIndex.size()) {
        switch(index.column()) {
        case 0: // firstname
            return firstNames.at(filteredIndex.at(index.row()));
        case 1:
            return lastNames.at(filteredIndex.at(index.row()));
        case 2:
            return phoneNumbers.at(filteredIndex.at(index.row()));
        }
        //        return QString("Row%1, Column%2")
        //                .arg(index.row())
        //                .arg(index.column());
    }

    return QVariant();
}

void MyAddressBookModel::openFile(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QTextStream in(&file);

    firstNames.clear();
    lastNames.clear();
    phoneNumbers.clear();

    for(int i = 0; !in.atEnd(); i++) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (i == 0) continue;

        for(int j = 0; j < fields.length(); j++) {
            std::cout << "[" << j << "]" << fields[j].toStdString();
        }
        std::cout << std::endl;

        firstNames.push_back(fields[0]);
        lastNames.push_back(fields[1]);
        phoneNumbers.push_back(fields[7]);

        filteredIndex.push_back(i-1);
    }

    file.close();

    emit layoutChanged();
}

QString MyAddressBookModel::getPhoneNumber(int index)
{
    return phoneNumbers.at(filteredIndex[index]);
}

QString MyAddressBookModel::getName(int index)
{
    return firstNames.at(filteredIndex[index]) + " " + lastNames.at(filteredIndex[index]);
}

void MyAddressBookModel::setFilterString(QString fStr, QString phoneNum)
{
    std::vector<int> tempDict;
    if(filteredIndex.size() == 0){
        for(int i = 0; i < phoneNumbers.size(); i ++){
            tempDict.push_back(i);
        }
    }else{
        for(int i = 0; i < filteredIndex.size(); i++){
            tempDict.push_back(filteredIndex.at(i));
        }
    }

    filteredIndex.clear();

//    std::set<int> retValSet;
    for(int i = 0; i < tempDict.size(); i++){
        int ndx = tempDict[i];
        std::cout << "search phone " << phoneNum.toInt() << std::endl;
        std::cout << "ndx " << ndx << std::endl;
        std::cout << "phone " << phoneNumbers.at(ndx).toInt() << std::endl;
        if (phoneNumbers[ndx].startsWith(phoneNum)) {
            filteredIndex.push_back(ndx);
        }else{
            QString fname = firstNames[ndx], lname = lastNames[ndx];
            std::cout << "search term " << fStr.toStdString() << std::endl;
            for(int j = 0; j < fStr.size(); j++){
                int numDigits = phoneNum.length();
                if(fname.length() >= numDigits && fname.at(numDigits -1).toUpper() == fStr[j]){
                    filteredIndex.push_back(ndx);
                    break;
                }
                if(lname.length() >= numDigits && lname.at(numDigits -1).toUpper() == fStr[j]){
                    filteredIndex.push_back(ndx);
                    break;
                }
            }
        }
    }

//    for (std::set<int>::iterator it=retValSet.begin(); it!=retValSet.end(); ++it)
//        filteredIndex.push_back(*it);

    emit layoutChanged();
}


void MyAddressBookModel::clearFilter(){
    filteredIndex.clear();

    for(int i = 0; i < phoneNumbers.size(); i++) filteredIndex.push_back(i);
    emit layoutChanged();
}








