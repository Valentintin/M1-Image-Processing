#include "Fusion.hpp"
#include <iostream>
#include <cstdlib>


Fusion::Fusion( Mat * image_, int* indTab_, const int & nbRegion_) : fusioned(image_->clone()) , indTab(indTab_), nbRegion(nbRegion_){
    srand(time(nullptr));
}

Fusion::~Fusion() {
    nbRegion = 0;
}

Mat Fusion::getFusion() {
    randomIntensity();
    std::cout<<"he \n";
    for (int x = 0; x<fusioned.cols; x++) {
        for (int y = 0; y<fusioned.rows; y++) {
            if (indTab[x * fusioned.size().height + y] > 0) {
                //std::cout<<indTab[x * fusioned->size().height + y] <<"\n";
                fusioned.at<Vec3b>(Point(x, y)) = randomIntensityTab[indTab[x * fusioned.size().height + y]-1];
            }
        }
    }
    return fusioned;
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