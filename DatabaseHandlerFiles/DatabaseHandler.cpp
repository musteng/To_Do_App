//
// Created by Mustafa Çevik on 7.07.2022.
//

#include "DatabaseHandler.h"


DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}


DatabaseHandler::~DatabaseHandler() {
    m_networkAccessManager->deleteLater();
}


std::vector<DatabaseItem*> DatabaseHandler::getData() {
    m_networkReply = this->m_networkAccessManager->get(QNetworkRequest(QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList.json")));
    connect(m_networkReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray responseData = m_networkReply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = json.object();

    for ( QString& key : jsonObject.keys() )
    {
        listItemDB = new DatabaseItem;
        listItemDB->dbID = key;
        listItemDB->userInput = jsonObject.value(key)["userInput"].toString();
        listItemDB->endingDate = jsonObject.value(key)["endDate"].toString();
        this->listItemDB->priorityLevel = jsonObject.value(key)["importance"].toString() ;
        listItemVectorDB.push_back(listItemDB);
    }
    return listItemVectorDB;
}


void DatabaseHandler::postData() {
    QString userIn = "userInput";
    QString endDateStr = "endDate";
    QString impStr = "importance";

    newItem [userIn] = this->listItemDB->userInput;
    newItem [impStr] = this->listItemDB->priorityLevel;
    newItem [endDateStr] = this->listItemDB->endingDate;
    jsonDoc = QJsonDocument::fromVariant(newItem);

    newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList.json"));
    newRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_networkReply = m_networkAccessManager->post(*newRequest, jsonDoc.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::itemToVector);
}


void DatabaseHandler::deleteData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json"));
    m_networkAccessManager->deleteResource(*newRequest);
    listItemVectorDB.erase(listItemVectorDB.begin() + selectedRowNumber);
}


void DatabaseHandler::updateData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QString userIn = "userInput";
    QString endDateStr = "endDate";
    QString impStr = "importance";

    newItem [userIn] = this->listItemDB->userInput;
    newItem [impStr] = this->listItemDB->priorityLevel;
    newItem [endDateStr] = this->listItemDB->endingDate;
    jsonDoc = QJsonDocument::fromVariant(newItem);

    newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json"));
    newRequest->setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkReply = m_networkAccessManager->put(*newRequest, jsonDoc.toJson()); // TODO PATCH

    listItemVectorDB[selectedRowNumber]->userInput = this->listItemDB->userInput;
    listItemVectorDB[selectedRowNumber]->priorityLevel = this->listItemDB->priorityLevel;
    listItemVectorDB[selectedRowNumber]->endingDate = this->listItemDB->endingDate;
}


void DatabaseHandler::itemToVector() {
    QByteArray itemKey = m_networkReply->readAll().split(':')[1];
    itemKey.chop(2);
    itemKey.remove(0, 1);
    qInfo() << itemKey;

    listItemDB->dbID = itemKey;
    listItemDB->userInput = this->listItemDB->userInput;
    listItemDB->endingDate = this->listItemDB->endingDate;
    listItemDB->priorityLevel = this->listItemDB->priorityLevel;
    listItemVectorDB.push_back(listItemDB);
}
