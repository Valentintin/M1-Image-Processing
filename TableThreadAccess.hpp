#ifndef _TABLETHREADACCESS
#define _TABLETHREADACCESS

#include <mutex>
#include <opencv2/core/types.hpp>
#include <condition_variable>


using namespace std;

/**
 * @brief Monitor for thread safe ressource on the id table
 * 
 */
class TableThreadAccess {

    public:
        /**
         * @brief Construct a new Table Thread Access object
         * 
         * @param imgSize 
         */
        TableThreadAccess(const cv::Size & imgSize);

        /**
         * @brief Destroy the Table Thread Access object
         * 
         */
        ~TableThreadAccess();

        /**
         * @brief set an Id at the point in the Table
         * 
         * @param point 
         */
        void setID(const cv::Point & point, const int & id);

        /**
         * @brief get a Id in the Table
         * 
         * @param point 
         * @return int 
         */
        int getID(const cv::Point & point);


    private:
        int* tableIndexRegion;
        bool* tableBoolAccess;
        int height;
        mutex m;
        condition_variable_any c;
};

#endif