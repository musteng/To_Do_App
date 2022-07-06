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
                            "QListWidget::item:alternate { background-color: #bfffbf; }"
                            "QListWidget::item { background-color: #deffde; }"
                            "QListWidget {background-color : black};"
                            "QListWidget::item { width: 100; }"
                            "QListView::item { selection-color: white }"
                            "QListView::item { selection-background-color: #3344de}"
                            "QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                                "stop: 0 #414fd1, stop: 1 #414fd1)}");
    FileController::fileRead(listItemVector);
    itemVectorToList(listItemVector);
}

TaskList::~TaskList() {
    delete ui;
}

void TaskList::handleAddButton() {
    dialogWindow = new DialogWindow(QString("Add Task"));
    if( dialogWindow->exec() == QDialog::Accepted ) {
        item = new ListItem;
        unsigned int uniqueTime = QDateTime::currentSecsSinceEpoch();
        this->addItem(addItemToList(dialogWindow));
        addItemToVector(item,
                        uniqueTime,
                        dialogWindow->inputText->text(),
                        dialogWindow->endingTime->text(),
                        dialogWindow->priorityLevel->currentText());

        FileController::fileWrite(listItemVector);
    }
}


void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        listItemVector.erase(listItemVector.begin() + selectedIndex);
        this->takeItem(selectedIndex);
        this->clearSelection();
        FileController::fileWrite(listItemVector);
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
        dialogWindow->endingTime->setDate( QDate(dateValues[2].toInt(&ok, 10),
                                                    dateValues[1].toInt(&ok, 10),
                                                    dateValues[0].toInt(&ok, 10)));
        dialogWindow->priorityLevel->setCurrentText(selectedItem->importance);

        if (dialogWindow->exec() == QDialog::Accepted){
            updateVectorItem(listItemVector, selectedRowNo);
            this->takeItem(selectedRowNo);
            this->insertItem(selectedRowNo,addItemToList(dialogWindow));
            this->clearSelection();
            FileController::fileWrite(listItemVector);
        }
    }
}


void TaskList::mouseDoubleClickEvent(QMouseEvent *event) {
    this->clearSelection();
    //TODO one click
}


void TaskList::itemVectorToList(std::vector<ListItem*>& itemVector){
    QString userInputText;
    QString userInputDate;
    QString userInputPriority;
    QString userInput;

    for(ListItem* element : itemVector){
        userInputText = element->userInput;
        userInputDate = element->endDate;
        userInputPriority = element->importance ;
        userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
        this->addItem(userInput);
    }
}


void TaskList::addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel) {
    addedItem->itemId = id;
    addedItem->userInput = std::move(userInput);
    addedItem->endDate = endingTime;
    addedItem->importance = priorityLevel;
    listItemVector.push_back(addedItem);
}


QString TaskList::addItemToList(DialogWindow* windowValues) {
    QString userInputText = windowValues->inputText->text();
    QString userInputDate = windowValues->endingTime->text();
    QString userInputPriority = windowValues->priorityLevel->currentText();
    QString addedTask = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
    return addedTask;
}


void TaskList::updateVectorItem(std::vector<ListItem*>& itemVector, int selectedRow) {
    itemVector[selectedRow]->userInput = dialogWindow->inputText->text();
    itemVector[selectedRow]->endDate = dialogWindow->endingTime->text();
    itemVector[selectedRow]->importance = dialogWindow->priorityLevel->currentText();
}
