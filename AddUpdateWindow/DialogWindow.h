//
// Created by Mustafa Çevik on 1.07.2022.
//

#ifndef TO_DO_APP_DIALOGWINDOW_H
#define TO_DO_APP_DIALOGWINDOW_H

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include "../ApplicationWindow/ListItem.h"


class DialogWindow : public QDialog {
Q_OBJECT

public:
    explicit DialogWindow(const QString& title);
    ~DialogWindow() override;

public:
    QFormLayout form;
    QLineEdit inputText;
    QDateEdit endingTime;
    QComboBox priorityLevel;
    QDialogButtonBox* buttonBox;

    QLabel labelText;
    QLabel labelDate;
    QLabel labelImportance;
};


#endif //TO_DO_APP_DIALOGWINDOW_H
