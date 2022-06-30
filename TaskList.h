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
    void loadTasks();
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Ui::TaskList *ui;

private:
    int positionX;
    int positionY;
    int windowWidth;
    int windowHeight;
    int fontSize;

    InputDialogWindow inputDialogWindow;
    QFont font;
    QSettings settings;
    QSettings valueSettings;

    QStringList keys;
    QListWidgetItem* insertedItem;
    QLineEdit::EchoMode echoMode;

    QString addPopUpTitle;
    QString addPopUpLabel;
    QString addPopUpInitialText;
    QString updatePupUpTitle;
    QString updatePupUpLabel;

    QDateTime time;
};


#endif //TO_DO_APP_TASKLIST_H
