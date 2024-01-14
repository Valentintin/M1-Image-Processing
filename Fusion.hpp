#ifndef _FUSION
#define _FUSION

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/matx.hpp>
#include <vector>
#include <stack>
#include "Region.hpp"

using namespace cv;

class Fusion {
    public:

        /**
         * @brief Construct a new Fusion object.
         * 
         * @param listRegion_ 
         */
        Fusion(Mat * image_, int* indTab_, const std::vector<Region> listRegion_, const int & seuil_);

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
        
        std::stack<int> setOfGroup;
    private:

        /**
         * @brief fill the tab with random color .
         * 
         */
        void randomIntensity();

        /**
         * @brief find Recurcive version for fusion Region.
         * 
         * @param ind 
         * @param grp 
         * @param randomIntensity 
         */
        void findColorFusionRec(int ind, std::set<int> grp, Vec3b randomIntensity, Vec3b referenceColor);

        /**
         * @brief call Recurcive fusion.
         * 
         */
        void findColorFusion();

        /**
         * @brief return a random color
         * 
         * @return Vec3b 
         */
        Vec3b randomOneIntensity();
        int seuil;
        std::vector<Vec3b> randomIntensityTab;
        std::vector<Region> listRegion;
        int * indTab;
        Mat fusioned;
};

#endif