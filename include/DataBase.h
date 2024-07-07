#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QSqlTableModel>
#pragma once

class DataBase
{
private:
    QSqlDatabase db;
public:
    DataBase();
    ~DataBase();
    //打开数据库
    bool connectToDatabase(const QString& host, const QString& dbName,
                           const QString& user, const QString& password);
    //数据库查询
    bool execQuery(const QString& queryStr);

    QSqlQuery prepareAndExecQuery(const QString& queryStr);
    //检查数据库表
    bool checkAndCreateTables();
    //车辆入库
    bool addCarInfo(const QString& carId, const QString& carColor,
                    const QDateTime& entryTime,  const QString& entryGate);
    //车辆出库
    bool closeCarInfo(const QString& carId, const QString& carColor,
                    const QDateTime& exitTime,const QString& exitGate);
    //获取数据
    QSqlTableModel* getTableModel(const QString& tableName);
    //已入库车辆检测
    int carnumber();

};

#endif