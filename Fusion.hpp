#ifndef _FUSION
#define _FUSION

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;

class Fusion {
    public:

        
        /**
         * @brief Construct a new Fusion object.
         * 
         * @param listRegion_ 
         */
        Fusion(Mat * image_, int* indTab_, const int & nbRegion_);

        /**
         * @brief Destroy the Fusion object
         * 
         */
        ~Fusion();

        /**
         * @brief function for fusion all region passed in the object.
         * 
         * @return Mat
         */
        Mat getFusion();

    private:

        /**
         * @brief give a random color for a region.
         * 
         */
        void randomIntensity();

        std::vector<Vec3b> randomIntensityTab;
        int nbRegion;
        int * indTab;
        Mat fusioned;
};

#endif