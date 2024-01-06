#include "Region.hpp"
#include <iterator>
#include <opencv2/core/hal/interface.h>
#include <set>
#include <iostream>
#include <stack>
#include <opencv2/core/types.hpp>

Region::Region() {

}


Region::Region(Mat * image_, const Point & germInit, const int & id_, const Scalar & intensity_, const int & seuil_)  : 
image(image_), germ(germInit), id(id_), intensity(intensity_), seuil(seuil_){
    refused.clear();
}

Region::~Region() {

}

bool Region::cond_color(const Point & point) {
    Scalar color = image->at<uchar>(point);
    if (color.val[0] >= 0
        && color.val[1] >= 0
        && color.val[2] >= 0
        && color.val[0] <= intensity.val[0]+seuil
        && color.val[0] >= intensity.val[0]-seuil
        && color.val[1] <= intensity.val[1]+seuil
        && color.val[1] >= intensity.val[1]-seuil
        && color.val[2] <= intensity.val[2]+seuil
        && color.val[2] >= intensity.val[2]-seuil) {
            std::cout<<"bonne couleur \n";
            return true;
    }
    return false;
}
    
bool Region::cond_y_sud(const Point & point) {
    if (point.y < image->size().height-1 && point.y >= 0) {
        return true;
    }
    return false;
}
bool Region::cond_y_nord(const Point & point) {
    if (point.y > 0 && point.y < image->size().height) {
        return true;
    }
    return false;
}
bool Region::cond_x_est(const Point & point) {
    if (point.x < image->size().width-1 && point.x >= 0) {
        return true;
    }
    return false;
}
bool Region::cond_x_ouest(const Point & point) {
    if (point.x > 0 && point.x < image->size().width) {
        return true;
    }
    return false;
}







void Region::pathGerm() {
    //pile init avec germ de base
    std::stack<Point> Pile;  
    Pile.push(germ);//empile le cas init
    //auto it = refused.begin();

    std::cout<<"before while ";

    while(!Pile.empty()) {

        //on dépile
        image->at<uchar>(Pile.top().y, Pile.top().x) = -id;
        Point temp(Pile.top());
        Pile.pop();
        std::cout<<"dépile ";

        //Y+1
        if (cond_y_sud(temp)) {
            Point Ysud = Point(temp.y+1, temp.x);
            if (cond_color(Ysud)) {
                Pile.push(Ysud);
            } else {
                refused.emplace_back(Ysud);
            }
            std::cout<<"cond_y_sud ";
        }
        else {
            Point Ysud = Point(temp.y, temp.x);
            if (cond_color(Ysud)) {
                Pile.push(Ysud);
            } else {
                refused.emplace_back(Ysud);
            }
            std::cout<<"point extreme sud ";
        }

        //Y-1
        if (cond_y_nord(temp)) {
            Point Ynord = Point(temp.y-1, temp.x);
            if (cond_color(Ynord)) {
                Pile.push(Ynord);
            } else {
                refused.emplace_back(Ynord);
            }
            std::cout<<"cond_y_nord ";
        }
        else {
            Point Ynord = Point(temp.y, temp.x);
            if (cond_color(Ynord)) {
                Pile.push(Ynord);
            } else {
                refused.emplace_back(Ynord);
            }
            std::cout<<"point extreme nord ";
        }

        //X+1
        if (cond_x_est(temp)) {
            Point Xest = Point(temp.y, temp.x+1);
            if (cond_color(Xest)) {
                Pile.push(Xest);
            } else {
                refused.emplace_back(Xest);
            }
            std::cout<<"cond_y_est ";
        }
        else {
            Point Xest = Point(temp.y, temp.x);
            if (cond_color(Xest)) {
                Pile.push(Xest);
            } else {
                refused.emplace_back(Xest);
            }
            std::cout<<"point extreme est ";
        }

        //X-1
        if (cond_x_ouest(temp)) {
            Point Xouest = Point(temp.y, temp.x-1);
            if (cond_color(Xouest)) {
                Pile.push(Xouest);
            } else {
                refused.emplace_back(Xouest);
            }
            std::cout<<"cond_y_ouest ";
        }
        else {
            Point Xouest = Point(temp.y, temp.x);
            if (cond_color(Xouest)) {
                Pile.push(Xouest);
            } else {
                refused.emplace_back(Xouest);
            }
            std::cout<<"point extreme ouest ";
        }

        //it = std::find(refused.begin(), refused.end(), Ysud);
        
/* 
        //Y+1
        Scalar YnordIntens = image->at<uchar>(temp.y+1, temp.x);
        Point Ynord = Point(temp.y+1, temp.x);
        it = std::find(refused.begin(), refused.end(), Ynord);
        if (it == refused.end() && condition(YnordIntens)) {
            Pile.push(Ynord);
        } else {
            refused.emplace_back(Ynord);
        }

        //X-1
        Scalar XouestIntens = image->at<uchar>(temp.y, temp.x-1);
        Point Xouest = Point(temp.y, temp.x-1);
        it = std::find(refused.begin(), refused.end(), Xouest);
        if (it == refused.end() && condition(XouestIntens)) {
            Pile.push(Xouest);
        } else {
            refused.emplace_back(Xouest);
        }

        //X+1
        Scalar XestIntens = image->at<uchar>(temp.y, temp.x+1);
        Point Xest = Point(temp.y, temp.x+1);
        it = std::find(refused.begin(), refused.end(), Xest);
        if (it == refused.end() && condition(XestIntens)) {
            Pile.push(Xest);
        } else {
            refused.emplace_back(Xest);
        } */
    }
}