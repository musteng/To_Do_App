//
// Created by Mustafa Çevik on 26.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , windowTitle("To Do List")
    , windowWidth(500)
    , windowHeight(600)
    , minWindowWidth(400)
    , minWindowHeight(300)
    , maxWindowWidth(500)
    , maxWindowHeight(700)
    , font("Geneva")
    , fontSize(12)
{
    ui->setupUi(this);
    this->setWindowTitle(windowTitle);
    this->resize(windowWidth, windowHeight);
    this->setMaximumSize(maxWindowWidth, maxWindowHeight);
    this->setMinimumSize(minWindowWidth, minWindowHeight);
    this->taskList = new TaskList(this);
    font.setPointSize(fontSize);

    addButton = new QPushButton("Add", this);
    addButton->setFont(font);
    addButton->setGeometry(QRect(QPoint(windowWidth - 475, 5), QSize(60, 40)));
    addButton->setStyleSheet("QPushButton:hover { color: white }");
    connect(addButton, &QPushButton::released, taskList, &TaskList::handleAddButton);

    deleteButton = new QPushButton("Remove", this);
    deleteButton->setFont(font);
    deleteButton->setGeometry(QRect(QPoint(windowWidth - 220, 5), QSize(60, 40)));
    deleteButton->setStyleSheet("QPushButton:hover { color: white }");
    connect(deleteButton, &QPushButton::released, taskList, &TaskList::handleDeleteButton);

    updateButton = new QPushButton("Update", this);
    updateButton->setFont(font);
    updateButton->setGeometry(QRect(QPoint(windowWidth - 85, 5), QSize(60, 40)));
    updateButton->setStyleSheet("QPushButton:hover { color: white }");
    connect(updateButton, &QPushButton::released, taskList, &TaskList::handleUpdateButton);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {

    deleteButton->setGeometry(QRect(QPoint((this->taskList->width() - 180)/2 + 85, 5),
                                    QSize(60, 40)));

    updateButton->setGeometry(QRect(QPoint(this->width() - 85, 5),
                                    QSize(60, 40)));

    this->taskList->resize(this->width() - 50, this->height() - 75);

}



