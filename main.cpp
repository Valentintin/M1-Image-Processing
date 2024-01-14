#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/highgui.hpp>
#include <vector>
#include "DivImage.hpp"
#include "Fusion.hpp"
#include "Region.hpp"

using namespace cv;

int main()
{
    cv::VideoCapture cap("img/test.avi");

    if (!cap.isOpened()) {
        std::cout << "Erreur lors de l'ouverture de la vidéo." << std::endl;
        return -1;
    }
    std::vector<Mat> imgsVideo;
    int cpmt = 0;
    while (cap.isOpened()) {
        cpmt++;
        cv::Mat frame;
        bool ret = cap.read(frame);

        if (!ret) {
            std::cout << "Impossible de recevoir la frame (fin du flux ?). Sortie..." << std::endl;
            break;
        }

        cv::Mat imgVideo;
        cv::cvtColor(frame, imgVideo, cv::COLOR_BGRA2BGR);
        if(cpmt%15==0) {
            int seuil = 40;
            DivImage* divImage = new DivImage(&imgVideo, 528, seuil);

            int* indTab = new int[imgVideo.size().height * imgVideo.size().width]{0};

            divImage->division(indTab);
            std::vector<Region> listRegion = divImage->getListRegion();
            for (int i = 0; i<listRegion.size(); i++) {
                listRegion[i].pathGerm();
            }

            Fusion* fusion = new Fusion(&imgVideo, indTab, listRegion, seuil);

            Mat img2 = fusion->getFusion();

            cv::imshow("frame", img2);

            if (cv::waitKey(1) == 'q') {
                break;
            }

            delete divImage;
            delete fusion;
            delete [] indTab;
        }
    }

    cap.release();
    cv::destroyAllWindows();
/*     std::string image_path = "img/t1.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    std::cout<<"height : "<<img.size().height<<", width : "<<img.size().width<<'\n';

    int seuil = 40;
    DivImage* divImage = new DivImage(&img, 124, seuil);

    int* indTab = new int[img.size().height * img.size().width]{0};

    divImage->division(indTab);
    std::vector<Region> listRegion = divImage->getListRegion();
    for (int i = 0; i<listRegion.size(); i++) {
        listRegion[i].pathGerm();
    }

    Fusion* fusion = new Fusion(&img, indTab, listRegion, seuil);

    std::cout<<"ho \n";
    Mat img2 = fusion->getFusion();
    std::cout<<"hoho \n";

    imshow("Display window", img);
    imshow("Display window 2", img2);
    imwrite( "img/out.jpg", img2 );
    int k = waitKey(0); // Wait for a keystroke in the window 
    delete divImage;
    delete fusion;
    delete [] indTab;
*/
    return 0;
}
