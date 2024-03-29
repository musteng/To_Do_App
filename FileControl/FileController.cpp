//
// Created by Mustafa Çevik on 5.07.2022.
//

#include "FileController.h"


void FileController::fileRead(std::vector<ListItem*>& itemVector) {
    QString homeDir = std::getenv("HOME");
    QString fileName = homeDir + "/Desktop/savedItemsTry.txt";

    QFile file;
    file.setFileName(fileName);
    file.open(QIODeviceBase::ReadWrite);
    QString line;
    QStringList lineValues;

    ListItem* item1;
    while(!file.atEnd()){
        item1 = new ListItem;
        line = file.readLine();
        if(line == "\n")
            continue;
        lineValues = line.split(", ");
        item1->itemId = lineValues[0].toUInt();
        item1->userInput = lineValues[1];
        item1->endDate = lineValues[2];
        item1->importance = lineValues[3];
        itemVector.push_back(item1);
    }
    file.close();
}


void FileController::fileWrite(const std::vector<ListItem*>& itemVector) {
    QString homeDir = std::getenv("HOME");
    QString fileName = homeDir + "/Desktop/savedItemsTry.txt";

    QFile file;
    file.setFileName(fileName);
    file.open(QIODeviceBase::ReadWrite);
    QTextStream out(&file);
    file.resize(0);

    for (ListItem* i : itemVector){
        out << i->itemId << ", " << i->userInput << ", " << i->endDate << ", " << i->importance << Qt::endl;
    }
    file.close();
}
