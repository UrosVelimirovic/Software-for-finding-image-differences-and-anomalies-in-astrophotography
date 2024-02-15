#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include "ImageWidget.h"
#include "Comparator.h"
#include "ErrorCoordinatesPopUp.h"

class MainWindow: public QWidget{
    QLabel* title;
    QPushButton* buttonFile1;
    QPushButton* buttonFile2;
    ImageWidget* imageWidget1;
    ImageWidget* imageWidget2;
    QLabel* file1PathLabel;
    QLabel* file2PathLabel;
    QLabel* file1Label;
    QLabel* file2Label;
    QPushButton* referenceButton1;
    QPushButton* referenceButton2;
    QLabel* referenceLabel1;
    QLabel* referenceLabel2;
    bool image1Selected;
    bool image2Selected;
    QPushButton* startButton;
    ErrorCoordinatesPopUp* ecpp;
    ImageWidget* penguin;

public:
    MainWindow(QWidget* parent = nullptr);
private slots:
    void imageSelector();
    void startComparing();
private:
    void openImageDialog(ImageWidget* imageWidget, QLabel* label);
    void openImage(ImageWidget* imageWidget, QLabel* label);

    friend class ImageWidget;
};

#endif // MAINWINDOW_H
