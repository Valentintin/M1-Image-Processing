#ifndef _FUSION
#define _FUSION

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "Region.hpp"

using namespace cv;

class Fusion{
    public:

        /**
         * @brief Construct a new Fusion object.
         * 
         * @param listRegion_ 
         */
        Fusion(std::vector<Region> listRegion_);


        /**
         * @brief function for fusion all region passed in the object.
         * 
         * @return Mat
         */
        Mat getFusion();


    private:
        Mat fusioned;
        std::vector<Region> listRegion;
};

#endif