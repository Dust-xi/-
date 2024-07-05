#include "DataBase.h"

DataBase::DataBase()
{

}
bool DataBase :: connectToDatabase(const QString& host, const QString& dbName,
                           const QString& user, const QString& password) {
    const QString connectionName = "MYQTQSl";
    if (QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
        db.setHostName(host);
        db.setDatabaseName(dbName);
        db.setUserName(user);
        db.setPassword(password);
    }

    if (!db.open()) {
        qDebug() << "无法打开数据库:" << db.lastError().text();
        return false;
    }
    // 检查并创建表
    if (!checkAndCreateTables()) {
        qDebug() << "无法创建表:" << db.lastError().text();
        return false;
    }

    return true;
}
bool DataBase::checkAndCreateTables() {
    QSqlQuery query(db);

    // 检查并创建测试表
    if (!query.exec("CREATE TABLE IF NOT EXISTS example_table ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    "name VARCHAR(100), "
                    "age INT)")) {
        qDebug() << "创建表失败:" << query.lastError().text();
        return false;
    }

    // 检测创建停车表 车牌、车牌颜色、入库时间、出库时间、停车时间、入库口、出库口、主键车牌
    if (!query.exec("CREATE TABLE IF NOT EXISTS Caryard_table ("
                    "carId VARCHAR(100) NOT NULL,"
                    "carColor VARCHAR(50),"
                    "entryTime DATETIME,"
                    "exitTime DATETIME,"
                    "parkingDuration TIME,"
                    "entryGate VARCHAR(50),"
                    "exitGate VARCHAR(50),"
                    "PRIMARY KEY (carId))"))  {
        qDebug() << "创建表失败:" << query.lastError().text();
        return false;
    }

    // 添加更多表的检查和创建逻辑
    // if (!query.exec("CREATE TABLE IF NOT EXISTS another_table (...)")) {
    //     qDebug() << "创建表失败:" << query.lastError().text();
    //     return false;
    // }

    return true;
}

bool DataBase :: execQuery(const QString& queryStr) {
    QSqlQuery query(db);
    bool ok = query.exec(queryStr);
    if (!ok) {
        qDebug() << "执行查询时出错:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DataBase :: prepareAndExecQuery(const QString& queryStr) {
    QSqlQuery query(db);
    query.prepare(queryStr);
    query.exec();

    return query;
}
#include "DataBase.h"

//入库操作
bool DataBase::addCarInfo(const QString& carId, const QString& carColor,
                           const QDateTime& entryTime, const QDateTime& exitTime,
                           const QTime& parkingDuration, const QString& entryGate,
                           const QString& exitGate) {
    QSqlQuery query(db);

    query.prepare("INSERT INTO Caryard_table (carId, carColor, entryTime, exitTime, parkingDuration, entryGate, exitGate) "
                  "VALUES (:carId, :carColor, :entryTime, :exitTime, :parkingDuration, :entryGate, :exitGate)");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);
    query.bindValue(":entryTime", entryTime.toString(Qt::ISODate));
    query.bindValue(":exitTime", exitTime.toString(Qt::ISODate));
    query.bindValue(":parkingDuration", parkingDuration.toString("hh:mm:ss"));
    query.bindValue(":entryGate", entryGate);
    query.bindValue(":exitGate", exitGate);

    if (!query.exec()) {
        qDebug() << "插入数据失败:" << query.lastError().text();
        return false;
    }

    qDebug() << "成功插入数据!";
    return true;
}
//出库操作
bool DataBase::closeCarInfo(const QString& carId, const QString& carColor,
                           const QDateTime& entryTime, const QDateTime& exitTime,
                           const QTime& parkingDuration, const QString& entryGate,
                           const QString& exitGate) {
    QSqlQuery query(db);

    query.prepare("INSERT INTO Caryard_table (carId, carColor, entryTime, exitTime, parkingDuration, entryGate, exitGate) "
                  "VALUES (:carId, :carColor, :entryTime, :exitTime, :parkingDuration, :entryGate, :exitGate)");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);
    query.bindValue(":entryTime", entryTime.toString(Qt::ISODate));
    query.bindValue(":exitTime", exitTime.toString(Qt::ISODate));
    query.bindValue(":parkingDuration", parkingDuration.toString("hh:mm:ss"));
    query.bindValue(":entryGate", entryGate);
    query.bindValue(":exitGate", exitGate);

    if (!query.exec()) {
        qDebug() << "插入数据失败:" << query.lastError().text();
        return false;
    }

    qDebug() << "成功插入数据!";
    return true;
}
DataBase::~DataBase()
{

}
