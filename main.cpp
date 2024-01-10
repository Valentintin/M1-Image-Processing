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

    int* indTab = new int[img.size().height * img.size().width]{0};

    divImage->division(indTab);
    std::vector<Region> listRegion = divImage->getListRegion();

    for (int i = 0; i<listRegion.size(); i++) {
        listRegion[i].pathGerm();
    }

    Fusion* fusion = new Fusion(&img, indTab, listRegion.size());

    std::cout<<"ho \n";
    Mat img2 = fusion->getFusion();
    std::cout<<"hoho \n";

    imshow("Display window 2", img2);
    int k = waitKey(0); // Wait for a keystroke in the window
    delete divImage;
    delete [] indTab;
    //delete fusion;
    return 0;
}