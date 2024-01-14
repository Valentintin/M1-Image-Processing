#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/highgui.hpp>
#include <vector>
#include "DivImage.hpp"
#include "Fusion.hpp"
#include "Region.hpp"
#include "TableThreadAccess.hpp"

using namespace cv;

int main()
{
    std::string image_path = "img/t1.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::cout<<"height : "<<img.size().height<<", width : "<<img.size().width<<'\n';

    int seuil = 40;
    DivImage* divImage = new DivImage(&img, 124, seuil);

    int* indTab = new int[img.size().height * img.size().width]();

    TableThreadAccess* tableThreadAccess = new TableThreadAccess(img.size());

    divImage->division(tableThreadAccess);
    std::vector<Region> listRegion = divImage->getListRegion();
    for (int i = 0; i<listRegion.size(); i++) {
        listRegion[i].pathGerm();
    }

    Fusion* fusion = new Fusion(&img, tableThreadAccess, listRegion, seuil);

    std::cout<<"ho \n";
    Mat img2 = fusion->getFusion();
    std::cout<<"hoho \n";

    imshow("Display window", img);
    imshow("Display window 2", img2);
    imwrite( "img/out.jpg", img2 );
    int k = waitKey(0); // Wait for a keystroke in the window
    delete divImage;
    delete fusion;
    delete [] indTab;
    delete tableThreadAccess;
    return 0;
}