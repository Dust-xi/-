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
#pragma once

class MyWindow : public QMainWindow
{
Q_OBJECT

public:
    MyWindow();
    ~MyWindow();

private:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;

    QWidget *centralWidget;
    QWidget *picturelayout;
    QVBoxLayout *mainLayout;
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

private slots:
    void onButton1Clicked();
    void onOpenclicked();
    void onCloseclicked();
    void plate(std::string &plateString,std::string pp[2]);
};

#endif // MYWINDOW_H
