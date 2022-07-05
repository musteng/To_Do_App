//
// Created by Mustafa Çevik on 5.07.2022.
//

#ifndef TO_DO_APP_FILECONTROLLER_H
#define TO_DO_APP_FILECONTROLLER_H

#include <QFile>
#include <QTextStream>
#include <vector>
#include "../mainWindowItems/ListItem.h"


class FileController {
public:
    static void fileRead(std::vector<ListItem*>& itemVector);
    static void fileWrite(std::vector<ListItem*>& itemVector);
};


#endif //TO_DO_APP_FILECONTROLLER_H
