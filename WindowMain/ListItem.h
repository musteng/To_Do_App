//
// Created by Mustafa Çevik on 1.07.2022.
//

#ifndef TO_DO_APP_LISTITEM_H
#define TO_DO_APP_LISTITEM_H

#include <QString>
#include <QListWidgetItem>

struct ListItem {
public:
    ListItem();
    ~ListItem();

public:
    unsigned int itemId;
    QString userInput;
    QString endDate;
    QString importance;
};


#endif //TO_DO_APP_LISTITEM_H
