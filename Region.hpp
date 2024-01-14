#ifndef _REGION
#define _REGION
#include "TableThreadAccess.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/types.hpp>
#include <set>
#include <vector>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>

using namespace cv;

/**
 * @brief permit to find a Region from a germ.
 * 
 */
class Region{
    public:

        /**
         * @brief Construct a new Region object
         * 
         * @param Region 
         */
        Region(Mat * image_, TableThreadAccess* tableThreadAccess_, const Point & germInit, const int & id_, const Vec3b & intensity_, const int & seuil_);

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

        /**
         * @brief Get the Group object
         * 
         * @return std::set<int> 
         */
        std::set<int> getGroup();

        /**
         * @brief Get the Intensity object
         * 
         * @return Vec3b 
         */
        Vec3b getIntensity();

        /**
         * @brief compare the current intensity with the color pass in parameter.
         * 
         * @param color 
         * @param seuil 
         * @return true 
         * @return false 
         */
        bool compare_color(Vec3b color, const int & seuil);
        
    private:
        /**
         * @brief verify that the color is near from the intensity.
         * 
         * @return true 
         * @return false 
         */
        bool cond_color(const Point & point);
        /**
         * @brief verify that the case ins't already marked
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        bool cond_indTab(const Point & point);
        /**
         * @brief verify that the point is in the shape
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        bool cond_x_est(const Point & point);
        /**
         * @brief verify that the point is in the shape
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        bool cond_x_ouest(const Point & point);
        /**
         * @brief verify that the point is in the shape
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        bool cond_y_sud(const Point & point);
        /**
         * @brief verify that the point is in the shape
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        bool cond_y_nord(const Point & point);
        /**
         * @brief fill the group of neight
         * 
         * @param point 
         */
        void fillGroup(const Point & point);

        Point germ;
        Mat* image;
        int id;
        TableThreadAccess* tableThreadAccess;
        int seuil;
        Vec3b intensity; //couleur de germe initial
        std::set<int> group;
};

#endif
