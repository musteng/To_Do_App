//
// Created by Mustafa Çevik on 7.07.2022.
//

#include "DatabaseHandler.h"


DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
    , networkAccessManager(this)
    , dbUrl("https://todoapp2-f922b-default-rtdb.europe-west1.firebasedatabase.app/")
{
}


DatabaseHandler::~DatabaseHandler() = default;


void DatabaseHandler::postData() {
    QString userInputDbKey = "userInput";
    QString endDateDbKey = "endDate";
    QString priorityDbKey = "importance";

    newDatabaseElement[userInputDbKey] = this->listItemDB->userInput;
    newDatabaseElement[priorityDbKey] = this->listItemDB->priorityLevel;
    newDatabaseElement[endDateDbKey] = this->listItemDB->endingDate;
    jsonData = QJsonDocument::fromVariant(newDatabaseElement);

    QUrl postRequestUrl = dbUrl + ".json";
    QNetworkRequest postRequest = QNetworkRequest(postRequestUrl);
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
        dbKeys.push_back(databaseItemKey);
    }
    delete networkReply;
    networkReply = nullptr;
}


void DatabaseHandler::deleteData(int selectedRowNumber) {
    QString dbKey = dbKeys[selectedRowNumber];
    QUrl deleteRequestUrl = dbUrl + dbKey + ".json";
    QNetworkRequest deleteRequest = QNetworkRequest(deleteRequestUrl);
    networkAccessManager.deleteResource(deleteRequest);
    dbKeys.erase(dbKeys.begin() + selectedRowNumber);
}


void DatabaseHandler::updateData(int selectedRowNumber) {
    QString dbKey = dbKeys[selectedRowNumber];
    QString userInputDbKey = "userInput";
    QString endDateDbKey = "endDate";
    QString priorityDbKey = "importance";

    newDatabaseElement[userInputDbKey] = this->listItemDB->userInput;
    newDatabaseElement[endDateDbKey] = this->listItemDB->endingDate;
    newDatabaseElement[priorityDbKey] = this->listItemDB->priorityLevel;
    jsonData = QJsonDocument::fromVariant(newDatabaseElement);

    QUrl updateRequestUrl = dbUrl + dbKey + ".json";
    QNetworkRequest updateRequest = QNetworkRequest(updateRequestUrl);
    updateRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkReply = networkAccessManager.put(updateRequest, jsonData.toJson());
    connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    delete networkReply;
    networkReply = nullptr;
}


QString DatabaseHandler::getSingleData(const QString& databaseID){
    QUrl itemUrl = dbUrl + databaseID + ".json";
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


// This function gets database keys at the application opening.
std::vector<QString> DatabaseHandler::getDBKeys() {
    QUrl getRequestUrl = dbUrl + ".json";
    QNetworkRequest getRequest = QNetworkRequest(getRequestUrl);
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
