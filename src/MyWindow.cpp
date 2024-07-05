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
#define Debug 0
MyWindow::MyWindow() : imagePath("/home/du/project/intelligence_parking/res/image/general_test/"), 
                tableView(new QTableView), 
                tablelayout(new QVBoxLayout),
                imagecome(QStringList()
                )
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    QDir dir(imagePath);
    
    // 获取文件夹中的所有图片文件
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.gif";
    dir.setNameFilters(filters);
    imageFiles = dir.entryList(QDir::Files);

    // 将文件名添加上路径前缀
    for (QString &file : imageFiles) {
        file = imagePath + file;
    }
    qDebug()<<imageFiles[0];
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
    btn1 = new QPushButton("测试");
    btn_o1 = new QPushButton("入库-A1");
    btn_o2 = new QPushButton("入库-A2");
    btn_c1 = new QPushButton("出库-B1");
    btn_c2 = new QPushButton("出库-B2");
    btn2 = new QPushButton("加载数据");
    btn3 = new QPushButton("车来了");
    btn4 = new QPushButton("车走了");

    //主界面创建、数据显示界面创建
    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(tablelayout);
    tablelayout->addWidget(btn2);
    //数据更新
    upData();
    
    //入库操作按钮显示
    layoutopen = new QVBoxLayout;
    mainLayout->addLayout(layoutopen);
    layoutopen->addWidget(btn1);
    layoutopen->addWidget(btn_o1);
    layoutopen->addWidget(btn_o2);
    layoutopen->addWidget(btn3);
   
    // 车辆信息显示
    picture = new Picture(this);
    QImage image(imageFiles[0]); 
    picture->setImage(image);
    mainLayout->addWidget(picture);

    //出库操作按钮显示
    layoutclose = new QVBoxLayout;
    mainLayout->addLayout(layoutclose);
    layoutclose->addWidget(btn_c1);
    layoutclose->addWidget(btn_c2);
    layoutclose->addWidget(btn4);

     // 创建中央窗口并设置布局
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 创建菜单栏和菜单项
    menuBar = new QMenuBar(this);
    fileMenu = new QMenu("文件");
    indexMenu = new QMenu("主页");
    exitAction = new QAction("打开", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    //按钮绑定
    connect(btn1,&QPushButton::clicked,this,&MyWindow::onButton1Clicked);
    connect(btn_o1,&QPushButton::clicked,this,&MyWindow::onOpenclicked);
    connect(btn_c1,&QPushButton::clicked,this,&MyWindow::onCloseclicked);
    connect(btn2,&QPushButton::clicked,this,&MyWindow::upData);
    connect(btn3,&QPushButton::clicked,this,&MyWindow::comecar);
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
    // tableView->setModel(model);
    // tablelayout->addWidget(tableView);

    // QSqlTableModel* model = new QSqlTableModel();
    // model->setTable("Caryard_table");
    // model->select();
    // if (!model->select()) {
    //     qDebug() << "Not table:" << model->lastError().text();
    //     delete model; // 清理未成功加载数据的模型
    //     exit(0);
    // }
    // if (model->rowCount() <= 0) {
    //     qDebug() << "Not data:" << "Caryard_table";
    //     delete model; 
    //    exit(0);
    // }
    //返回数据
    tableView->setModel(model);
    tablelayout->addWidget(tableView);
}

void MyWindow::comecar()
{
    
}

void MyWindow::gobycar()
{
}

//入库
void MyWindow::onOpenclicked()
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    //获取车牌信息
    std::string number = recognition->recogni(imageFiles[0]);
    std::string pp[2];
    plate(number,pp);
    QString carColor = QString::fromStdString(pp[0]);
    QString carId = QString::fromStdString(pp[1]);
    // 获取当前系统时间点
    QDateTime entryTime = QDateTime::currentDateTime();
    qDebug() << "num:" << carId;
    qDebug() << "color:" << carColor;
    qDebug() << "time:" << entryTime;
    dbManager.addCarInfo(carId, carColor, entryTime,"A1");
    upData();
}

//出库
void MyWindow::onCloseclicked()
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    //获取车牌信息
    std::string number = recognition->recogni(imageFiles[0]);
    std::string pp[2];
    plate(number,pp);
    QString carColor = QString::fromStdString(pp[0]);
    QString carId = QString::fromStdString(pp[1]);
    // 获取当前系统时间点
    QDateTime exitTime = QDateTime::currentDateTime();
    dbManager.closeCarInfo(carId, carColor, exitTime,"B1");
    upData();
}

void MyWindow::onButton1Clicked()
{
    std::string number = recognition->recogni(imageFiles[0]);
    std::cout << number <<std::endl;
}