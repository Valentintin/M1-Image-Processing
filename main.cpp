#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "DivImage.hpp"
#include "Region.hpp"

using namespace cv;
int main()
{
    std::string image_path = "img/madame.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::cout<<"height : "<<img.size().height<<", width : "<<img.size().width<<'\n';

    DivImage* divImage = new DivImage(img, 9);

    divImage->division();
    std::vector<Region> listRegion = divImage->getListRegion();

    //listRegion[0].pathGerm();
    for (int i = 0; i<listRegion.size(); i++) {
        std::cout<<listRegion[i].id<<'\n';
        listRegion[i].pathGerm();
    }

    

    //imshow("Display window", img);
    //int k = waitKey(0); // Wait for a keystroke in the window

    delete divImage;
    return 0;
}