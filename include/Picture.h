// Picture.h
#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>
#include <QImage>
#include <QWheelEvent>
#include <QPainter>

class Picture : public QWidget
{
    Q_OBJECT

public:
    explicit Picture(QWidget *parent = nullptr);
    void setImagePath(const QString &path);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QImage image;
    QString imagePath;
    double scaleFactor;
};

#endif // PICTURE_H
