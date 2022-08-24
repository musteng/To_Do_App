//
// Created by Mustafa Çevik on 7.07.2022.
//

#include "DatabaseHandler.h"


DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
    , networkAccessManager(this)
    , dbUrl("https://todoapp2-f922b-default-rtdb.europe-west1.firebasedatabase.app/ItemList.json")
{
}


DatabaseHandler::~DatabaseHandler()
{
}


std::vector<DatabaseItem*> DatabaseHandler::getData() {
    QNetworkRequest getRequest = QNetworkRequest(dbUrl);
    networkReply = this->networkAccessManager.get(getRequest);
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    if (!networkReply->error()) {
        QByteArray responseData = networkReply->readAll();
        QJsonDocument jsonResponseFromByteArray = QJsonDocument::fromJson(responseData);
        QJsonObject jsonResponse = jsonResponseFromByteArray.object();

        for (QString &key: jsonResponse.keys()) {
            listItemDB = new DatabaseItem;
            listItemDB->dbID = key;
            listItemDB->userInput = jsonResponse.value(key)["userInput"].toString();
            listItemDB->endingDate = jsonResponse.value(key)["endDate"].toString();
            listItemDB->priorityLevel = jsonResponse.value(key)["importance"].toString();
            listItemVectorDB.push_back(listItemDB);
        }
    }
    delete networkReply;
    networkReply = nullptr;

    return listItemVectorDB;
}


void DatabaseHandler::postData() {
    QString userInputDbKey = "userInput";
    QString endDateDbKey = "endDate";
    QString priorityDbKey = "importance";

    newDatabaseElement[userInputDbKey] = this->listItemDB->userInput;
    newDatabaseElement[priorityDbKey] = this->listItemDB->priorityLevel;
    newDatabaseElement[endDateDbKey] = this->listItemDB->endingDate;
    jsonData = QJsonDocument::fromVariant(newDatabaseElement);

    QNetworkRequest postRequest = QNetworkRequest(dbUrl);
    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkReply = networkAccessManager.post(postRequest, jsonData.toJson());
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (!networkReply->error()){
        QByteArray itemKey = networkReply->readAll();
        QJsonDocument jsonKeyDocument = QJsonDocument::fromJson(itemKey);
        QJsonObject jsonKeyObject = jsonKeyDocument.object();
        QString databaseItemKey = jsonKeyObject["name"].toString();
        qInfo() << databaseItemKey;

        listItemDB->dbID = databaseItemKey;
        //listItemVectorDB.push_back(listItemDB);
        dbKeys.push_back(databaseItemKey);
    }
    delete networkReply;
    networkReply = nullptr;
}


void DatabaseHandler::deleteData(int selectedRowNumber) {
    //QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QString dbKey = dbKeys[selectedRowNumber];
    QUrl deleteRequestUrl = "https://todoapp2-f922b-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json";
    QNetworkRequest deleteRequest = QNetworkRequest(deleteRequestUrl);
    networkAccessManager.deleteResource(deleteRequest);

    //delete listItemVectorDB[selectedRowNumber];
    //listItemVectorDB[selectedRowNumber] = nullptr;
    //listItemVectorDB.erase(listItemVectorDB.begin() + selectedRowNumber);
    dbKeys.erase(dbKeys.begin() + selectedRowNumber);
}


void DatabaseHandler::updateData(int selectedRowNumber) {
    //QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QString dbKey = dbKeys[selectedRowNumber];
    QString userInputDbKey = "userInput";
    QString endDateDbKey = "endDate";
    QString priorityDbKey = "importance";

    newDatabaseElement[userInputDbKey] = this->listItemDB->userInput;
    newDatabaseElement[endDateDbKey] = this->listItemDB->endingDate;
    newDatabaseElement[priorityDbKey] = this->listItemDB->priorityLevel;
    jsonData = QJsonDocument::fromVariant(newDatabaseElement);

    QUrl updateRequestUrl = "https://todoapp2-f922b-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json";
    QNetworkRequest updateRequest = QNetworkRequest(updateRequestUrl);
    updateRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkReply = networkAccessManager.put(updateRequest, jsonData.toJson()); // TODO PATCH
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (!networkReply->error()) {
        //listItemVectorDB[selectedRowNumber]->userInput = this->listItemDB->userInput;
        //listItemVectorDB[selectedRowNumber]->priorityLevel = this->listItemDB->priorityLevel;
        //listItemVectorDB[selectedRowNumber]->endingDate = this->listItemDB->endingDate;
    }
    delete networkReply;
    networkReply = nullptr;
}


QString DatabaseHandler::getSingleData(const QString& databaseID){
    QUrl itemUrl = "https://todoapp2-f922b-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + databaseID + ".json";
    QNetworkRequest getSingleElementRequest = QNetworkRequest(itemUrl);
    networkReply = this->networkAccessManager.get(getSingleElementRequest);
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QString addedTask;
    if (!networkReply->error()){
        QByteArray itemData = networkReply->readAll();
        QJsonDocument itemDataJsonDocument = QJsonDocument::fromJson(itemData);
        QJsonObject itemDataJson = itemDataJsonDocument.object();

        QString userInputText = itemDataJson["userInput"].toString();
        QString userInputDate = itemDataJson["endDate"].toString();
        QString userInputPriority = itemDataJson["importance"].toString();
        addedTask = userInputText + "\n" + userInputDate + "\n" + userInputPriority;
    }
    delete networkReply;
    networkReply = nullptr;
    return addedTask;
}

std::vector<QString> DatabaseHandler::getDBKeys() {
    QNetworkRequest getRequest = QNetworkRequest(dbUrl);
    networkReply = this->networkAccessManager.get(getRequest);
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (!networkReply->error()) {
        QByteArray responseData = networkReply->readAll();
        QJsonDocument jsonResponseFromByteArray = QJsonDocument::fromJson(responseData);
        QJsonObject jsonResponse = jsonResponseFromByteArray.object();
        for (QString &key: jsonResponse.keys()) {
            dbKeys.push_back(key);
        }
    }
    delete networkReply;
    networkReply = nullptr;

    return dbKeys;
}