#include "MyWindow.h"
#include "DataBase.h"
#include "Picture.h"
#include "Recognition.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QTabBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTableView>
#include <QLabel>
#include <QDir>
#include <QRandomGenerator>
#include <QLabel>
#include <QSpacerItem>
#include <QSplitter>
#define Debug 0
MyWindow::MyWindow() : imagePath("/home/du/project/intelligence_parking/res/image/general_test/"), 
                tableView(new QTableView), 
                tableView_go(new QTableView),
                tablelayout(new QHBoxLayout),
                tablelayout_go(new QVBoxLayout),
                imagecome(QStringList()),
                img(QString()),
                picture(new Picture)
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    QDir dir(imagePath);
    
    // 获取文件夹中的jpg图片文件
    QStringList filters;
    filters << "*.jpg";
    dir.setNameFilters(filters);
    imageFiles = dir.entryList(QDir::Files);

    // 将文件名添加上路径前缀
    for (QString &file : imageFiles) {
        file = imagePath + file;
    }
    qDebug()<<imageFiles[0];
    img = imageFiles[0];
    //debug
    if(Debug){
        QString carId = "川12345";
        QString carColor = "蓝色";
        QDateTime entryTime = QDateTime::currentDateTime();
        QString entryGate = "A1";

        if (dbManager.addCarInfo(carId, carColor, entryTime, entryGate)) {
        qDebug() << "成功添加车辆信息到数据库!";
        } else {
        qDebug() << "添加车辆信息失败!";
        }
    }
    //按钮
    btn_test = new QPushButton("测试");
    btn_o1 = new QPushButton("入库-A1");
    btn_o2 = new QPushButton("入库-A2");
    btn_c1 = new QPushButton("出库-B1");
    btn_c2 = new QPushButton("出库-B2");
    btn_load = new QPushButton("加载数据");
    btn_come = new QPushButton("车来了");
    btn_go = new QPushButton("车走了");

    // 创建中央窗口并设置布局
    centralWidget = new QWidget(this);
    
    //主界面创建、数据显示界面创建
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    mainLayout = new QHBoxLayout;
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(splitter);
    //按钮容器
    QWidget *buttonwidget = new QWidget;
    //数据显示容器
    QWidget *listwidget = new QWidget;
    //图片显示容器
    QWidget *imgwidget = new QWidget;
    //将容器放入splitter中
    splitter->addWidget(buttonwidget);
    QSplitter *splitter_hor = new QSplitter(Qt::Horizontal);
    splitter->addWidget(splitter_hor);
    splitter_hor->addWidget(listwidget);
    splitter_hor->addWidget(imgwidget);

    //数据容器设置
    listwidget->setLayout(tablelayout);
    
    // 创建一个表名标签
    // QLabel *tableNameLabel = new QLabel("停车场现有车辆", listwidget);
    // tablelayout->addWidget(tableNameLabel);

    // 设置水平表头的伸缩模式
    tablelayout->addWidget(btn_load);

    //按钮容器设置
    QGridLayout *gridLayout = new QGridLayout;
    buttonwidget->setLayout(gridLayout);
    //入库操作按钮显示
    gridLayout->addWidget(btn_test, 0, 0); // 第一行第一列
    gridLayout->addWidget(btn_o1, 0, 1); // 第一行第二列
    gridLayout->addWidget(btn_o2, 0, 2); // 第一行第三列
    gridLayout->addWidget(btn_come, 0, 3); // 第一行第四列

    //出库操作按钮显示
    gridLayout->addWidget(btn_c1, 1, 0); // 第二行第一列
    gridLayout->addWidget(btn_c2, 1, 1); // 第二行第二列
    gridLayout->addWidget(btn_go, 1, 2); // 第二行第三列
    gridLayout->addWidget(btn_load,1,3);
    //图片容器设置
    splitter_hor->addWidget(picture);

    //表单更新
    //upData();
    //车来了
    comecar();

    setCentralWidget(centralWidget);

    // 创建菜单栏和菜单项
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu("文件");
    indexMenu = new QMenu("主页");
    exitAction = new QAction("打开", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    //按钮绑定
    connect(btn_test,&QPushButton::clicked,this,&MyWindow::onButton1Clicked);
    connect(btn_o1, &QPushButton::clicked, this, [=]() {
        this->onOpenclicked("A1");
    });
    connect(btn_c1, &QPushButton::clicked, this, [=]() {
        this->onCloseclicked("B1");
    });
    connect(btn_o2, &QPushButton::clicked, this, [=]() {
        this->onOpenclicked("A2");
    });
    connect(btn_c2, &QPushButton::clicked, this, [=]() {
        this->onCloseclicked("B2");
    });
    connect(btn_load,&QPushButton::clicked,this,&MyWindow::upData);
    connect(btn_come,&QPushButton::clicked,this,&MyWindow::comecar);
    connect(btn_go,&QPushButton::clicked,this,&MyWindow::gobycar);
    fileMenu->addAction(exitAction);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(indexMenu);

    setMenuBar(menuBar);
}

MyWindow::~MyWindow()
{
    
}

void MyWindow::plate(std::string &plateString,std::string pp[2]){
    // 找到分隔符位置
    size_t colonPos = plateString.find(':');
    
    if (colonPos != std::string::npos) {
        // 提取冒号前后的字符串
        std::string type = plateString.substr(0, colonPos); // 颜色
        std::string number = plateString.substr(colonPos + 1); // 车牌号
        
        // 输出结果
        std::cout << "类型: " << type << std::endl;
        std::cout << "号码: " << number << std::endl;
        pp[0]=type;
        pp[1]=number;
    } else {
        std::cout << "未找到分隔符" << std::endl;
    }
    
}

void MyWindow::upData()
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    QSqlTableModel *model = dbManager.getTableModel("Caryard_table");
    model->setTable("Caryard_table");
    model->select();
    if (!model->select()) {
        qDebug() << "Not table:" << model->lastError().text();
        delete model; // 清理未成功加载数据的模型
        exit(0);
    }
    if (model->rowCount() <= 0) {
        qDebug() << "Not data:" << "Caryard_table";
    }
    //返回数据
    tableView->setModel(model);
    tableView->setMinimumSize(400,600);
    tablelayout->addWidget(tableView);

}

void MyWindow::upDatacar()
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    QSqlTableModel *model_go = dbManager.getTableModel("Cargo_table");
    model_go->setTable("Cargo_table");
    model_go->select();

    if (!model_go->select()) {
        qDebug() << "Not table:" << model_go->lastError().text();
        delete model_go; // 清理未成功加载数据的模型
        exit(0); // 如果表不存在，程序退出
    }
    if (model_go->rowCount() <= 0) {
        qDebug() << "Not data in Cargo_table";
        // 添加一行空数据
    }
    tableView_go->setModel(model_go);
    tableView_go->setMinimumSize(400,600);
    tablelayout->addWidget(tableView_go);
}

void MyWindow::comecar()
{
    // 取0-250的随机数
    int randomNumber = QRandomGenerator::global()->bounded(0, 250 + 1);
    img = imageFiles[randomNumber];
    imagecome.append(img);
    qDebug() << img;
    QImage image(img); 
    picture->setImage(image); 
}

void MyWindow::gobycar()
{
    int count = imagecome.size();
    if (count == 0) {
        qDebug() << "没有车辆";
        return;
    }
    int randnumber = QRandomGenerator::global()->bounded(0, count);
    img = imagecome[randnumber];
    qDebug() << "gobycar selected image:" << img;
    QImage image(img);
    if (image.isNull()) {
        qDebug() << "Failed to load image:" << img;
        return;
    }
    picture->setImage(image);
    imagecome.removeAt(randnumber); // 从列表中移除已使用的图片
}

//入库
void MyWindow::onOpenclicked(const QString &men)
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    //获取车牌信息
    std::string number = recognition->recogni(img);
    std::string pp[2];
    plate(number,pp);
    QString carColor = QString::fromStdString(pp[0]);
    QString carId = QString::fromStdString(pp[1]);
    // 获取当前系统时间点
    QDateTime entryTime = QDateTime::currentDateTime();
    qDebug() << "num:" << carId;
    qDebug() << "color:" << carColor;
    qDebug() << "time:" << entryTime;
    dbManager.addCarInfo(carId, carColor, entryTime,men);
    upData();
}

//出库
void MyWindow::onCloseclicked(const QString &men)
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    //获取车牌信息
    std::string number = recognition->recogni(img);
    std::string pp[2];
    plate(number,pp);
    QString carColor = QString::fromStdString(pp[0]);
    QString carId = QString::fromStdString(pp[1]);
    // 获取当前系统时间点
    QDateTime exitTime = QDateTime::currentDateTime();
    dbManager.closeCarInfo(carId, carColor, exitTime,men);
    upDatacar();
}

void MyWindow::onButton1Clicked()
{
    std::string number = recognition->recogni(img);
    std::cout << number <<std::endl;
}