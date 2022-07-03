//
// Created by Mustafa Çevik on 27.06.2022.
//

#ifndef TO_DO_APP_TASKLIST_H
#define TO_DO_APP_TASKLIST_H

#include <QListWidget>
#include <QPalette>
#include <QColor>
#include <QPushButton>
#include "InputDialogWindow.h"
#include <QSettings>
#include <QDateTime>
#include "ListItem.h"
#include "DialogWindow.h"
#include <vector>
#include <iostream>
#include <QFile>

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
    void fileWrite();
    void fileRead();

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
    QFile file;
    ListItem* item;
    DialogWindow* dialogWindow;
};


#endif //TO_DO_APP_TASKLIST_H
