#include "Fusion.hpp"
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <opencv2/core/matx.hpp>
#include <vector>


Fusion::Fusion( Mat * image_, int* indTab_, const std::vector<Region> listRegion_, const int & seuil_) : fusioned(image_->clone()), indTab(indTab_), listRegion(listRegion_), seuil(seuil_) {
    srand(time(nullptr));
}

Fusion::~Fusion() {
}

void Fusion::findColorFusionRec(int ind, std::stack<int> grp, Vec3b randomIntensity, Vec3b referenceColor) {
    if (randomIntensityTab[ind-1] != Vec3b(0, 0, 0)) {
        std::cout<<"stop déjà init "<<ind<<'\n';
        return;
    }
    if ( listRegion[ind-1].compare_color(referenceColor, seuil) ) {
        randomIntensityTab[ind-1] = randomIntensity;
        std::cout<<"région"<<ind<<" coloré \n";
    }
    if (!grp.empty()) {
        int temp = grp.top();
        grp.pop();
        if (!grp.empty()) {
            findColorFusionRec(grp.top(), grp, randomIntensity, referenceColor);
        }
    }
}

void Fusion::findColorFusion() {
    randomIntensityTab.clear();
    randomIntensityTab.reserve(listRegion.size());
    for (int i = 0; i<listRegion.size(); i++) {
        randomIntensityTab[i] = Vec3b(0, 0, 0);
    }
    for (int i = 0; i<listRegion.size(); i++) {
        std::cout<<"\n \n Colorisation de la région "<<i+1<<'\n';
        if (randomIntensityTab[i] == Vec3b(0, 0, 0)) { //color for Ri ins't already affected
            findColorFusionRec(i+1, listRegion[i].getGroup(),
                               randomOneIntensity(), listRegion[i].getIntensity());
        }
    }
} 

Mat Fusion::getFusion() {
    findColorFusion();
    //randomIntensity(); //sans fusion
    std::cout<<"he \n";
    for (int x = 0; x<fusioned.cols; x++) {
        for (int y = 0; y<fusioned.rows; y++) {
            if (indTab[x * fusioned.size().height + y] > 0) { //verify that 
                //std::cout<<indTab[x * fusioned->size().height + y] <<"\n";
                fusioned.at<Vec3b>(Point(x, y)) = randomIntensityTab[indTab[x * fusioned.size().height + y]-1];
            }
        }
    }
    return fusioned;
}

void Fusion::randomIntensity() {
    randomIntensityTab.clear();
    randomIntensityTab.reserve(listRegion.size());
    for (int i = 0; i<listRegion.size(); i++) {
        randomIntensityTab[i] = randomOneIntensity();
    }
}

Vec3b Fusion::randomOneIntensity() {
    int blue = rand() % 255;
    int green = rand() % 255;
    int red = rand() % 255;
    return Vec3b(blue, green, red);
}