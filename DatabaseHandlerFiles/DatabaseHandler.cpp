//
// Created by Mustafa Çevik on 7.07.2022.
//

#include "DatabaseHandler.h"


DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
    , networkAccessManager(this)
    , dbUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList.json")
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
        QByteArray itemKey = networkReply->readAll().split(':')[1];
        itemKey.chop(2);
        itemKey.remove(0, 1);
        qInfo() << itemKey;

        listItemDB->dbID = itemKey;
        listItemVectorDB.push_back(listItemDB);
    }
    delete networkReply;
    networkReply = nullptr;
}


void DatabaseHandler::deleteData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QUrl deleteRequestUrl = "https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json";
    QNetworkRequest deleteRequest = QNetworkRequest(deleteRequestUrl);
    networkAccessManager.deleteResource(deleteRequest);

    delete listItemVectorDB[selectedRowNumber];
    listItemVectorDB[selectedRowNumber] = nullptr;
    listItemVectorDB.erase(listItemVectorDB.begin() + selectedRowNumber);
}


void DatabaseHandler::updateData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QString userInputDbKey = "userInput";
    QString endDateDbKey = "endDate";
    QString priorityDbKey = "importance";

    newDatabaseElement[userInputDbKey] = this->listItemDB->userInput;
    newDatabaseElement[endDateDbKey] = this->listItemDB->endingDate;
    newDatabaseElement[priorityDbKey] = this->listItemDB->priorityLevel;
    jsonData = QJsonDocument::fromVariant(newDatabaseElement);

    QUrl updateRequestUrl = "https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json";
    QNetworkRequest updateRequest = QNetworkRequest(updateRequestUrl);
    updateRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkReply = networkAccessManager.put(updateRequest, jsonData.toJson()); // TODO PATCH

    if (!networkReply->error()) {
        listItemVectorDB[selectedRowNumber]->userInput = this->listItemDB->userInput;
        listItemVectorDB[selectedRowNumber]->priorityLevel = this->listItemDB->priorityLevel;
        listItemVectorDB[selectedRowNumber]->endingDate = this->listItemDB->endingDate;
    }
    delete networkReply;
    networkReply = nullptr;
}
