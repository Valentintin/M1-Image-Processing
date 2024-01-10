#include "Fusion.hpp"
#include <cstdlib>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>

Fusion::Fusion( Mat * image_, int* indTab_, const int & nbRegion_) : fusioned(image_) , indTab(indTab_), nbRegion(nbRegion_){
    srand(time(nullptr));
}

Fusion::~Fusion() {
    delete [] indTab;
    nbRegion = 0;
}

Mat Fusion::getFusion() {
    //randomIntensity();
    std::cout<<"he \n";
    for (int x = 0; x<fusioned->size().width; x++) {
        for (int y = 0; y<fusioned->size().height; y++) {
            if (indTab[x * fusioned->size().height + y] > 0) {
                std::cout<<"heeee \n";
                fusioned->at<Vec3b>(y, x) = Vec3b(0, 255, 0);
            }
        }
    }
    return *fusioned;
}

void Fusion::randomIntensity() {
    randomIntensityTab.clear();
    randomIntensityTab.reserve(nbRegion);
    for (int i = 0; i<nbRegion; i++) {
        int blue = rand() % 255;
        int green = rand() % 255;
        int red = rand() % 255;
        randomIntensityTab[i] = Vec3b(blue, green, red);
    }
}