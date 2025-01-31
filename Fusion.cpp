#include "Fusion.hpp"
#include "TableThreadAccess.hpp"
#include <iostream>
#include <stack>


Fusion::Fusion( Mat * image_, TableThreadAccess* tableThreadAccess_, const std::vector<Region> listRegion_, const int & seuil_) : fusioned(image_->clone()), tableThreadAccess(tableThreadAccess_), listRegion(listRegion_), seuil(seuil_) {
    srand(time(nullptr));
}

Fusion::~Fusion() {
}

void Fusion::findColorFusion() {
    randomIntensityTab.clear();
    randomIntensityTab.reserve(listRegion.size());
    for (int i = 0; i<listRegion.size(); i++) {
        randomIntensityTab[i] = Vec3b(0, 0, 0);
    }
    for (int i = 0; i<listRegion.size(); i++) {
        // std::cout<<"\n Colorisation de la région "<<i+1<<":    ";
        if (randomIntensityTab[i] == Vec3b(0, 0, 0)) { //color for Ri ins't already affected
            //findColorFusionRec(i+1, listRegion[i].getGroup(), randomOneIntensity(), listRegion[i].getIntensity());
            Vec3b randomIntensity = randomOneIntensity();
            std::stack<std::set<int>> rec;
            rec.push(listRegion[i].getGroup());
            while (!rec.empty()) {
                for (int ind : rec.top()) {
                    if (randomIntensityTab[ind-1] != Vec3b(0, 0, 0)) {
                        // std::cout<<"r"<<ind<<" déjà init,    ";
                    } else if ( listRegion[ind-1].compare_color(listRegion[i].getIntensity(), seuil) ) {
                        randomIntensityTab[ind-1] = randomIntensity;
                        // std::cout<<"r"<<ind<<" coloré,    ";
                        rec.push(listRegion[ind-1].getGroup());
                    } else {
                        // std::cout<<"r"<<ind<<" pas coloré,    ";
                    }
                }
                rec.pop();
            }
        }
    }
}

Mat Fusion::getFusion() {
    findColorFusion();
    //randomIntensity(); //sans fusion
    for (int x = 0; x<fusioned.cols; x++) {
        for (int y = 0; y<fusioned.rows; y++) {
            if (tableThreadAccess->getID(Point(x,y)) > 0) { 
                fusioned.at<Vec3b>(Point(x, y)) = randomIntensityTab[tableThreadAccess->getID(Point(x, y))-1];
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