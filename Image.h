#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QMouseEvent>

class Image:public QImage{

protected:
    void mousePressEvent(QMouseEvent *event) override {



    }

};

#endif // IMAGE_H
