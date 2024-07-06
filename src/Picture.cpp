#include "Picture.h"

Picture::Picture(QWidget *parent) : QWidget(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(500,350);
    layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    setLayout(layout);
}

Picture::~Picture()
{
    
}

void Picture::setImage(const QImage &image)
{
    imageLabel->setPixmap(QPixmap::fromImage(image));
}
