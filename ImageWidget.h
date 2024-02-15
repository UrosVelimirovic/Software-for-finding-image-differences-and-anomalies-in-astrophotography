#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
class ImageWidget : public QWidget {
    Q_OBJECT
    QImage actualImage;
    QLabel* referenceLabel;
    int referenceX;
    int referenceY;
    QString path;
public:
    ImageWidget(QWidget* parent = nullptr);

    void setImage(const QImage& image);
    QImage getImage() const;

    void setReferenceLabelPointer(QLabel* referenceLabelReceived){
        referenceLabel = referenceLabelReceived;
    }

    int getReferenceX();
    int getReferenceY();
    void setPath(QString path){
        this->path = path;
    }
    QString getPath(){
        return this->path;
    }
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;


};
#endif // IMAGEWIDGET_H
