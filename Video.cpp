#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap("img/test.avi");

    while (cap.isOpened()) {
        cv::Mat frame;
        bool ret = cap.read(frame);

        if (!ret) {
            std::cout << "Impossible de recevoir la frame (fin du flux ?). Sortie..." << std::endl;
            break;
        }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::imshow("frame", gray);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}