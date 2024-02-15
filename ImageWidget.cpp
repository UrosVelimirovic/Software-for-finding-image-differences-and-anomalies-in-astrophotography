#include "ImageWidget.h"
#include <QPainter>

ImageWidget::ImageWidget(QWidget* parent):QWidget(parent){
     resize(600, 600);
}



void ImageWidget::setImage(const QImage& image) {
    actualImage = image;
    update();  // update trigeruje paintEvent
}

QImage ImageWidget::getImage() const {
    return actualImage;
}

int ImageWidget::getReferenceX()
{
    return this->referenceX;
}

int ImageWidget::getReferenceY()
{
    return this->referenceY;
}

void ImageWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawImage(0, 0 , actualImage);
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint clickPos = event->pos();
    referenceX = QString::number(clickPos.x()).toInt();
    referenceY = QString::number(clickPos.y()).toInt();
    referenceLabel->setText("X: "+ QString::number(clickPos.x()) + " Y: " + QString::number(clickPos.y()));

    // Call the base class implementation
    QWidget::mousePressEvent(event);
}
