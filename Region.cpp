#include "Region.hpp"
#include <stack>



Region::Region(Mat * image_, int * indTab_, const Point & germInit, const int & id_, const Vec3b & intensity_, const int & seuil_)  : 
image(image_), germ(germInit), id(id_), intensity(intensity_), seuil(seuil_), indTab(indTab_){
    refused.clear();
}

Region::~Region() {

}

bool Region::cond_color(const Point & point) {
    Vec3b color = image->at<Vec3b>(point);
    if (color.val[0] <= intensity.val[0]+seuil
        && color.val[0] >= intensity.val[0]-seuil
        && color.val[1] <= intensity.val[1]+seuil
        && color.val[1] >= intensity.val[1]-seuil
        && color.val[2] <= intensity.val[2]+seuil
        && color.val[2] >= intensity.val[2]-seuil
        && indTab[point.x * image->size().height + point.y] == 0) {
            //std::cout<<"bonne couleur \n";
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
        }
        Point temp(Pile.top());
        Pile.pop();

        //Y+1
        if (cond_y_sud(temp)) {
            Point Ysud = Point(temp.x, temp.y+1);
            if (cond_color(Ysud)) {
                Pile.push(Ysud);
            }
            //std::cout<<"cond_y_sud ";
        }

        //Y+1 && X+1
        if (cond_y_sud(temp) && cond_x_est(temp)) {
            Point SudEst = Point(temp.x+1, temp.y+1);
            if (cond_color(SudEst)) {
                Pile.push(SudEst);
            }
        }

        //Y+1 && X-1
        if (cond_y_sud(temp) && cond_x_ouest(temp)) {
            Point SudOuest = Point(temp.x-1, temp.y+1);
            if (cond_color(SudOuest)) {
                Pile.push(SudOuest);
            }
        }

        //Y-1
        if (cond_y_nord(temp)) {
            Point Ynord = Point(temp.x, temp.y-1);
            if (cond_color(Ynord)) {
                Pile.push(Ynord);
            }
            //std::cout<<"cond_y_nord ";
        }

        //Y-1 && X+1
        if (cond_y_nord(temp) && cond_x_est(temp)) {
            Point NordEst = Point(temp.x+1, temp.y-1);
            if (cond_color(NordEst)) {
                Pile.push(NordEst);
            }
        }

        //Y-1 && X-1
        if (cond_y_nord(temp) && cond_x_ouest(temp)) {
            Point NordOuest = Point(temp.x-1, temp.y-1);
            if (cond_color(NordOuest)) {
                Pile.push(NordOuest);
            }
        }

        //X+1
        if (cond_x_est(temp)) {
            Point Xest = Point(temp.x+1, temp.y);
            if (cond_color(Xest)) {
                Pile.push(Xest);
            }
            //std::cout<<"cond_y_est ";
        }

        //X-1
        if (cond_x_ouest(temp)) {
            Point Xouest = Point(temp.x-1, temp.y);
            if (cond_color(Xouest)) {
                Pile.push(Xouest);
            }
            //std::cout<<"cond_y_ouest ";
        }
    }
}