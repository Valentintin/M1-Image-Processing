#ifndef _REGION
#define _REGION
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types.hpp>

using namespace cv;

/**
 * @brief permit to find a Region from a germ.
 * 
 */
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
        Region(Mat * image_, const Point & germInit, const int & id_);

        /**
         * @brief Destroy the Region object
         * 
         */
        ~Region();

        /**
         * @brief find the region, with the path of the Germ.
         * 
         */
        void pathGerm();

    private:
        Mat* image;
        Point germ;
        int id;
        int intensity;
};

#endif
