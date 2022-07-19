//
// Created by Mustafa Çevik on 7.07.2022.
//

#ifndef TO_DO_APP_DATABASEHANDLER_H
#define TO_DO_APP_DATABASEHANDLER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include "DatabaseItem.h"


class DatabaseHandler : public QObject {
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject* parent = nullptr);
    ~DatabaseHandler() override;

public:
    std::vector<DatabaseItem*> getData();
    void postData();
    void updateData(int selectedRowNumber);
    void deleteData(int selectedRowNumber);

public:
    DatabaseItem* listItemDB;
    std::vector<DatabaseItem*> listItemVectorDB;

private:
    QNetworkAccessManager networkAccessManager;
    QNetworkReply* networkReply;
    QVariantMap newDatabaseElement;
    QJsonDocument jsonData;
    QEventLoop eventLoop;
    QUrl dbUrl;
};


#endif //TO_DO_APP_DATABASEHANDLER_H
