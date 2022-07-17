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
    connect(m_networkReply, SIGNAL(finished()), &m_loop, SLOT(quit()));
    m_loop.exec();

    QByteArray responseData = m_networkReply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = json.object();

    for ( QString& key : jsonObject.keys() )
    {
        listItemDB = new DatabaseItem;
        listItemDB->dbID = key;
        listItemDB->userInput = jsonObject.value(key)["userInput"].toString();
        listItemDB->endingDate = jsonObject.value(key)["endDate"].toString();
        listItemDB->priorityLevel = jsonObject.value(key)["importance"].toString() ;
        listItemVectorDB.push_back(listItemDB);
    }
    return listItemVectorDB;
}


void DatabaseHandler::postData() {
    QString userIn = "userInput";
    QString endDateStr = "endDate";
    QString impStr = "importance";

    m_newItem [userIn] = this->listItemDB->userInput;
    m_newItem [impStr] = this->listItemDB->priorityLevel;
    m_newItem [endDateStr] = this->listItemDB->endingDate;
    m_jsonDoc = QJsonDocument::fromVariant(m_newItem);

    m_newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList.json"));
    m_newRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_networkReply = m_networkAccessManager->post(*m_newRequest, m_jsonDoc.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::itemToVector);
}


void DatabaseHandler::deleteData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    m_newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json"));
    m_networkAccessManager->deleteResource(*m_newRequest);
    listItemVectorDB.erase(listItemVectorDB.begin() + selectedRowNumber);
}


void DatabaseHandler::updateData(int selectedRowNumber) {
    QString dbKey = listItemVectorDB[selectedRowNumber]->dbID;
    QString userIn = "userInput";
    QString endDateStr = "endDate";
    QString impStr = "importance";

    m_newItem [userIn] = this->listItemDB->userInput;
    m_newItem [impStr] = this->listItemDB->priorityLevel;
    m_newItem [endDateStr] = this->listItemDB->endingDate;
    m_jsonDoc = QJsonDocument::fromVariant(m_newItem);

    m_newRequest = new QNetworkRequest( QUrl("https://todoapp-c3d85-default-rtdb.europe-west1.firebasedatabase.app/ItemList/" + dbKey + ".json"));
    m_newRequest->setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    m_networkReply = m_networkAccessManager->put(*m_newRequest, m_jsonDoc.toJson()); // TODO PATCH

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
    listItemVectorDB.push_back(listItemDB);
}
