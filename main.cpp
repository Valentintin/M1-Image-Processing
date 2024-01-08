#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/highgui.hpp>
#include <vector>
#include "DivImage.hpp"
#include "Fusion.hpp"
#include "Region.hpp"

using namespace cv;
int main()
{
    std::string image_path = "img/lena_color.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::cout<<"height : "<<img.size().height<<", width : "<<img.size().width<<'\n';

    DivImage* divImage = new DivImage(&img, 64);

    divImage->division();
    std::vector<Region> listRegion = divImage->getListRegion();

    for (int i = 0; i<listRegion.size(); i++) {
        listRegion[i].pathGerm();
    }

    Fusion* fusion = new Fusion(listRegion, &img);

    std::cout<<"ho \n";
    fusion->getFusion();
    std::cout<<"hoho \n";

    imshow("Display window 2", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    delete divImage;
    delete fusion;
    return 0;
}