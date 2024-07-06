// Picture.cpp
#include "Picture.h"

Picture::Picture(QWidget *parent)
    : QWidget(parent), scaleFactor(1.0)
{
}

void Picture::setImagePath(const QString &path)
{
    imagePath = path;
    image.load(imagePath); // 加载图片
    update();
}

void Picture::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (!image.isNull()) {
        int w = static_cast<int>(image.width() * scaleFactor);
        int h = static_cast<int>(image.height() * scaleFactor);
        painter.drawImage(0, 0, image.scaled(w, h, Qt::KeepAspectRatio));
    }
}

void Picture::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        // 滚轮向上滚动，放大图片
        scaleFactor *= 1.1;
    } else {
        // 滚轮向下滚动，缩小图片
        scaleFactor /= 1.1;
    }

    // 限制缩放比例范围
    if (scaleFactor < 0.1) {
        scaleFactor = 0.1;
    } else if (scaleFactor > 10.0) {
        scaleFactor = 10.0;
    }

    update();
}
