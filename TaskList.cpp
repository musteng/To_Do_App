//
// Created by Mustafa Çevik on 27.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TaskList.h" resolved

#include "TaskList.h"
#include "ui_TaskList.h"


TaskList::TaskList(QWidget *parent)
    : QListWidget(parent)
    , ui(new Ui::TaskList)
    , positionX(25)
    , positionY(50)
    , windowWidth(450)
    , windowHeight(525)
    , font("Geneva")
    , fontSize(14)
{
    ui->setupUi(this);
    this->setGeometry(QRect(QPoint(positionX, positionY),QSize(windowWidth, windowHeight)));
    this->setAlternatingRowColors(true);
    font.setPointSize(fontSize);
    font.setWeight(QFont::Weight::Light);
    font.setLetterSpacing(QFont::SpacingType::AbsoluteSpacing,static_cast<qreal>(1));
    this->setFont(font);
    this->setStyleSheet("QListWidget::item { height: 75px; }"
                            "QListWidget::item { width: 100; }"
                            "QListView::item { selection-color: white }"
                            "QListView::item { selection-background-color: #3344de}"
                            "QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                                "stop: 0 #414fd1, stop: 1 #414fd1)}");
    file.setFileName("/Users/mustafacevik/Desktop/savedItemsTry.txt");
    this->fileRead();
}

TaskList::~TaskList() {
    delete ui;
}

void TaskList::handleAddButton() {
    dialogWindow = new DialogWindow(QString("Add Task"));

    if( dialogWindow->exec() == QDialog::Accepted ) {
        item = new ListItem;
        unsigned int uniqueTime = QDateTime::currentSecsSinceEpoch();

        QString userInputText = dialogWindow->inputText->text();
        QString userInputDate = dialogWindow->endingTime->text();
        QString userInputPriority = dialogWindow->priorityLevel->currentText();

        QString userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
        this->addItem(userInput);

        item->itemId = uniqueTime;
        item->userInput = dialogWindow->inputText->text();
        item->endDate = dialogWindow->endingTime->text();
        item->importance = dialogWindow->priorityLevel->currentText();
        listItemVector.push_back(item);
    }
}


void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        listItemVector.erase(listItemVector.begin() + selectedIndex);
        this->takeItem(selectedIndex);
        this->clearSelection();
    }
}


void TaskList::handleUpdateButton() {
    bool ok;
    int selectedRowNo = this->currentRow();
    ListItem* selectedItem;

    if( selectedRowNo != -1) {
        dialogWindow = new DialogWindow(QString("Update Task"));
        selectedItem = listItemVector[selectedRowNo];

        dialogWindow->inputText->setText(selectedItem->userInput);
        QStringList dateValues = selectedItem->endDate.split('.');
        dialogWindow->endingTime->setDate( QDate(dateValues[2].toInt(&ok, 10),dateValues[1].toInt(&ok, 10),dateValues[0].toInt(&ok, 10)));
        dialogWindow->priorityLevel->setCurrentText(selectedItem->importance);

        if (dialogWindow->exec() == QDialog::Accepted){
            QString userInputText = dialogWindow->inputText->text();
            QString userInputDate = dialogWindow->endingTime->text();
            QString userInputPriority = dialogWindow->priorityLevel->currentText();
            QString userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;

            listItemVector[selectedRowNo]->userInput = dialogWindow->inputText->text();
            listItemVector[selectedRowNo]->endDate = dialogWindow->endingTime->text();
            listItemVector[selectedRowNo]->importance = dialogWindow->priorityLevel->currentText();

            this->takeItem(selectedRowNo);
            this->insertItem(selectedRowNo,userInput);
            this->clearSelection();
        }
    }
}


void TaskList::mouseDoubleClickEvent(QMouseEvent *event) {
    this->clearSelection();
    //TODO one click
}


void TaskList::fileWrite() {
    file.open(QIODeviceBase::ReadWrite);
    QTextStream out(&file);
    file.resize(0);

    for (auto & i : listItemVector){
        out << i->itemId << ", " << i->userInput << ", " << i->endDate << ", " << i->importance << "\n";
    }
    file.close();
}


void TaskList::fileRead() {
    file.open(QIODeviceBase::ReadWrite);
    QString line;
    QStringList lineValues;

    while(!file.atEnd()){
        item = new ListItem;
        line = file.readLine();
        if(line == "\n")
            continue;
        lineValues = line.split(", ");
        item->itemId = lineValues[0].toUInt();
        item->userInput = lineValues[1];
        item->endDate = lineValues[2];
        item->importance = lineValues[3];
        listItemVector.push_back(item);

        QString userInputText = item->userInput;
        QString userInputDate = item->endDate;
        QString userInputPriority = item->importance;

        QString userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
        this->addItem(userInput);
    }
    file.close();
}