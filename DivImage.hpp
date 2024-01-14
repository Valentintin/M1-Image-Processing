#ifndef _DIVIMAGE
#define _DIVIMAGE

#include "Region.hpp"
#include "TableThreadAccess.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <opencv2/core/matx.hpp>

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
        DivImage(Mat * img, const int & nbDiv_, const int & seuil_);

        /**
         * @brief Destroy the Div Region object
         * 
         */
        ~DivImage();

        /**
         * @brief divise the image in n for create Region
         * 
         */
        void division(TableThreadAccess* tableThreadAccess);

        /**
         * @brief Get the List Region object
         * 
         * @return std::vector<Region> 
         */
        std::vector<Region> getListRegion();

        Mat* image;
    private:

        /**
         * @brief find a random point in the array.
         * 
         * @param cooDiv 
         * @return Point 
         */
        Point randomPlantGerm(Point cooDiv);
        Size* divSize;
        std::vector<Region> listRegion;
        int seuil;
        int nbDiv;
};

#endif