//
// Created by Mustafa Çevik on 1.07.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogWindow.h" resolved

#include "DialogWindow.h"
#include "ui_DialogWindow.h"


DialogWindow::DialogWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
}

DialogWindow::~DialogWindow() {
    delete ui;
}

DialogWindow::DialogWindow(QString title) {

    this->setWindowTitle(title);
    this->setModal(true);

    form = new QFormLayout;
    labelText = new QLabel(this);
    labelText->setFont(QFont("Geneva", 13, 1, false));
    labelText->setText("Task : ");

    inputText = new QLineEdit;
    inputText->setFont(QFont("Geneva", 13, 1, false));

    form->addRow(labelText, inputText);

    endingTime = new QDateEdit(this);
    endingTime->setDate(QDate::currentDate());
    endingTime->setTime(QTime::currentTime());
    endingTime->setCalendarPopup(true);
    endingTime->setMinimumDate(QDate::currentDate());
    endingTime->setFont(QFont("Geneva", 13, 1, false));
    endingTime->setDisplayFormat("dd.MM.yyyy");

    labelDate = new QLabel(this);
    labelDate->setText("Ending Date : ");
    labelDate->setFont(QFont("Geneva", 13, 1, false));

    form->addRow(labelDate, endingTime);

    priorityLevel = new QComboBox(this);
    priorityLevel->addItem("Trivial");
    priorityLevel->addItem("Low");
    priorityLevel->addItem("Medium");
    priorityLevel->addItem("High");
    priorityLevel->setFont(QFont("Geneva", 13, 1, false));

    labelImportance = new QLabel(this);
    labelImportance->setText("Priority : ");
    labelImportance->setFont(QFont("Geneva", 13, 1, false));

    form->addRow(labelImportance, priorityLevel);

    QDialogButtonBox* buttonBox;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Close);

    form->addRow(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    this->setLayout(form);
}