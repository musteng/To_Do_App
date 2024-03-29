//
// Created by Mustafa Çevik on 26.06.2022.
//

#ifndef TO_DO_APP_MAINWINDOW_H
#define TO_DO_APP_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QDialog>
#include "TaskList.h"
#include "ListItem.h"


class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QString windowTitle;
    int windowWidth;
    int windowHeight;
    int minWindowWidth;
    int minWindowHeight;
    int maxWindowWidth;
    int maxWindowHeight;
    QFont font;
    int fontSize;

private:
    QPushButton addButton;
    QPushButton deleteButton;
    QPushButton updateButton;
    TaskList taskList;
};


#endif //TO_DO_APP_MAINWINDOW_H
