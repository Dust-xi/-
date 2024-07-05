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
#include <QListWidget>
#include <QLabel>
MyWindow::MyWindow() : imagePath("/home/du/project/intelligence_parking/res/image/general_test/川A09X20.jpg")
{
    DataBase dbManager;
    if (dbManager.connectToDatabase("localhost", "car", "root", "123456")) {
        std::cout << "连接成功！" << std::endl;
    }
    btn1 = new QPushButton("测试");
    btn2 = new QPushButton("入库");
    btn3 = new QPushButton("出库");
    // btn4 = new QPushButton("信息");
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(btn1);
    mainLayout->addWidget(btn2);
    mainLayout->addWidget(btn3);
    // mainLayout->addWidget(btn4);
   
    // 创建Picture对象
    picture = new Picture(this);
    QImage image(imagePath); 
    picture->setImage(image);
    mainLayout->addWidget(picture);
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

    connect(btn1,&QPushButton::clicked,this,&MyWindow::onButton1Clicked);
    connect(btn2,&QPushButton::clicked,this,&MyWindow::onOpenclicked);

    fileMenu->addAction(exitAction);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(indexMenu);

    setMenuBar(menuBar);
}

MyWindow::~MyWindow()
{
    
}

void MyWindow::plate(std::string &plateString,std::string pp[2]){
    // 找到冒号的位置
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
        std::cout << "未找到冒号" << std::endl;
    }
    
}

void MyWindow::onOpenclicked()
{
    std::string number = recognition->recogni(imagePath);
    std::string pp[2];
    plate(number,pp);
    // 获取当前系统时间点
    auto now = std::chrono::system_clock::now();
    // 将时间点转换为时间类型
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    // 使用 localtime 将时间类型转换为本地时间
    std::tm *local_time = std::localtime(&now_time);
    // 格式化当前时间为字符串
    char currentTime[100];
    std::strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", local_time);

    // dbManager.execQuery();
}


void MyWindow::onCloseclicked()
{
}

void MyWindow::onButton1Clicked()
{
    std::string number = recognition->recogni(imagePath);
    std::cout << number <<std::endl;
}