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
#include <QSplitter>
#include <QLCDNumber>
#pragma once


class MyWindow : public QMainWindow
{
Q_OBJECT

public:
    MyWindow();
    ~MyWindow();

private:
    QPushButton *btn_test;
    QPushButton *btn_o1;
    QPushButton *btn_o2;
    QPushButton *btn_c1;
    QPushButton *btn_c2;
    QPushButton *btn_load;
    QPushButton *btn_come;
    QPushButton *btn_go;
    

    QWidget *centralWidget;
    QWidget *picturelayout;
    QHBoxLayout *mainLayout;
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
    QTableView *tableView_go;
    // QHBoxLayout *tablelayout;
    // QVBoxLayout *tablelayout_go;
    // QWidget *tablewidget;
    // QWidget *tablewidget_go;
    QSplitter *splitter_list;
    //未入库车辆信息
    QStringList imageFiles;
    //入库的车辆信息
    QStringList imagecome;
    QString img;
    QLCDNumber lcd;
    void clock_num();
private slots:
    void onButton1Clicked();
    void onOpenclicked(const QString &men);
    void onCloseclicked(const QString &men);
    void plate(std::string &plateString,std::string pp[2]);
    void upData();
    void upDatacar();
    void comecar();
    void gobycar();
};

#endif // MYWINDOW_H
