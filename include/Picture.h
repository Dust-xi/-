#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>

class Picture : public QWidget
{
    Q_OBJECT

public:
    Picture(QWidget *parent = nullptr);
    ~Picture();
    void setImage(const QImage &image);

private:
    QLabel *imageLabel;
    QVBoxLayout *layout;
};

#endif // PICTURE_H
