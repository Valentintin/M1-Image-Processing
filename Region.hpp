#ifndef _REGION
#define _REGION
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class Region{
    public:
        /**
         * @brief Construct a default new Region object
         * 
         */
        Region();

        /**
         * @brief Construct a new Region object
         * 
         * @param Region 
         */
        Region(const Mat * image_);

        /**
         * @brief Destroy the Region object
         * 
         */
        ~Region();

        /**
         * @brief find the region, with the path of the Germ.
         * 
         * @param step 
         */
        void pathGerm(const int & step);

    private:
        Mat* image;
        int germeX;
        int germeY;
};


#endif
