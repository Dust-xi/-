#include "DataBase.h"
#include <iostream>
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
    if (db.open()) {
        qDebug() << "打开数据库成功！";
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
    // 检测创建出车表 车牌、车牌颜色、入库时间、出库时间、停车时间、入库口、出库口、主键id
    if (!query.exec("CREATE TABLE IF NOT EXISTS Cargo_table ("
                "Id INTEGER PRIMARY KEY AUTO_INCREMENT,"
                "carId VARCHAR(100),"
                "carColor VARCHAR(50),"
                "entryTime DATETIME,"
                "exitTime DATETIME,"
                "parkingDuration TIME,"
                "entryGate VARCHAR(50),"
                "exitGate VARCHAR(50),"
                "carBill DOUBLE(10, 2));"))  {
    qDebug() << "创建表失败:" << query.lastError().text();
    return false;
}
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
//入库操作 车牌、车牌色、入库时间、入库口
bool DataBase::addCarInfo(const QString& carId, const QString& carColor,
                          const QDateTime& entryTime, const QString& entryGate) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Caryard_table (carId, carColor, entryTime, exitTime, parkingDuration, entryGate, exitGate) "
                  "VALUES (:carId, :carColor, :entryTime, :exitTime, :parkingDuration, :entryGate, :exitGate)");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);
    query.bindValue(":entryTime", entryTime.toString(Qt::ISODate));
    query.bindValue(":entryGate", entryGate);
    //没有数据的设置为空
    query.bindValue(":exitTime", QVariant(QVariant::String)); 
    query.bindValue(":parkingDuration", QVariant(QVariant::String)); 
    query.bindValue(":exitGate", QVariant(QVariant::String)); 

    if (!query.exec()) {
        qDebug() << "入库失败:" << query.lastError().text();
        return false;
    }

    qDebug() << "成功入库!";
    return true;
}

//出库操作  根据车牌、车牌色查找车 、出库时间、出库口
bool DataBase::closeCarInfo(const QString& carId, const QString& carColor,
                            const QDateTime& exitTime, const QString& exitGate) {
    QSqlQuery query(db);

    // 查找车辆的入库时间和入库口
    query.prepare("SELECT entryTime, entryGate FROM Caryard_table WHERE carId = :carId AND carColor = :carColor AND exitTime IS NULL;");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);

    if (!query.exec() || !query.next()) {
        qDebug() << "未找到车辆或查询失败:" << query.lastError().text();
        return false;
    }

    QDateTime entryTime = query.value("entryTime").toDateTime();
    QString entryGate = query.value("entryGate").toString();
    // 计算停车时间
    qint64 durationSecs = entryTime.secsTo(exitTime);
    QTime parkingDuration = QTime(0, 0).addSecs(durationSecs);
    qDebug() << "停车时间" << parkingDuration;
    // 更新出库信息
    query.prepare("UPDATE Caryard_table SET exitTime = :exitTime, parkingDuration = :parkingDuration, exitGate = :exitGate "
                  "WHERE carId = :carId AND carColor = :carColor AND exitTime IS NULL");
    query.bindValue(":exitTime", exitTime.toString(Qt::ISODate));
    query.bindValue(":parkingDuration", parkingDuration.toString("hh:mm:ss"));
    query.bindValue(":exitGate", exitGate);
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);

    if (!query.exec()) {
        qDebug() << "出库失败:" << query.lastError().text();
        return false;
    }
    qDebug() << "成功出库!";
    // 出库成功后插入 Cargo_table
    qDebug() << "出库结算";
    double bill = 0;
    if(parkingDuration.toString("hh:mm:ss")>"00:00:00.000"&&parkingDuration.toString("hh:mm:ss")<"00:00:10.000"){
        bill = 0;
    }else if (parkingDuration.toString("hh:mm:ss")>"00:00:10.000"&&parkingDuration.toString("hh:mm:ss")<="00:00:15.000")
    {
        bill = 5;
    }else if (parkingDuration.toString("hh:mm:ss")>"00:00:15.000"&&parkingDuration.toString("hh:mm:ss")<="00:00:20.000")
    {
        bill = 10;
    }else if (parkingDuration.toString("hh:mm:ss")>"00:00:20.000"&&parkingDuration.toString("hh:mm:ss")<="00:00:30.000")
    {
        bill = 15.5;
    }else if (parkingDuration.toString("hh:mm:ss")>"00:00:30.000"&&parkingDuration.toString("hh:mm:ss")<="00:00:40.000")
    {
        bill = 25;
    }else if (parkingDuration.toString("hh:mm:ss")>"00:00:40.000"&&parkingDuration.toString("hh:mm:ss")<="00:00:60.000")
    {
        bill = 30;
    }
    else if (parkingDuration.toString("hh:mm:ss")>"00:00:60.000")
    {
        bill = 50;
    }
    query.prepare("INSERT INTO Cargo_table (carId, carColor, entryTime, exitTime, parkingDuration, entryGate, exitGate, carBill) "
                  "VALUES (:carId, :carColor, :entryTime, :exitTime, :parkingDuration, :entryGate, :exitGate, :carBill)");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);
    query.bindValue(":entryTime", entryTime);
    query.bindValue(":exitTime", exitTime.toString(Qt::ISODate));
    query.bindValue(":parkingDuration", parkingDuration.toString("hh:mm:ss"));
    query.bindValue(":entryGate", entryGate);
    query.bindValue(":exitGate", exitGate);
    query.bindValue(":carBill", bill);

    if (!query.exec()) {
        qDebug() << "插入 Cargo_table 失败:" << query.lastError().text();
        return false;
    }
    qDebug() << "结算成功";
    // 删除已出库的车辆信息
    query.prepare("DELETE FROM Caryard_table WHERE carId = :carId AND carColor = :carColor AND exitTime = :exitTime");
    query.bindValue(":carId", carId);
    query.bindValue(":carColor", carColor);
    query.bindValue(":exitTime", exitTime.toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "删除数据失败:" << query.lastError().text();
        return false;
    }

    qDebug() << "成功出库并删除数据!";
    return true;
}

QSqlTableModel* DataBase::getTableModel(const QString& tableName)
{
    QSqlTableModel* model = new QSqlTableModel(nullptr, db);
    if (db.isOpen()) {
        qDebug() << "Database connection is open.";
    } else {
        qDebug() << "Database connection is not open.";
    }
    model->setTable(tableName);
    // 设置编辑策略
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 更新
    model->select();
    // 设置表头
    if (!model->select()) {
        qDebug() << "Not table:" << model->lastError().text();
        delete model; // 清理未成功加载数据的模型
        return nullptr;
    }
    if (model->rowCount() <= 0) {
        qDebug() << "Not data:" << tableName;
        delete model; 
        return nullptr;
    }

    // 成功获取数据
    return model;
}

int DataBase::carnumber()
{
    int count =0;
    QSqlQuery query(db);
    if(query.exec("SELECT COUNT(*) FROM Caryard_table")){
        if(query.next()){
            count = query.value(0).toInt();
        }else{
            qDebug() << "error:" << query.lastError().text();
        }
    std::cout << "car number:" << count <<std::endl;
    }
    return count;
}

DataBase::~DataBase()
{
    //关闭数据库
    if (db.isOpen()) {
        db.close();
    }
}
