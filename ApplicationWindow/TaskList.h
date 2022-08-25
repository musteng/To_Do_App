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
#include "../AddUpdateWindow/DialogWindow.h"
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
    void databaseToList(const std::vector<QString>& dbKeys);
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    int positionX;
    int positionY;
    int windowWidth;
    int windowHeight;
    int fontSize;
    QFont font;
    DatabaseHandler databaseHandler;

    /*
     * These functions and data structures are used to operate file writing and file reading related operations.
     * And only meaningful when file read and write are preferred rather than database usage.

public:
    void addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel);
    static void updateVectorItem(const std::vector<ListItem*>& itemVector, int selectedRow, const DialogWindow& dialogWindow);
    void itemVectorToList(const std::vector<ListItem*>& listItemVector);
    std::vector<ListItem*> listItemVector;

private:
    ListItem* item;
    std::vector<DatabaseItem*> dbData;

     */
};


#endif //TO_DO_APP_TASKLIST_H
