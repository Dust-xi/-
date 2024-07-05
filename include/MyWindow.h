#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QTabBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>
#include <QString>
#include "Picture.h"
#include "Recognition.h"
#include "DataBase.h"
#include <chrono>
#include <ctime>
#include <QDateTime>
#include <QAction>
#include <QSqlTableModel>
#include <QTableView>
#include <QStringList>
#pragma once


class MyWindow : public QMainWindow
{
Q_OBJECT

public:
    MyWindow();
    ~MyWindow();

private:
    QPushButton *btn1;
    QPushButton *btn_o1;
    QPushButton *btn_o2;
    QPushButton *btn_c1;
    QPushButton *btn_c2;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    

    QWidget *centralWidget;
    QWidget *picturelayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *layoutopen;
    QVBoxLayout *layoutclose;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *indexMenu;
    QAction *exitAction;
    Picture *picture;
    Recognition *recognition;
    QString number;
    QImage image;
    QString imagePath;
    DataBase dbManager;
    QTableView *tableView;
    QVBoxLayout *tablelayout;
    //未入库车辆信息
    QStringList imageFiles;
    //入库的车辆信息
    QStringList imagecome;

private slots:
    void onButton1Clicked();
    void onOpenclicked();
    void onCloseclicked();
    void plate(std::string &plateString,std::string pp[2]);
    void upData();
    void comecar();
    void gobycar();
};

#endif // MYWINDOW_H
