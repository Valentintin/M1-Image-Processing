#include "DivImage.hpp"
#include "Region.hpp"

DivImage::DivImage(const Mat & img, const int & nbDiv_): image(new Mat(img)), nbDiv(nbDiv_) {
    divSize = new Size(image->size().height/sqrt(nbDiv), image->size().width/sqrt(nbDiv));
    listRegion.reserve(nbDiv);
    srand(time(nullptr));
}

DivImage::~DivImage() {
    delete divSize;
    delete image;
    listRegion.clear();
    nbDiv = 0;
}

void DivImage::division() {
    listRegion.clear();
    listRegion.reserve(nbDiv);

    int id = 0;
    for (int x = 0; x<=image->size().width; x = x + divSize->width) {
        for (int y = 0; y<=image->size().height; y = y + divSize->height) {
            Point randomCooDiv = randomPlantGerm(Point(x, y));
            //std::cout<<"init germ at : "<<randomCooDiv<<'\n';
            id++;
            listRegion.emplace_back(Region(image,randomCooDiv, id, image->at<uchar>(y, x), 20));
        }
    }
}

std::vector<Region> DivImage::getListRegion() {
    return listRegion;
}

Point DivImage::randomPlantGerm(Point cooDiv) {
    int randX = rand() % divSize->width + cooDiv.x + cooDiv.x;
    int randY = rand() % divSize->height + cooDiv.y + cooDiv.y;
    return Point(randX, randY);
}
