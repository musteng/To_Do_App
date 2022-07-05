//
// Created by Mustafa Çevik on 5.07.2022.
//

#include "FileController.h"


void FileController::fileRead(std::vector<ListItem*>& itemVector) {
    ListItem* item1;
    QFile file;
    file.setFileName("/Users/mustafacevik/Desktop/savedItemsTry.txt");
    file.open(QIODeviceBase::ReadWrite);
    QString line;
    QStringList lineValues;

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


void FileController::fileWrite(std::vector<ListItem*>& itemVector) {
    QFile file;
    file.setFileName("/Users/mustafacevik/Desktop/savedItemsTry.txt");
    file.open(QIODeviceBase::ReadWrite);
    QTextStream out(&file);
    file.resize(0);

    for (ListItem* i : itemVector){
        out << i->itemId << ", " << i->userInput << ", " << i->endDate << ", " << i->importance << Qt::endl;
    }
    file.close();
}