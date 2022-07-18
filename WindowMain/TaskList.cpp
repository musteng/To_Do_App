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
                        "QListWidget::item { background-color: #00ffde; }"
                        "QListWidget::item:alternate { background-color: #248a7c; }"
                        "QListWidget {background-color : black};"
                        "QListWidget::item { width: 100; }"
                        "QListView::item { selection-color: white }"
                        "QListView::item { selection-background-color: #3344de}"
                        "QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                                "stop: 0 #00ffde, stop: 1 #414fd1)}");
    FileController::fileRead(listItemVector);
    //itemVectorToList(listItemVector); // used to read from file to app list
    dbItem = new DatabaseHandler();
    dbData = dbItem->getData();
    this->databaseToList(dbData);
}


TaskList::~TaskList() {
    delete ui;
}


void TaskList::handleAddButton() {
    dialogWindow = new DialogWindow(QString("Add Task"));
    if( dialogWindow->exec() == QDialog::Accepted ) {
        this->addItem(addItemToList(dialogWindow));

        item = new ListItem;
        unsigned int uniqueTime = QDateTime::currentSecsSinceEpoch();
        addItemToVector(item,
                        uniqueTime,
                        dialogWindow->inputText.text(),
                        dialogWindow->endingTime.text(),
                        dialogWindow->priorityLevel.currentText());
        FileController::fileWrite(listItemVector);

        dbItem->listItemDB = new DatabaseItem();
        dbItem->listItemDB->userInput = dialogWindow->inputText.text();
        dbItem->listItemDB->endingDate = dialogWindow->endingTime.text();
        dbItem->listItemDB->priorityLevel = dialogWindow->priorityLevel.currentText();
        dbItem->postData();
        this->clearSelection();
    }
    delete dialogWindow;
}


void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        delete listItemVector[selectedIndex];
        listItemVector[selectedIndex] = nullptr;

        listItemVector.erase(listItemVector.begin() + selectedIndex);
        this->takeItem(selectedIndex);
        this->clearSelection();

        FileController::fileWrite(listItemVector);
        dbItem->deleteData(selectedIndex);
    }
}


void TaskList::handleUpdateButton() {
    bool ok;
    int selectedRowNo = this->currentRow();
    ListItem* selectedItem;
    DatabaseItem* selectedItemDBVector;

    if( selectedRowNo != -1) {
        dialogWindow = new DialogWindow(QString("Update Task"));
        selectedItem = listItemVector[selectedRowNo];
        selectedItemDBVector = dbItem->listItemVectorDB[selectedRowNo];

        dialogWindow->inputText.setText(selectedItemDBVector->userInput);
        QStringList dateValues = selectedItemDBVector->endingDate.split('.');
        dialogWindow->endingTime.setDate( QDate(dateValues[2].toInt(&ok, 10),
                                                    dateValues[1].toInt(&ok, 10),
                                                    dateValues[0].toInt(&ok, 10)));
        dialogWindow->priorityLevel.setCurrentText(selectedItemDBVector->priorityLevel);

        if (dialogWindow->exec() == QDialog::Accepted){
            updateVectorItem(listItemVector, selectedRowNo);
            this->takeItem(selectedRowNo);
            this->insertItem(selectedRowNo,addItemToList(dialogWindow));
            this->clearSelection();
            FileController::fileWrite(listItemVector);

            dbItem->listItemDB = new DatabaseItem();
            dbItem->listItemDB->userInput = dialogWindow->inputText.text();
            dbItem->listItemDB->endingDate = dialogWindow->endingTime.text();
            dbItem->listItemDB->priorityLevel = dialogWindow->priorityLevel.currentText();
            dbItem->updateData(selectedRowNo);
        }
        delete dialogWindow;
    }
}


void TaskList::mouseDoubleClickEvent(QMouseEvent *event) {
    this->clearSelection();
    //TODO one click
}


void TaskList::itemVectorToList(const std::vector<ListItem*>& itemVector){
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


QString TaskList::addItemToList(const DialogWindow* windowValues) {
    QString userInputText = windowValues->inputText.text();
    QString userInputDate = windowValues->endingTime.text();
    QString userInputPriority = windowValues->priorityLevel.currentText();
    QString addedTask = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
    return addedTask;
}


void TaskList::updateVectorItem(const std::vector<ListItem*>& itemVector, int selectedRow) {
    itemVector[selectedRow]->userInput = dialogWindow->inputText.text();
    itemVector[selectedRow]->endDate = dialogWindow->endingTime.text();
    itemVector[selectedRow]->importance = dialogWindow->priorityLevel.currentText();
}


void TaskList::databaseToList(const std::vector<DatabaseItem*>& dbItemList) {
    QString userInputText;
    QString userInputDate;
    QString userInputPriority;
    QString userInput;

    for(DatabaseItem* itemInVector : dbItemList){
        userInputText = itemInVector->userInput;
        userInputDate = itemInVector->endingDate;
        userInputPriority = itemInVector->priorityLevel;
        userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
        this->addItem(userInput);
    }
}
