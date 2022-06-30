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
    , fontSize(15)
    , settings("To_Do_App", "To_Do_App") // settings("/Users/mustafacevik/Desktop/savedItems.txt", QSettings::Format::IniFormat)
    //, settings( "/Users/mustafacevik/Desktop/savedTasks", QSettings::Format::NativeFormat)
    , echoMode(QLineEdit::Normal)
    , addPopUpTitle("Add Task")
    , addPopUpLabel("Add a Task To List")
    , addPopUpInitialText("")
    , updatePupUpTitle("Update Task")
    , updatePupUpLabel("Update the Task")
    , valueSettings("To_Do_App", "To_Do_App_Values")
{
    ui->setupUi(this);
    this->setGeometry(QRect(QPoint(positionX, positionY),QSize(windowWidth, windowHeight)));
    this->setAlternatingRowColors(true);
    font.setPointSize(fontSize);
    font.setLetterSpacing(QFont::SpacingType::AbsoluteSpacing,static_cast<qreal>(1));
    this->setFont(font);
    this->setStyleSheet("QListWidget::item { height: 35px; }"
                            "QListView::item { selection-color: white }"
                            "QListView::item { selection-background-color: #3344de}"
                            "QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                                "stop: 0 #535c75, stop: 1 #414fd1)}");

    settings.beginGroup("myKeys");
    keys = settings.childKeys();
    loadTasks();
    //settings.clear();
    //settings.setPath(QSettings::Format::NativeFormat, QSettings::Scope::SystemScope, "/Users/mustafacevik/Desktop/savedTasks");
    //this->setStyleSheet("QListView
    // { selection-color: white }");
    // settings.setPath(QSettings::Format::NativeFormat, QSettings::Scope::UserScope, "/Users/mustafacevik/Desktop/savedTasks");
    //this->setStyleSheet( "QListWidget{ background: black;}");
    //this->addItem(items.value("1").toString());
}

TaskList::~TaskList() {
    delete ui;
}

void TaskList::handleAddButton() {
    int row = this->count();
    unsigned int uniqueTime = time.currentSecsSinceEpoch();
    QString rowStr2 = QString::number(uniqueTime);
    QString rowStr = QString::number(row);
    bool okClicked;
    QString userInput = inputDialogWindow.getText(this, addPopUpTitle, addPopUpLabel,
                                                  echoMode, addPopUpInitialText, &okClicked);
    if (okClicked && !userInput.isEmpty()){
        this->addItem(userInput);
        settings.setValue(rowStr2, userInput);
        valueSettings.setValue(userInput, rowStr2);
        //settings.setValue(rowStr, userInput);
        //insertedItem = this->item(row);
        //insertedItem->setSizeHint(QSize(35,35));
    }

    /**
    this->inputDialogWindow.exec();
    QString userInput = this->inputDialogWindow.textValue();
    this->addItem(userInput);
    */
}

void TaskList::handleDeleteButton() {
    int selectedIndex = this->currentRow();

    if (selectedIndex != -1) {
        QString selectedItem = this->currentItem()->text();
        QString deletedItem = valueSettings.value(selectedItem).toString();
        QListWidgetItem *item = this->currentItem();
        QString key = QString::number(selectedIndex);
        this->takeItem(selectedIndex);
        //settings.remove(item->text());
        settings.remove(deletedItem);
        this->clearSelection();
    }
}

void TaskList::handleUpdateButton() {
    int selectedRowNo = this->currentRow();
    if( selectedRowNo != -1) {
        QString updatedRow = this->currentItem()->text();
        QString updateRowKey = valueSettings.value(updatedRow).toString();
        QListWidgetItem *selectedItem = this->currentItem();
        QString textToBeUpdated = selectedItem->text();
        settings.remove(updateRowKey);
        bool okClicked;
        QString updatedInput = inputDialogWindow.getText(this, updatePupUpTitle, updatePupUpLabel,
                                                         echoMode, textToBeUpdated, &okClicked);
        if (okClicked && !updatedInput.isEmpty()) {
            this->takeItem(selectedRowNo);
            this->insertItem(selectedRowNo,updatedInput);
            settings.setValue(updateRowKey, updatedInput);
            valueSettings.setValue(updatedInput, updateRowKey);
            this->clearSelection();
        }
    }
    /**
    inputDialogWindow.exec();
    int selectedRowNo = this->currentRow();
    this->takeItem(selectedRowNo);
    this->insertItem(selectedRowNo, inputDialogWindow.textValue());
    */
}

void TaskList::loadTasks() {
    for(const QString& key : keys){
        this->addItem((settings.value(key).toString()));
    }
}

void TaskList::mouseDoubleClickEvent(QMouseEvent *event) {
    this->clearSelection();
}