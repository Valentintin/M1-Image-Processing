#include "Region.hpp"

Region::Region() {

}

Region::Region(Mat * image_, const Point & germInit): image(image_), germ(germInit){}

Region::~Region() {

}

void Region::pathGerm(const int & step) {

}