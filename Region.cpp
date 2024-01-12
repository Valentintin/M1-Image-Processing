#include "Region.hpp"
#include <opencv2/core/matx.hpp>
#include <stack>



Region::Region(Mat * image_, int * indTab_, const Point & germInit, const int & id_, const Vec3b & intensity_, const int & seuil_)  : 
image(image_), germ(germInit), id(id_), intensity(intensity_), seuil(seuil_), indTab(indTab_){
    refused.clear();
    group.push(id);
}

Region::~Region() {

}

std::stack<int> Region::getGroup() {
    return group;
}

Vec3b Region::getIntensity() {
    return intensity;
}

bool Region::compare_color(Vec3b color, const int & seuil_) {
    if (color.val[0] <= intensity.val[0]+seuil_
        && color.val[0] >= intensity.val[0]-seuil_
        && color.val[1] <= intensity.val[1]+seuil_
        && color.val[1] >= intensity.val[1]-seuil_
        && color.val[2] <= intensity.val[2]+seuil_
        && color.val[2] >= intensity.val[2]-seuil_) {
            //std::cout<<"bonne couleur \n";
            return true;
    }
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
        } else {
            group.push(indTab[Pile.top().x * image->size().height + Pile.top().y]);
        }
        Point temp(Pile.top());
        Pile.pop();

        //Y+1
        if (cond_y_sud(temp)) {
            Point Ysud = Point(temp.x, temp.y+1);
            if (cond_color(Ysud)) {
                if (cond_indTab(Ysud)) {
                    Pile.push(Ysud);
                }
            }
            //std::cout<<"cond_y_sud ";
        }

        //Y+1 && X+1
        if (cond_y_sud(temp) && cond_x_est(temp)) {
            Point SudEst = Point(temp.x+1, temp.y+1);
            if (cond_color(SudEst)) {
                if (cond_indTab(SudEst)) {
                    Pile.push(SudEst);
                }
            }
        }

        //Y+1 && X-1
        if (cond_y_sud(temp) && cond_x_ouest(temp)) {
            Point SudOuest = Point(temp.x-1, temp.y+1);
            if (cond_color(SudOuest)) {
                if (cond_indTab(SudOuest)) {
                    Pile.push(SudOuest);
                }
            }
        }

        //Y-1
        if (cond_y_nord(temp)) {
            Point Ynord = Point(temp.x, temp.y-1);
            if (cond_color(Ynord)) {
                if (cond_indTab(Ynord)) {
                    Pile.push(Ynord);
                }
            }
            //std::cout<<"cond_y_nord ";
        }

        //Y-1 && X+1
        if (cond_y_nord(temp) && cond_x_est(temp)) {
            Point NordEst = Point(temp.x+1, temp.y-1);
            if (cond_color(NordEst)) {
                if (cond_indTab(NordEst)) {
                    Pile.push(NordEst);
                }
            }
        }

        //Y-1 && X-1
        if (cond_y_nord(temp) && cond_x_ouest(temp)) {
            Point NordOuest = Point(temp.x-1, temp.y-1);
            if (cond_color(NordOuest)) {
                if (cond_indTab(NordOuest)) {
                    Pile.push(NordOuest);
                }
            }
        }

        //X+1
        if (cond_x_est(temp)) {
            Point Xest = Point(temp.x+1, temp.y);
            if (cond_color(Xest)) {
                if (cond_indTab(Xest)) {
                    Pile.push(Xest);
                }
            }
            //std::cout<<"cond_y_est ";
        }

        //X-1
        if (cond_x_ouest(temp)) {
            Point Xouest = Point(temp.x-1, temp.y);
            if (cond_color(Xouest)) {
                if (cond_indTab(Xouest)) {
                    Pile.push(Xouest);
                }
            }
            //std::cout<<"cond_y_ouest ";
        }
    }
}