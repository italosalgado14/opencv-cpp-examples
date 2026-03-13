/*
 * Content Finder
 */

#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"

int main() {

    cv::Mat image= cv::imread("/home/laila/programacion/C++/openCV/41_histogramColor/000001.png",0);
    if (!image.data) return 0;

    //seleccionar el roi de referencia para segmentar
    cv::Mat imageROI;
    imageROI= image(cv::Rect(293,52,54,148)); //region de interes
    //cv::namedWindow("1Reference");
    //cv::imshow("1Reference",imageROI);

    //histograma en ByN clasico
    Histogram1D h;
    cv::Mat hist= h.getHistogram(imageROI);
    //cv::namedWindow("2Reference Histogram");
    //cv::imshow("2Reference Histogram",h.getHistogramImage(imageROI));

    //segmentacion con histograma en ByN
    ContentFinder finder;
    finder.setHistogram(hist); //normaliza de 0 a 1
    finder.setThreshold(0.20f);
    cv::Mat result1;
    result1 = finder.find(image);

    //resultado intermedio del backproj
    cv::Mat tmp;
    result1.convertTo(tmp,CV_8U,-1.0,255.0);
    //cv::namedWindow("Backprojection result");
    //cv::imshow("Backprojection result",tmp);
    finder.setThreshold(0.12f);
    result1 = finder.find(image);


    cv::rectangle(image, cv::Rect(293,52,54,148), cv::Scalar(0, 0, 0));
    //cv::namedWindow("ImageOriginal");
    //cv::imshow("ImageOriginal",image); //imagen en ByN
    //cv::namedWindow("Detection Result");
    //cv::imshow("Detection Result",result1);

    //------------------------------------------------------


    ColorHistogram hc;
    cv::Mat color= cv::imread("/home/laila/programacion/C++/openCV/41_histogramColor/000001.png");

    //configurar el histograma 3D
    imageROI = color(cv::Rect(293,52,54,148)); // un area
    hc.setSize(8); // 8x8x8
    cv::Mat shist= hc.getHistogram(imageROI);


    finder.setHistogram(shist);
    finder.setThreshold(0.60f);
    result1 = finder.find(color);
    cv::namedWindow("Color Detection Result");
    cv::imshow("Color Detection Result",result1);

    //--------------------------------------------
    //test de el filtro con otra imagen

    cv::Mat color2 = cv::imread("/home/laila/programacion/C++/openCV/41_histogramColor/000050.png");
    cv::namedWindow("Second Image");
    cv::imshow("Second Image",color2);

    cv::Mat result2= finder.find(color2);
    cv::namedWindow("Result color (2)");
    cv::imshow("Result color (2)",result2);

    //obtener el histograma ab
    hc.setSize(256);
    cv::Mat colorhist= hc.getabHistogram(imageROI);
    colorhist.convertTo(tmp,CV_8U,-1.0,255.0);
    cv::namedWindow("ab histogram");
    cv::imshow("ab histogram",tmp);

    //histograma backproj
    finder.setHistogram(colorhist);
    finder.setThreshold(0.05f);
    cv::Mat lab;
    cv::cvtColor(color, lab, cv::COLOR_BGR2Lab);
    int ch[2]={1,2};
    cv::namedWindow("Result ab (1)");
    cv::imshow("Result ab (1)",result1);
    cv::cvtColor(color2, lab, cv::COLOR_BGR2Lab);
    result2= finder.find(lab,0,256.0,ch);
    cv::imshow("Result ab (2)",result2);

    // Draw a rectangle around the reference sky area
    cv::rectangle(color,cv::Rect(293,52,54,148),cv::Scalar(0,0,0));
    cv::namedWindow("Color Image");
    cv::imshow("Color Image",color);


    // Get Hue colour histogram
    hc.setSize(180); // 180 bins
    colorhist= hc.getHueHistogram(imageROI);

    // set histogram to be back-projected
    finder.setHistogram(colorhist);

    // Convert to HSV space
    cv::Mat hsv;
    cv::cvtColor(color, hsv, cv::COLOR_BGR2HSV);

    // Get back-projection of hue histogram
    ch[0]=0;
    result1= finder.find(hsv,160.0f,180.0f,ch);

    cv::namedWindow("Result Hue (1)");
    cv::imshow("Result Hue (1)",result1);

    // Second colour image
    color2= cv::imread("/home/laila/programacion/C++/openCV/41_histogramColor/000050.png");

    // Convert to HSV space
    cv::cvtColor(color2, hsv, cv::COLOR_BGR2HSV);

    // Get back-projection of hue histogram
    result2= finder.find(hsv,0.0f,180.0f,ch);

    cv::namedWindow("Result Hue (2)");
    cv::imshow("Result Hue (2)",result2);

    cv::waitKey();
    return 0;
}
