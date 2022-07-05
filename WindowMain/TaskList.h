//
// Created by Mustafa Çevik on 27.06.2022.
//

#ifndef TO_DO_APP_TASKLIST_H
#define TO_DO_APP_TASKLIST_H

#include <QListWidget>
#include <QPalette>
#include <QColor>
#include <QPushButton>
#include "../WindowDialog/InputDialogWindow.h"
#include <QSettings>
#include <QDateTime>
#include "ListItem.h"
#include "../WindowDialog/DialogWindow.h"
#include <vector>
#include <QFile>
#include <QTextFormat>
#include "../FileControl/FileController.h"
#include <utility>

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
    void itemVectorToList(std::vector<ListItem*>& listItemVector);
    static QString addItemToList(DialogWindow* windowValues);
    void addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel);
    void updateVectorItem(std::vector<ListItem*>& itemVector, int selectedRow);

    std::vector<ListItem*> listItemVector;

private:
    Ui::TaskList *ui;

private:
    int positionX;
    int positionY;
    int windowWidth;
    int windowHeight;
    int fontSize;

    QFont font;
    ListItem* item;
    DialogWindow* dialogWindow;
};


#endif //TO_DO_APP_TASKLIST_H
