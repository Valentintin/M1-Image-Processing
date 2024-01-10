#include "DivImage.hpp"
#include "Region.hpp"
#include <opencv2/core/matx.hpp>

DivImage::DivImage(Mat * img, const int & nbDiv_): image(img), nbDiv(nbDiv_) {
    divSize = new Size(image->rows/sqrt(nbDiv), image->cols/sqrt(nbDiv));
    listRegion.reserve(nbDiv);
    srand(time(nullptr));
}

DivImage::~DivImage() {
    delete divSize;
    listRegion.clear();
    nbDiv = 0;
}

void DivImage::division(int* indTab) {
    listRegion.clear();
    listRegion.reserve(nbDiv);
    int id = 0;
    for (int x = 0; x + divSize->height <= image->cols; x = x + divSize->height) {
        for (int y = 0; y + divSize->width <= image->rows; y = y + divSize->width) {
            Point randomCooDiv = randomPlantGerm(Point(x, y));
            std::cout<<"init germ at : "<<randomCooDiv<<'\n';
            id++;
            listRegion.emplace_back(Region(image,indTab, randomCooDiv, id, image->at<Vec3b>(Point(x, y)), 40));
        }
    }
}

std::vector<Region> DivImage::getListRegion() {
    return listRegion;
}

Point DivImage::randomPlantGerm(Point cooDiv) {
    int randX = rand() % (divSize->height);
    int randY = rand() % (divSize->width);
    return Point(randX + cooDiv.x, randY + cooDiv.y);
}
