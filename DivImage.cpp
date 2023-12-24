#include "DivImage.hpp"
#include "Region.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <vector>



DivImage::~DivImage() {
    listRegion.clear();
    nbDiv = 0;
}

void DivImage::division() {
    // trouve la taille d'une Image = racine du nombre de région

    //initialise la région avec la taille et les coordonnées pour les n divisions.

    //tailleXdiv et tailleYdiv  = tailleImg(X/Y) / sqrt(nbDiv)
    Size DivSize(image.size().height/sqrt(nbDiv), image.size().width/sqrt(nbDiv));
    std::cout<<"height : "<<DivSize.height<<'\n';
    std::cout<<"width : "<<DivSize.width<<'\n';

    //Pour i parcourrant tailleXimg par pas de tailleXdiv:
        //pour j parcourrant tailleYimg par pas de tailleYDiv:
            //ajouter région à list
            //l'initialiser avec image, coordonné i, j, taille(X/Y)Div
    
}

std::vector<Region> DivImage::getListRegion() {
    return listRegion;
}
