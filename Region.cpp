#include "Region.hpp"

Region(const Mat *image_) {
    image = image_;
    germeX = 0;
    germeY = 0;
}

~Region() {
    delete image;
    germeX = 0;
    germeY = 0;
}

void pathGerm(const int & step) {
    traverseX = germeX;
    traverseY = germeY;
    
    while()
}