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
    void postData();
    void updateData(int selectedRowNumber);
    void deleteData(int selectedRowNumber);
    QString getSingleData(const QString& databaseID);
    std::vector<QString> getDBKeys();

public:
    DatabaseItem* listItemDB;
    std::vector<QString> dbKeys;
    QString dbUrl;

private:
    QNetworkAccessManager networkAccessManager;
    QNetworkReply* networkReply;
    QVariantMap newDatabaseElement;
    QJsonDocument jsonData;
    QEventLoop eventLoop;
};


#endif //TO_DO_APP_DATABASEHANDLER_H
