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

    DivImage* divImage = new DivImage(img, 9);

    divImage->division();
    std::vector<Region> listRegion = divImage->getListRegion();

    

    //imshow("Display window", img);
    //int k = waitKey(0); // Wait for a keystroke in the window

    delete divImage;
    return 0;
}