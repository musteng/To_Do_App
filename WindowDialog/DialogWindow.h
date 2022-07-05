//
// Created by Mustafa Çevik on 1.07.2022.
//

#ifndef TO_DO_APP_DIALOGWINDOW_H
#define TO_DO_APP_DIALOGWINDOW_H

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
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
    Ui::DialogWindow *ui;
    QFormLayout* form;
    QLineEdit* inputText;
    QDateEdit* endingTime;
    QLabel* labelText;
    QLabel* labelDate;
    QComboBox* priorityLevel;
    QLabel* labelImportance;
};


#endif //TO_DO_APP_DIALOGWINDOW_H