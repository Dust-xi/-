#include "DisplayClock.h"
#include<QPainter>
#include<QPen>
#include<QTime>
#include<QTimer>
#include<QLabel>
#include<QPushButton>
#include<QDebug>
DisplayClock::DisplayClock(QWidget *parent): QWidget(parent), 
            hourHandPen(Qt::black, 2.0), 
            minuteHandPen(Qt::black, 1.0)
{
    // const QPoint hourHand[4] = {
    //     QPoint(3, 5),
    //     QPoint(0, 13),
    //     QPoint(-3, 5),
    //     QPoint(0, -40)
    // };
    // const QPoint minuteHand[4] = {
    //     QPoint(3, 5),
    //     QPoint(0, 16),
    //     QPoint(-3, 5),
    //     QPoint(0, -70)
    // };
    // const QPoint secondHand[4] = {
    //     QPoint(3, 5),
    //     QPoint(0, 18),
    //     QPoint(-3, 5),
    //     QPoint(0, -90)
    // };
    // 初始化时钟指针的形状
    hourHand << QPoint(3, 5) << QPoint(0, 13) << QPoint(-3, 5) << QPoint(0, -40);
    minuteHand << QPoint(3, 5) << QPoint(0, 16) << QPoint(-3, 5) << QPoint(0, -70);
    secondHand << QPoint(3, 5) << QPoint(0, 18) << QPoint(-3, 5) << QPoint(0, -90);
    // 设置定时器，每秒更新一次
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&DisplayClock::update));
    timer->start(1000);
}

void DisplayClock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    //设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //自动算出大小保证正圆
    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-100, -100, 200, 200);

    drawClockDial(&painter);
    drawHourHand(&painter);
    drawMinuteHand(&painter);
    drawSecondHand(&painter);
    //qDebug() << "paintEvent";
}
void DisplayClock::drawClockDial(QPainter *painter)
{   
    painter->setPen(hourHandPen);

    for (int i = 0; i < 12; ++i) {
        painter->drawLine(88, 0, 96, 0);
        painter->rotate(30.0);
    }

    painter->setPen(minuteHandPen);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter->drawLine(92, 0, 96, 0);
        painter->rotate(6.0);
    }
}

void DisplayClock::drawHourHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);

    painter->save();
    painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter->drawConvexPolygon(hourHand.data(), hourHand.size());
    // painter->drawConvexPolygon(hourHand,4);
    painter->restore();
    //qDebug() << "drawHourHand";
}

void DisplayClock::drawMinuteHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);

    painter->save();
    painter->rotate(6.0 * ((time.minute() + time.second() / 60.0)));
    painter->drawConvexPolygon(minuteHand.data(), minuteHand.size());
    // painter->drawConvexPolygon(minuteHand,4);
    painter->restore();
    //qDebug() << "drawMinuteHand";
}

void DisplayClock::drawSecondHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);

    painter->save();
    painter->rotate(6.0 * time.second());
    painter->drawConvexPolygon(secondHand.data(), secondHand.size());
    // painter->drawConvexPolygon(secondHand,4);
    painter->restore();
    //qDebug() << "drawSecondHand";
}

DisplayClock::~DisplayClock()
{
}