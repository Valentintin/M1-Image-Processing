#include "TableThreadAccess.hpp"
#include <opencv2/core/types.hpp>

TableThreadAccess::TableThreadAccess(const cv::Size & imgSize) {
    tableIndexRegion = new int[imgSize.height*imgSize.width];
    tableBoolAccess = new bool[imgSize.height*imgSize.width];
    for (int i = 0; i<imgSize.height*imgSize.width; i++) {
        tableBoolAccess[i] = false;
    }
    height = imgSize.height;
}

TableThreadAccess::~TableThreadAccess() {
    delete [] tableIndexRegion;
}

void TableThreadAccess::setID(const cv::Point & point, const int & id) {
    unique_lock<mutex> lock(m);
    while (tableBoolAccess[point.x * height + point.y]) {
        c.wait(lock);
    }
    tableBoolAccess[point.x * height + point.y] = true;
    tableIndexRegion[point.x * height + point.y] = id;
    tableBoolAccess[point.x * height + point.y] = false;
    c.notify_all();
}

int TableThreadAccess::getID(const cv::Point & point) {
    unique_lock<mutex> lock(m);
    while (tableBoolAccess[point.x * height + point.y]) {
        c.wait(lock);
    }
    tableBoolAccess[point.x * height + point.y] = true;
    int id = tableIndexRegion[point.x * height + point.y];
    tableBoolAccess[point.x * height + point.y] = false;
    c.notify_all();
    return id;
}