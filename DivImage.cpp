#include "DivImage.hpp"
#include "Region.hpp"
#include <vector>

DivImage::DivImage(Mat * img, const int & nbDiv_) {
    image = img;
    nbDiv = nbDiv_;
    listRegion = std::vector<Region>(nbDiv);
}

DivImage::~DivImage() {
    delete image;
    listRegion.clear();
    nbDiv = 0;
}

void DivImage::division() {
    // trouve la taille d'une Image = racine du nombre de région

    //initialise la région avec la taille et les coordonnées pour les n divisions.

    //tailleXdiv et tailleYdiv  = tailleImg(X/Y) / sqrt(Tailleimage(X/Y))

    //Pour i parcourrant tailleXimg par pas de tailleXdiv:
        //pour j parcourrant tailleYimg par pas de tailleYDiv:
            //ajouter région à list
            //l'initialiser avec image, coordonné i, j, taille(X/Y)Div
}

std::vector<Region> DivImage::getListRegion() {
    return listRegion;
}
