//
// Created by Mustafa Çevik on 11.07.2022.
//

#ifndef TO_DO_APP_DATABASEITEM_H
#define TO_DO_APP_DATABASEITEM_H

#include <QString>

struct DatabaseItem {
    DatabaseItem();
    ~DatabaseItem();

    QString dbID;
    QString userInput;
    QString endingDate;
    QString priorityLevel;
};


#endif //TO_DO_APP_DATABASEITEM_H
