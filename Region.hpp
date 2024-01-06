#ifndef _REGION
#define _REGION
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types.hpp>
#include <vector>

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
        Region(Mat * image_, const Point & germInit, const int & id_, const Scalar & intensity_, const int & seuil_);

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
        
        int id;

    private:
        /**
         * @brief verify that the color is near from the intensity.
         * 
         * @return true 
         * @return false 
         */
        bool cond_color(const Point & point);

        bool cond_x_sud(const Point & point);
        bool cond_x_nord(const Point & point);        
        bool cond_y_sud(const Point & point);
        bool cond_y_nord(const Point & point);
        Mat* image;
        Point germ;
        std::vector<Point> refused;
        int seuil;
        Scalar intensity; //couleur de germe initial
};

#endif
