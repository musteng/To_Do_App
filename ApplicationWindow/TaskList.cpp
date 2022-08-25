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

    this->databaseToList(databaseHandler.getDBKeys());

    //Uncomment when file read and write is used rather than database operation.
    //FileController::fileRead(listItemVector);
    //itemVectorToList(listItemVector);
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
        this->clearSelection();

        /*
        //These lines are used when file read and write is used.

        item = new ListItem;
        unsigned int uniqueTime = QDateTime::currentSecsSinceEpoch();
        addItemToVector(item,
                        uniqueTime,
                        dialogWindow.inputText.text(),
                        dialogWindow.endingTime.text(),
                        dialogWindow.priorityLevel.currentText());
        FileController::fileWrite(listItemVector);
         */
    }
}


void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        this->takeItem(selectedIndex);
        this->clearSelection();

        databaseHandler.deleteData(selectedIndex);

        /*
        //These lines are used when file read and write is used.

        delete listItemVector[selectedIndex];
        listItemVector[selectedIndex] = nullptr;

        listItemVector.erase(listItemVector.begin() + selectedIndex);
        FileController::fileWrite(listItemVector);

        */
    }
}


void TaskList::handleUpdateButton() {
    DialogWindow dialogWindow("Update Task");
    bool ok;
    int selectedRowNo = this->currentRow();
    // ListItem* selectedItem; // File write and read related.

    if( selectedRowNo != -1) {
        // selectedItem = listItemVector[selectedRowNo]; // File write and read related.

        QString key = databaseHandler.dbKeys[selectedRowNo];
        QUrl itemUrl = databaseHandler.dbUrl + key + ".json";
        QNetworkAccessManager networkAccessManager;
        QNetworkRequest getElementRequest = QNetworkRequest(itemUrl);
        QNetworkReply* networkReply = networkAccessManager.get(getElementRequest);
        QEventLoop eventLoop;
        connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec();

        QString userInputText;
        QString userInputDate;
        QString userInputPriority;
        if (!networkReply->error()){
            QByteArray itemData = networkReply->readAll();
            QJsonDocument itemDataJsonDocument = QJsonDocument::fromJson(itemData);
            QJsonObject itemDataJson = itemDataJsonDocument.object();

            userInputText = itemDataJson["userInput"].toString();
            userInputDate = itemDataJson["endDate"].toString();
            userInputPriority = itemDataJson["importance"].toString();
        }
        dialogWindow.inputText.setText(userInputText);
        QStringList dateValues = userInputDate.split('.');
        dialogWindow.endingTime.setDate( QDate(dateValues[2].toInt(&ok, 10),
                                               dateValues[1].toInt(&ok, 10),
                                               dateValues[0].toInt(&ok, 10)));
        dialogWindow.priorityLevel.setCurrentText(userInputPriority);

        if (dialogWindow.exec() == QDialog::Accepted){
            databaseHandler.listItemDB = new DatabaseItem();
            databaseHandler.listItemDB->userInput = dialogWindow.inputText.text();
            databaseHandler.listItemDB->endingDate = dialogWindow.endingTime.text();
            databaseHandler.listItemDB->priorityLevel = dialogWindow.priorityLevel.currentText();
            databaseHandler.updateData(selectedRowNo);

            this->insertItem(selectedRowNo, this->databaseHandler.getSingleData(key));
            this->takeItem(selectedRowNo + 1);
            this->clearSelection();

            //TaskList::updateVectorItem(listItemVector, selectedRowNo, dialogWindow);  // File write and read related.
            //FileController::fileWrite(listItemVector);  // File write and read related.
        }
    }
}


// This function is used to transfer items from database to application window at opening.
void TaskList::databaseToList(const std::vector<QString>& dbKeys) {
    QString userInputText;
    QString userInputDate;
    QString userInputPriority;
    QString userInput;

    for(const QString& key : dbKeys){
        QUrl itemUrl = databaseHandler.dbUrl + key + ".json";
        QNetworkAccessManager networkAccessManager;
        QNetworkRequest getElementRequest = QNetworkRequest(itemUrl);
        QNetworkReply* networkReply = networkAccessManager.get(getElementRequest);
        QEventLoop eventLoop;
        connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec();

        if (!networkReply->error()){
            QByteArray itemData = networkReply->readAll();
            QJsonDocument itemDataJsonDocument = QJsonDocument::fromJson(itemData);
            QJsonObject itemDataJson = itemDataJsonDocument.object();

            userInputText = itemDataJson["userInput"].toString();
            userInputDate = itemDataJson["endDate"].toString();
            userInputPriority = itemDataJson["importance"].toString();
            userInput = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
        }
        this->addItem(userInput);
        delete networkReply;
    }
}


void TaskList::mouseDoubleClickEvent(QMouseEvent *event) {
    this->clearSelection(); // Clear row when clicked twice.
}


/**
 * These below functions (itemVectorToList, addItemToVector, updateVectorItem) are used when file read and write is operational.
 */


/*
// This function is used to transfer tasks from file to application window.
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


// This function is used to append last added item to item vector.
void TaskList::addItemToVector(ListItem* addedItem, unsigned int id, QString userInput, QString endingTime, QString priorityLevel) {
    addedItem->itemId = id;
    addedItem->userInput = std::move(userInput);
    addedItem->endDate = std::move(endingTime);
    addedItem->importance = std::move(priorityLevel);
    listItemVector.push_back(addedItem);
}


// This function is used to update last updated item in the item vector.
void TaskList::updateVectorItem(const std::vector<ListItem*>& itemVector, int selectedRow,const DialogWindow& dialogWindow) {
    itemVector[selectedRow]->userInput = dialogWindow.inputText.text();
    itemVector[selectedRow]->endDate = dialogWindow.endingTime.text();
    itemVector[selectedRow]->importance = dialogWindow.priorityLevel.currentText();
}
*/
