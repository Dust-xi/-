#ifndef DISPLAYCLOCK_H
#define DISPLAYCLOCK_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPen>

class DisplayClock : public QWidget
{
    Q_OBJECT

public:
    DisplayClock(QWidget *parent = nullptr);
    ~DisplayClock();
    

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawHourHand(QPainter *painter);
    void drawMinuteHand(QPainter *painter);
    void drawSecondHand(QPainter *painter);
    void drawClockDial(QPainter *painter);

    // static const QPoint hourHand[4];
    // static const QPoint minuteHand[4];
    // static const QPoint secondHand[4];
    QVector<QPoint> hourHand;
    QVector<QPoint> minuteHand;
    QVector<QPoint> secondHand;

    QPen hourHandPen;
    QPen minuteHandPen;
};

#endif // DISPLAYCLOCK_H
