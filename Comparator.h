#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "ImageWidget.h"
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

class Comparator{
private:
    ImageWidget* imageWidget1;
    ImageWidget* imageWidget2;
    QImage image1;
    QImage image2;
    int avgImage1R;
    int avgImage1G;
    int avgImage1B;
    int borderImage1N;
    int borderImage1E;
    int borderImage1S;
    int borderImage1W;
    int avgImage2R;
    int avgImage2G;
    int avgImage2B;
    int borderImage2N;
    int borderImage2E;
    int borderImage2S;
    int borderImage2W;
    int maxLightX;
    int maxLightY;
    int alignedPixelImage2X;
    int alignedPixelImage2Y;
    string destinationImagePath;
//    struct pair{
//        int x;
//        int y;
//        pair(int x1, int y1) : x(x1), y(y1){}
//    };

//    vector<pair> brightestPixels;
public:
    Comparator(ImageWidget* iw1, ImageWidget* iw2 ):
        imageWidget1(iw1),
        imageWidget2(iw2),
        image1(imageWidget1->getImage()),
        image2(imageWidget2->getImage()),
        borderImage1N(0),
        borderImage1E(0),
        borderImage1S(0),
        borderImage1W(0)
    {}

    int checkError();

    void start();
private:
    void averageImagePixels();
    void findImageBorders();
    void findMaxLightPixel();
    void findAlignedPixel();
    int makeNewImageAndCopy();
    int averageRGB(QImage*, int, int);
};

#endif // COMPARATOR_H
