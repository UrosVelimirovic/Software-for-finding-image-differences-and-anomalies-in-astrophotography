#include "MainWindow.h"
#include <QFont>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget* parent)
{
    resize(600, 600);
    setWindowTitle("AstroDiff");

    // setting the title
    title = new QLabel(this);
    QFont titleFont("Helvetica");
    titleFont.setPointSize(25);
    title->setFont(titleFont);
    title->move(230, 70);
    title->setText("AstroDiff");
    title->setFixedSize(300,100);

    // Image 1 button
    buttonFile1 = new QPushButton(this);
    buttonFile1->setText("choose");
    buttonFile1->move(75,300);
    image1Selected = false;

    // Image 2 button
    buttonFile2 = new QPushButton(this);
    buttonFile2->setText("choose");
    buttonFile2->move(75,400);
    image2Selected = false;

    // setting Image widgets and connecting slots and signals for images
    imageWidget1 = new ImageWidget();
    imageWidget2 = new ImageWidget();
    connect(buttonFile1, &QPushButton::clicked, this, &MainWindow::imageSelector);
    connect(buttonFile2, &QPushButton::clicked, this, &MainWindow::imageSelector);

    // Image1: label
    file1Label = new QLabel(this);
    file1Label->move(20,300);
    file1Label->setFixedSize(45,20);
    file1Label->setText("Image 1:");

    // Image2: label
    file2Label = new QLabel(this);
    file2Label->move(20,400);
    file2Label->setFixedSize(45,20);
    file2Label->setText("Image 2:");

    // Path label 1
    file1PathLabel = new QLabel(this);
    file1PathLabel->move(50,350);
    file1PathLabel->setFixedSize(500,20);

    // Path label 2
    file2PathLabel = new QLabel(this);
    file2PathLabel->move(50,450);
    file2PathLabel->setFixedSize(500,20);

    // refference button 1
    referenceButton1 = new QPushButton(this);
    referenceButton1->setText("reference");
    referenceButton1->move(175,300);
    connect(referenceButton1, &QPushButton::clicked, this, &MainWindow::imageSelector);

    // reference button 2
    referenceButton2 = new QPushButton(this);
    referenceButton2->setText("reference");
    referenceButton2->move(175,400);
    connect(referenceButton2, &QPushButton::clicked, this, &MainWindow::imageSelector);

    // reference label 1
    referenceLabel1 = new QLabel(this);
    referenceLabel1->move(250,300);
    referenceLabel1->setFixedSize(100,20);

    // reference label 2
    referenceLabel2 = new QLabel(this);
    referenceLabel2->move(250,400);
    referenceLabel2->setFixedSize(100,20);

    // start button
    startButton = new QPushButton(this);
    startButton->setText("start");
    startButton->move(250,200);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startComparing);

    // error pop up
    ecpp = new ErrorCoordinatesPopUp("empty");

    // penguin image
    penguin = new ImageWidget(this);
    QImage penguinImage("D:/Qt/Projekti/astrodiff1/pingvin sa teleskopom.png");
    QImage resizedPenguinImage = penguinImage.scaled(100,100);
    penguin->setImage(resizedPenguinImage);
    penguin->move(500,500);
    penguin->setVisible(true);
}

void MainWindow::imageSelector()
{
    QObject* sender = QObject::sender();
    ImageWidget* tempImageWidget = nullptr;
    QLabel* tempLabel = nullptr;
    if(sender == buttonFile1){
        tempImageWidget = imageWidget1;
        tempLabel = file1PathLabel;
        openImageDialog(tempImageWidget, tempLabel);
        image1Selected = true;
    }
    else if (sender == buttonFile2){
        tempImageWidget = imageWidget2;
        tempLabel = file2PathLabel;
        openImageDialog(tempImageWidget, tempLabel);
        image2Selected = true;
    }
    else if(sender == referenceButton1){
        tempImageWidget = imageWidget1;
        tempLabel = referenceLabel1;
        if(image1Selected)
        {
            openImage(tempImageWidget, tempLabel);
        }
    }
    else if(sender == referenceButton2){
        tempImageWidget = imageWidget2;
        tempLabel = referenceLabel2;
        if(image2Selected)
        {
            openImage(tempImageWidget, tempLabel);
        }
    }

}

void MainWindow::startComparing()
{
    Comparator comparator(this->imageWidget1, this->imageWidget2);
    int errorMessage = comparator.checkError();
    if(errorMessage > 0){
        ecpp->setMessage("ERROR: Image " + QString::number(errorMessage) + " refference coordinates are out of bounds! Please select Again.");
        ecpp->setVisible(true);
        ecpp->show();
    }
    comparator.start();
}


void MainWindow::openImageDialog(ImageWidget* imageWidget, QLabel* label)
{
    //error check
    if(imageWidget == nullptr || label == nullptr) return;

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!imagePath.isEmpty()) {
        QImage image(imagePath);
        if (!image.isNull()) {
            imageWidget->setImage(image);
            imageWidget->setPath(imagePath);
        } else {
            qDebug() << "Failed to load the image.";
        }
    }
    label->setText(imagePath);
}

void MainWindow::openImage(ImageWidget* imageWidget, QLabel* label)
{
    //error check
    if(imageWidget == nullptr || label == nullptr) return;
    imageWidget->setReferenceLabelPointer(label);

    imageWidget->setVisible(true);
}

