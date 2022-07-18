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
#include "../WindowMain/ListItem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DialogWindow; }
QT_END_NAMESPACE

class DialogWindow : public QDialog {
Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    explicit DialogWindow(QString title);
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
