#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
int main()
{
    std::string image_path = "img/madame.png";
    Mat img = imread(image_path, IMREAD_COLOR);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in  sudo find / -name "*opencv*"the window
    return 0;
}