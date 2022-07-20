//
// Created by Mustafa Çevik on 27.06.2022.
//

#ifndef TO_DO_APP_TASKLIST_H
#define TO_DO_APP_TASKLIST_H

#include <QListWidget>
#include <QPushButton>
#include <QDateTime>
#include <QFile>
#include <QTextFormat>
#include <vector>
#include <utility>
#include "ListItem.h"
#include "../WindowDialog/DialogWindow.h"
#include "../FileControl/FileController.h"
#include "../DatabaseHandlerFiles/DatabaseItem.h"
#include "../DatabaseHandlerFiles/DatabaseHandler.h"


class TaskList : public QListWidget {
Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList() override;

public:
    void handleAddButton();
    void handleDeleteButton();
    void handleUpdateButton();
    void addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel);
    static void updateVectorItem(const std::vector<ListItem*>& itemVector, int selectedRow, const DialogWindow& dialogWindow);
    void databaseToList(const std::vector<DatabaseItem*>& dbItemList);
    void itemVectorToList(const std::vector<ListItem*>& listItemVector); // Used to read from file and transfer items to list
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    std::vector<ListItem*> listItemVector;

private:
    int positionX;
    int positionY;
    int windowWidth;
    int windowHeight;
    int fontSize;
    QFont font;

private:
    ListItem* item;
    DatabaseHandler databaseHandler;
    std::vector<DatabaseItem*> dbData;
};


#endif //TO_DO_APP_TASKLIST_H
