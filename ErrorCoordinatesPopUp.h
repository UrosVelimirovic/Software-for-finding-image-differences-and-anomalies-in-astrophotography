#ifndef ERRORCOORDINATESPOPUP_H
#define ERRORCOORDINATESPOPUP_H
#include <QWidget>
#include <QLabel>

class ErrorCoordinatesPopUp : public QWidget {
    QString message;
    QLabel label;
public:

    ErrorCoordinatesPopUp(QString msg): QWidget(nullptr), message(msg), label(this){
        this->setFixedSize(600, 100);
        label.move(20,50);
        label.setFixedSize(500,20);
        label.setText(message);

    }

    void setMessage(QString message){
        this->message = message;
        label.setText(message);
    }
};

#endif // ERRORCOORDINATESPOPUP_H
