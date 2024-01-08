#include "Fusion.hpp"
#include <cstdlib>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>

Fusion::Fusion(std::vector<Region> listRegion_, Mat * image_) : listRegion(listRegion_), fusioned(image_) {
        srand(time(nullptr));
}

void Fusion::getFusion() {
    randomIntensity();
    for (int x = 0; x<fusioned->size().width; x++) {
        for (int y = 0; y<fusioned->size().height; y++) {
            fusioned->at<Scalar>(y, x) = randomIntensityTab[-fusioned->at<int>(y, x)];
        }
    }
}

void Fusion::randomIntensity() {
    randomIntensityTab.clear();
    randomIntensityTab.reserve(listRegion.size());
    for (int i = 0; i<listRegion.size(); i++) {
        int blue = rand() % 255;
        int green = rand() % 255;
        int red = rand() % 255;
        randomIntensityTab[i] = Scalar(blue, green, red);
    }
}