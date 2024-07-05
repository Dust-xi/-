#ifndef RECGNITION_H
#define RECGNITION_H

#include "easypr.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QObject>
#include <QString>
#include <QImage>
class Recognition : public QObject
{
Q_OBJECT
public:
    Recognition(QObject *parent = nullptr);
    ~Recognition();
    QString imgpath;
    

private:
    
public slots:
    cv::String recogni(const QString &img);
};

#endif