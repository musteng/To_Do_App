//
// Created by Mustafa Çevik on 7.07.2022.
//

#ifndef TO_DO_APP_DATABASEHANDLER_H
#define TO_DO_APP_DATABASEHANDLER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager> // Allows the application to send network requests and receive replies
#include <QtNetwork/QNetworkReply>  // The QNetworkReply class contains the data and headers for a request sent with QNetworkAccessManager
#include <QtNetwork/QNetworkRequest> // The QNetworkRequest class holds a request to be sent with QNetworkAccessManager.
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "DatabaseItem.h"
#include <QJsonObject>
#include "../WindowMain/ListItem.h"

class DatabaseHandler : public QObject {
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject* parent = nullptr);
    ~DatabaseHandler() override;

public:
    void postData();
    void getData();
    void updateData(int selectedRowNumber);
    void deleteData(int selectedRowNumber);
    void itemToVector();

    std::vector<DatabaseItem*> networkReply();
    std::vector<DatabaseItem*> listItemVectorDB;

public:
    DatabaseItem* listItemDB;

private:
    QNetworkAccessManager* m_networkAccessManager;
    QNetworkReply* m_networkReply;
    QVariantMap newItem;
    QJsonDocument jsonDoc;
    QNetworkRequest* newRequest;
};


#endif //TO_DO_APP_DATABASEHANDLER_H
