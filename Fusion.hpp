#ifndef _FUSION
#define _FUSION

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "Region.hpp"

using namespace cv;

class Fusion{
    public:

    private:
        Mat fusioned;
        std::vector<Region> listRegion;
        int nbRegion;
};

#endif