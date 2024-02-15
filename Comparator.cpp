#include "Comparator.h"

int Comparator::checkError()
{
    int width;
    int height;

    // Check first image
    width = image1.size().width();
    height = image1.size().height();

    if(imageWidget1->getReferenceX() >= width || imageWidget1->getReferenceY() >= height){
        return 1;
    }

    // Check second image
    width = image2.size().width();
    height = image2.size().height();

    if(imageWidget2->getReferenceX() >= width || imageWidget2->getReferenceY() >= height){
        return 2;
    }

    return 0;
}

void Comparator::start()
{
    // Find average colors of all pixels in image1 and image2
    averageImagePixels();

    // Find the rectangle which has the reference object for both images
    findImageBorders();

    // Find approximate center of an object in image 1
    findMaxLightPixel();

    // Find the corresponding pixel in image2
    findAlignedPixel();

    // Make a result image
    if(makeNewImageAndCopy() < 0){
        return;
    }
}

void Comparator::averageImagePixels()
{

    for(int k = 1; k <=2; k ++){
        QImage* image = (k==1)? &image1:&image2;
        int* avgR = (k==1)? &avgImage1R:&avgImage2R;
        int* avgG = (k==1)? &avgImage1G:&avgImage2G;
        int* avgB = (k==1)? &avgImage1B:&avgImage2B;
        int width = image->size().width();
        int height = image->size().height();

        for(int i = 0; i < height; i ++){
            for(int j = 0; j < width; j++){
                *avgR += qGreen(image->pixel(j,i));
                *avgG += qRed(image->pixel(j,i));
                *avgB += qBlue(image->pixel(j,i));
            }
        }

        *avgR /= (width * height);
        *avgG /= (width * height);
        *avgB /= (width * height);
    }

}

void Comparator::findImageBorders()
{
    for(int k = 1; k <=2; k ++){

        ImageWidget* imageWidget = (k==1)? imageWidget1:imageWidget2;
        QImage* image = (k==1)? &image1:&image2;
        int avgR = (k==1)? avgImage1R:avgImage2R;
        int avgG = (k==1)? avgImage1G:avgImage2G;
        int avgB = (k==1)? avgImage1B:avgImage2B;
        int* borderImageE = (k==1)? &borderImage1E:&borderImage2E;
        int* borderImageW = (k==1)? &borderImage1W:&borderImage2W;
        int* borderImageN = (k==1)? &borderImage1N:&borderImage2N;
        int* borderImageS = (k==1)? &borderImage1S:&borderImage2S;

        int referenceX = imageWidget->getReferenceX();
        int referenceY = imageWidget->getReferenceY();
        int average = (avgR + avgG + avgB) / 3;
        int averageTemp = 0;


        // East
        for(int i = referenceX; i < image->size().width(); i ++){
            averageTemp = averageRGB(image,i,referenceY);
            if(averageTemp < average){
                *borderImageE = i;
                break;
            }
        }

        // West
        for(int i = referenceX; i >= 0; i --){
            averageTemp = averageRGB(image,i,referenceY);
            if(averageTemp < average){
                *borderImageW = i;
                break;
            }
        }

        // North
        for(int i = referenceY; i >= 0; i --){
            averageTemp = averageRGB(image, referenceX, i);
            if(averageTemp < average){
                *borderImageN = i;
                break;
            }
        }

        // South
        for(int i = referenceY; i < image->size().height(); i ++){
            averageTemp = averageRGB(image, referenceX, i);
            if(averageTemp < average){
                *borderImageS = i;
                break;
            }
        }

        if(*borderImageE == 0 || *borderImageN == 0 || *borderImageS == 0 || *borderImageW == 0){
            // Greska
        }

    }

}

void Comparator::findMaxLightPixel()
{
    int maxAverage = 0;
    int tempAverage = 0;

    // Traverse through rectangle of the refference object and find the maximum-light pixel

    for(int i = borderImage1N; i <= borderImage1S; i++){
        for(int j = borderImage1W; j <= borderImage1E; j ++ ){
            tempAverage = averageRGB(&image1, j, i);
            if( tempAverage > maxAverage){
                maxAverage = tempAverage;
                maxLightX = j;
                maxLightY = i;

            }
        }
    }

}

void Comparator::findAlignedPixel()
{
    int tempDifference = 0;
    int maxDifference = 0;

    for(int i = borderImage2N; i <= borderImage2S; i++){
        for(int j = borderImage2W; j <= borderImage2E; j ++ ){
            tempDifference = abs( qRed(image2.pixel(j,i)) - qRed(image1.pixel(maxLightX, maxLightY)) )
                                + abs( qGreen(image2.pixel(j,i)) - qGreen(image1.pixel(maxLightX, maxLightY)) )
                                    + abs( qBlue(image2.pixel(j,i)) - qBlue(image1.pixel(maxLightX, maxLightY)) );
            if(tempDifference > maxDifference){
                alignedPixelImage2X = j;
                alignedPixelImage2Y = i;
            }
        }
    }

}

int Comparator::makeNewImageAndCopy()
{
    string extension;
    int dotIndex = 0;
    // Specify the paths for the source and destination images
    string sourceImagePath = imageWidget1->getPath().toStdString();
    for(int i = sourceImagePath.size() - 1; i >= 0; i --){
        if(sourceImagePath[i] == '.'){
            extension = sourceImagePath.substr( i+1, sourceImagePath.size() - 1 - i);
            dotIndex = i;
            break;
        }
    }
    destinationImagePath = sourceImagePath.substr( 0, dotIndex) + "DIFFERENTIATED." + extension;

    // Open the source image file for binary reading
    std::ifstream sourceFile(sourceImagePath, std::ios::binary);

    // Check if the source file is open
    if (!sourceFile.is_open()) {
        std::cerr << "Error opening source file for reading" << std::endl;
        return -1;
    }

    // Open the destination image file for binary writing
    std::ofstream destinationFile(destinationImagePath, std::ios::binary);

    // Check if the destination file is open
    if (!destinationFile.is_open()) {
        std::cerr << "Error opening destination file for writing" << std::endl;
        sourceFile.close(); // Close the source file
        return -1;
    }

    // Copy the contents of the source file to the destination file
    destinationFile << sourceFile.rdbuf();

    // Check if the copy operation was successful
    if (!destinationFile) {
        std::cerr << "Error copying file contents" << std::endl;
    } else {
        std::cout << "Image copy successful" << std::endl;
    }

    // Close the files
    sourceFile.close();
    destinationFile.close();

    return 0;

}

int Comparator::averageRGB(QImage* image, int x, int y)
{
    return ( qGreen(image->pixel(x,y)) + qRed(image->pixel(x,y)) + qBlue(image->pixel(x,y)) ) / 3;
}
