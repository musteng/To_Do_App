//
// Created by Mustafa Çevik on 26.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , windowTitle("To Do List")
    , windowWidth(500)
    , windowHeight(600)
    , minWindowWidth(400)
    , minWindowHeight(300)
    , maxWindowWidth(500)
    , maxWindowHeight(700)
    , font("Geneva")
    , fontSize(12)
    , addButton("Add", this)
    , deleteButton("Remove", this)
    , updateButton("Update", this)
    , taskList(this)
{
    this->setStyleSheet("MainWindow {background-color : #49494d};");
    this->setWindowTitle(windowTitle);
    this->resize(windowWidth, windowHeight);
    this->setMaximumSize(maxWindowWidth, maxWindowHeight);
    this->setMinimumSize(minWindowWidth, minWindowHeight);
    this->font.setPointSize(fontSize);

    addButton.setFont(font);
    addButton.setGeometry(QRect(QPoint(windowWidth - 475, 5), QSize(60, 40)));
    addButton.setStyleSheet("QPushButton:hover { color: #49494d }");
    connect(&addButton, &QPushButton::released, &taskList, &TaskList::handleAddButton);

    deleteButton.setFont(font);
    deleteButton.setGeometry(QRect(QPoint(windowWidth - 220, 5), QSize(60, 40)));
    deleteButton.setStyleSheet("QPushButton:hover { color: #49494d }");
    connect(&deleteButton, &QPushButton::released, &taskList, &TaskList::handleDeleteButton);

    updateButton.setFont(font);
    updateButton.setGeometry(QRect(QPoint(windowWidth - 85, 5), QSize(60, 40)));
    updateButton.setStyleSheet("QPushButton:hover { color: #49494d }");
    connect(&updateButton, &QPushButton::released, &taskList, &TaskList::handleUpdateButton);
}


MainWindow::~MainWindow() {
}


void MainWindow::resizeEvent(QResizeEvent *event) {

    this->deleteButton.setGeometry(QRect(QPoint((this->taskList.width() - 180)/2 + 85, 5),
                                    QSize(60, 40)));

    this->updateButton.setGeometry(QRect(QPoint(this->width() - 85, 5),
                                    QSize(60, 40)));

    this->taskList.resize(this->width() - 50, this->height() - 75);

}
