#ifndef _DIVIMAGE
#define _DIVIMAGE

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "Region.hpp"

using namespace cv;

/**
 * @brief permit to put germs on image with high coverage.
 * 
 */
class DivImage {
    public:
    
        /**
         * @brief Construct a new Div Region object
         * 
         * @param img 
         * @param nbDiv_ 
         */
        DivImage(Mat * img, const int & nbDiv_);

        /**
         * @brief Destroy the Div Region object
         * 
         */
        ~DivImage();

        /**
         * @brief divise the image in n for create Region
         * 
         */
        void division();

        /**
         * @brief Get the List Region object
         * 
         * @return std::vector<Region> 
         */
        std::vector<Region> getListRegion();




    private:
        Mat* image;
        std::vector<Region> listRegion;
        int nbDiv;
};

#endif