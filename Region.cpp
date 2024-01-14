#include "Region.hpp"
#include <stack>
#include <iostream>



Region::Region(Mat * image_, int * indTab_, const Point & germInit, const int & id_, const Vec3b & intensity_, const int & seuil_)  : 
image(image_), germ(germInit), id(id_), intensity(intensity_), seuil(seuil_), indTab(indTab_){
    refused.clear();
    group.emplace(id);
}

Region::~Region() {

}

std::set<int> Region::getGroup() {
    return group;
}

Vec3b Region::getIntensity() {
    return intensity;
}

bool Region::compare_color(Vec3b color, const int & seuil_) {
    for (int i = 0; i < 3; ++i) {
        if (std::abs(color.val[i] - intensity.val[i]) > seuil) {
            return false;
        }
    }
    return true;
    return false;
}

bool Region::cond_color(const Point & point) {
    Vec3b color = image->at<Vec3b>(point);
    return compare_color(color, seuil);
}

bool Region::cond_indTab(const Point & point) {
    if (indTab[point.x * image->size().height + point.y] == 0) {
        return true;
    }
    return false;
}

bool Region::cond_y_sud(const Point & point) {
    if (point.y < image->size().height-1) {
        return true;
    }
    return false;
}
bool Region::cond_y_nord(const Point & point) {
    if (point.y > 0) {
        return true;
    }
    return false;
}
bool Region::cond_x_est(const Point & point) {
    if (point.x < image->size().width-1) {
        return true;
    }
    return false;
}
bool Region::cond_x_ouest(const Point & point) {
    if (point.x > 0) {
        return true;
    }
    return false;
}

void Region::fillGroup(const Point & point) {
    if (indTab[point.x * image->size().height + point.y] > 0) {
        //std::cout<<"ajout dans grp"<<id<<" de "<<indTab[point.x * image->size().height + point.y]<<'\n';
        group.emplace(indTab[point.x * image->size().height + point.y]);
    }
}

void Region::pathGerm() {
    //pile init avec germ de base
    std::stack<Point> Pile; 
    Pile.push(germ);//empile le cas init

    //std::cout<<"before while ";
    
    while(!Pile.empty()) {

        //on dépile
        //std::cout<<"dépile "<<Pile.top().x<<','<<Pile.top().y<<'\n';
        if (indTab[Pile.top().x * image->size().height + Pile.top().y] == 0) {
            indTab[Pile.top().x * image->size().height + Pile.top().y] = id;
        }
        Point temp(Pile.top());
        Pile.pop();

        //Y+1
        if (cond_y_sud(temp)) {
            Point Ysud = Point(temp.x, temp.y+1);
            if (cond_color(Ysud) && cond_indTab(Ysud)) {
                Pile.push(Ysud);
            } else {
                fillGroup(Ysud);
            }
            //std::cout<<"cond_y_sud ";
        }

        //Y+1 && X+1
        if (cond_y_sud(temp) && cond_x_est(temp)) {
            Point SudEst = Point(temp.x+1, temp.y+1);
            if (cond_color(SudEst) && cond_indTab(SudEst)) {
                Pile.push(SudEst);
            } else {
                fillGroup(SudEst);
            }
        }

        //Y+1 && X-1
        if (cond_y_sud(temp) && cond_x_ouest(temp)) {
            Point SudOuest = Point(temp.x-1, temp.y+1);
            if (cond_color(SudOuest) && cond_indTab(SudOuest)) {
                Pile.push(SudOuest);
            } else {
                fillGroup(SudOuest);
            }
        }

        //Y-1
        if (cond_y_nord(temp)) {
            Point Ynord = Point(temp.x, temp.y-1);
            if (cond_color(Ynord) && cond_indTab(Ynord)) {
                Pile.push(Ynord);
            } else {
                fillGroup(Ynord);
            }
            //std::cout<<"cond_y_nord ";
        }

        //Y-1 && X+1
        if (cond_y_nord(temp) && cond_x_est(temp)) {
            Point NordEst = Point(temp.x+1, temp.y-1);
            if (cond_color(NordEst) && cond_indTab(NordEst)) {
                Pile.push(NordEst);
            } else {
                fillGroup(NordEst);
            }
        }

        //Y-1 && X-1
        if (cond_y_nord(temp) && cond_x_ouest(temp)) {
            Point NordOuest = Point(temp.x-1, temp.y-1);
            if (cond_color(NordOuest) && cond_indTab(NordOuest)) {
                Pile.push(NordOuest);
            } else {
                fillGroup(NordOuest);
            }
        }

        //X+1
        if (cond_x_est(temp)) {
            Point Xest = Point(temp.x+1, temp.y);
            if (cond_color(Xest) && cond_indTab(Xest)) {
                Pile.push(Xest);
            } else {
                fillGroup(Xest);
            }
            //std::cout<<"cond_y_est ";
        }

        //X-1
        if (cond_x_ouest(temp)) {
            Point Xouest = Point(temp.x-1, temp.y);
            if (cond_color(Xouest) && cond_indTab(Xouest)) {
                Pile.push(Xouest);
            } else {
                fillGroup(Xouest);
            }
            //std::cout<<"cond_y_ouest ";
        }
    }
}
