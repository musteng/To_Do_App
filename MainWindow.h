//
// Created by Mustafa Çevik on 26.06.2022.
//

#ifndef TO_DO_APP_MAINWINDOW_H
#define TO_DO_APP_MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <iostream>
#include "InputDialogWindow.h"
#include <QDebug>
#include "TaskList.h"
#include "ListItem.h"
#include <QListWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;
    QString windowTitle;
    int windowWidth;
    int windowHeight;
    int minWindowWidth;
    int minWindowHeight;
    int maxWindowWidth;
    int maxWindowHeight;

private:
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    TaskList* taskList;
    QFont font;
    int fontSize;
};


#endif //TO_DO_APP_MAINWINDOW_H
