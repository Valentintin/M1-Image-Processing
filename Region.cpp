#include "Region.hpp"

Region::Region() {

}

Region::Region(Mat * image_, const Point & germInit, const int & id_): image(image_), germ(germInit), id(id_){}

Region::~Region() {

}

void Region::pathGerm() {

}