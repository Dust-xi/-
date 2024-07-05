#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#pragma once

class DataBase
{
private:
    QSqlDatabase db;
public:
    DataBase();
    ~DataBase();
    bool connectToDatabase(const QString& host, const QString& dbName,
                           const QString& user, const QString& password);
    bool execQuery(const QString& queryStr);
    QSqlQuery prepareAndExecQuery(const QString& queryStr);
    bool checkAndCreateTables();
    bool addCarInfo(const QString& carId, const QString& carColor,
                const QDateTime& entryTime, const QDateTime& exitTime,
                const QTime& parkingDuration, const QString& entryGate,
                const QString& exitGate);
    bool closeCarInfo(const QString& carId, const QString& carColor,
                           const QDateTime& entryTime, const QDateTime& exitTime,
                           const QTime& parkingDuration, const QString& entryGate,
                           const QString& exitGate)
};

#endif