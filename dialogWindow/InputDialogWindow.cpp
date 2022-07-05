//
// Created by Mustafa Çevik on 27.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InputDialogWindow.h" resolved

#include "InputDialogWindow.h"
#include "ui_InputDialogWindow.h"


InputDialogWindow::InputDialogWindow(QWidget *parent)
    : QInputDialog(parent)
    , ui(new Ui::InputDialogWindow)
{
    ui->setupUi(this);
    this->setLabelText("Add Task to List");
    this->setWindowTitle("Add Task");
    this->setOkButtonText("Add");
    this->setCancelButtonText("Cancel");
    this->setAutoFillBackground(true);
}

InputDialogWindow::~InputDialogWindow() {
    delete ui;
}

