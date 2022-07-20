//
// Created by Mustafa Çevik on 27.06.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TaskList.h" resolved

#include "TaskList.h"


TaskList::TaskList(QWidget *parent)
    : QListWidget(parent)
    , positionX(25)
    , positionY(50)
    , windowWidth(450)
    , windowHeight(525)
    , font("Geneva")
    , fontSize(14)
{
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
    dbData = databaseHandler.getData();
    this->databaseToList(dbData);
}


TaskList::~TaskList() = default;


void TaskList::handleAddButton() {
    DialogWindow dialogWindow("Add Task");

    if( dialogWindow.exec() == QDialog::Accepted ) {
        databaseHandler.listItemDB = new DatabaseItem();
        databaseHandler.listItemDB->userInput = dialogWindow.inputText.text();
        databaseHandler.listItemDB->endingDate = dialogWindow.endingTime.text();
        databaseHandler.listItemDB->priorityLevel = dialogWindow.priorityLevel.currentText();
        databaseHandler.postData();
        this->addItem(databaseHandler.getSingleData(databaseHandler.listItemDB->dbID));

        item = new ListItem;
        unsigned int uniqueTime = QDateTime::currentSecsSinceEpoch();
        addItemToVector(item,
                        uniqueTime,
                        dialogWindow.inputText.text(),
                        dialogWindow.endingTime.text(),
                        dialogWindow.priorityLevel.currentText());
        FileController::fileWrite(listItemVector);
        this->clearSelection();
    }
}


void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        delete listItemVector[selectedIndex];
        listItemVector[selectedIndex] = nullptr;

        listItemVector.erase(listItemVector.begin() + selectedIndex);
        this->takeItem(selectedIndex);
        this->clearSelection();

        databaseHandler.deleteData(selectedIndex);
        FileController::fileWrite(listItemVector);
    }
}


void TaskList::handleUpdateButton() {
    DialogWindow dialogWindow("Update Task");
    bool ok;
    int selectedRowNo = this->currentRow();
    ListItem* selectedItem;
    DatabaseItem* selectedItemDBVector;

    if( selectedRowNo != -1) {
        selectedItem = listItemVector[selectedRowNo];
        selectedItemDBVector = databaseHandler.listItemVectorDB[selectedRowNo];

        dialogWindow.inputText.setText(selectedItemDBVector->userInput);
        QStringList dateValues = selectedItemDBVector->endingDate.split('.');
        dialogWindow.endingTime.setDate( QDate(dateValues[2].toInt(&ok, 10),
                                                    dateValues[1].toInt(&ok, 10),
                                                    dateValues[0].toInt(&ok, 10)));
        dialogWindow.priorityLevel.setCurrentText(selectedItemDBVector->priorityLevel);

        if (dialogWindow.exec() == QDialog::Accepted){
            databaseHandler.listItemDB = new DatabaseItem();
            databaseHandler.listItemDB->userInput = dialogWindow.inputText.text();
            databaseHandler.listItemDB->endingDate = dialogWindow.endingTime.text();
            databaseHandler.listItemDB->priorityLevel = dialogWindow.priorityLevel.currentText();
            databaseHandler.updateData(selectedRowNo);

            TaskList::updateVectorItem(listItemVector, selectedRowNo, dialogWindow);
            this->insertItem(selectedRowNo, this->databaseHandler.getSingleData(selectedItemDBVector->dbID));
            this->takeItem(selectedRowNo + 1);
            this->clearSelection();
            FileController::fileWrite(listItemVector);
        }
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
    addedItem->endDate = std::move(endingTime);
    addedItem->importance = std::move(priorityLevel);
    listItemVector.push_back(addedItem);
}


void TaskList::updateVectorItem(const std::vector<ListItem*>& itemVector, int selectedRow,const DialogWindow& dialogWindow) {
    itemVector[selectedRow]->userInput = dialogWindow.inputText.text();
    itemVector[selectedRow]->endDate = dialogWindow.endingTime.text();
    itemVector[selectedRow]->importance = dialogWindow.priorityLevel.currentText();
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
