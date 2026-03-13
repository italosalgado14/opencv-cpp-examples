#include <iostream>
#include <opencv2/core/core.hpp> //core functionalities
#include <opencv2/highgui.hpp>

int main() {

    cv::namedWindow("Image");
    cv::Mat image = cv::imread("/home/laila/programacion/C++/openCV/4_ROI/mundo.png");
    cv::Mat logo = cv::imread("/home/laila/programacion/C++/openCV/4_ROI/pessoa.jpg");


    //Con la funcion Rect definimos el ROI
    cv::Mat imageROI(image, cv::Rect(image.cols-logo.cols, image.rows-logo.rows, logo.cols, logo.rows));
    logo.copyTo(imageROI);

    cv::imshow("Image", image);
    cv::waitKey(0);
}
