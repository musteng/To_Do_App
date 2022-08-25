//
// Created by Mustafa Çevik on 1.07.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogWindow.h" resolved

#include "DialogWindow.h"


DialogWindow::DialogWindow(const QString& title)
    : form(this)
    , labelText(this)
    , inputText(this)
    , labelDate(this)
    , endingTime(this)
    , labelImportance(this)
    , priorityLevel(this)
{
    this->setWindowTitle(title);
    this->setModal(true);

    labelText.setFont(QFont("Geneva", 13, 1, false));
    labelText.setText("Task : ");
    inputText.setFont(QFont("Geneva", 13, 1, false));
    form.addRow(&labelText, &inputText);

    labelDate.setText("Ending Date : ");
    labelDate.setFont(QFont("Geneva", 13, 1, false));
    endingTime.setDate(QDate::currentDate());
    endingTime.setCalendarPopup(true);
    endingTime.setMinimumDate(QDate::currentDate());
    endingTime.setFont(QFont("Geneva", 13, 1, false));
    endingTime.setDisplayFormat("dd.MM.yyyy");
    form.addRow(&labelDate, &endingTime);

    labelImportance.setText("Priority : ");
    labelImportance.setFont(QFont("Geneva", 13, 1, false));
    priorityLevel.addItem("None");
    priorityLevel.addItem("Low");
    priorityLevel.addItem("Medium");
    priorityLevel.addItem("High");
    priorityLevel.setFont(QFont("Geneva", 13, 1, false));
    form.addRow(&labelImportance, &priorityLevel);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Close);
    form.addRow(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    this->setLayout(&form);
}


DialogWindow::~DialogWindow() {
    delete buttonBox;
}
