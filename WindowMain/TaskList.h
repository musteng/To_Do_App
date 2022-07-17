//
// Created by Mustafa Çevik on 27.06.2022.
//

#ifndef TO_DO_APP_TASKLIST_H
#define TO_DO_APP_TASKLIST_H

#include <QListWidget>
#include <QColor>
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


QT_BEGIN_NAMESPACE
namespace Ui { class TaskList; }
QT_END_NAMESPACE

class TaskList : public QListWidget {
Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList() override;

public:
    void handleAddButton();
    void handleDeleteButton();
    void handleUpdateButton();
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void itemVectorToList(std::vector<ListItem*>& listItemVector); // Used to read from file and transfer items to list
    static QString addItemToList(DialogWindow* windowValues);
    void addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel);
    void updateVectorItem(std::vector<ListItem*>& itemVector, int selectedRow);
    void databaseToList(std::vector<DatabaseItem*>& dbItemList);

    std::vector<ListItem*> listItemVector;

private:
    int positionX;
    int positionY;
    int windowWidth;
    int windowHeight;
    int fontSize;
    QFont font;

private:
    Ui::TaskList *ui;
    ListItem* item;
    DialogWindow* dialogWindow;
    DatabaseHandler* dbItem;
    std::vector<DatabaseItem*> dbData;
};


#endif //TO_DO_APP_TASKLIST_H
