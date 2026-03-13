#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram.h"

int main() {
    //leer la imagen en escala de grises
    cv::Mat image= cv::imread("/home/laila/programacion/C++/openCV/40_histogram/apples.png",0);
    if (!image.data) return 0;

    // guardar imagen en escala de grises
    cv::imwrite("/home/laila/programacion/C++/openCV/40_histogram/applesBW.png", image);

    // mostrar la imagen
    cv::namedWindow("Image");
    cv::imshow("Image",image);

    //inicializar histograma
    Histogram1D h;
    cv::Mat histo= h.getHistogram(image); //un array unidimensional con 256 entradas

    //loop sobre cada bin, para ver los valores, como un simple array de 256 entradas
    for (int i=0; i<256; i++){
        cout << "Value " << i << " = " << histo.at<float>(i) << endl;
    }

    //display el histograma como imagen, de manera mas intuitiva
    cv::namedWindow("Histogram");
    cv::imshow("Histogram", h.getHistogramImage(image));

    //-------------------------------------------------------

    //volver a mostrar el histograma con un threshold seleccionado
    cv::Mat hi = h.getHistogramImage(image);
    cv::line(hi, cv::Point(70, 0), cv::Point(70, 255), cv::Scalar(128)); //linea threshold
    cv::namedWindow("Histogram with threshold value");
    cv::imshow("Histogram with threshold value", hi);

    //crear y mostrar el threshold image
    cv::Mat thresholded;
    cv::threshold(image,
                  thresholded,
                  70,
                  255, //valor asignado a los pixels sobre el valor de threshold
                  cv::THRESH_BINARY); //tipo de threshold
    cv::namedWindow("Binary Image");
    cv::imshow("Binary Image",thresholded);
    thresholded = 255 - thresholded;
    cv::imwrite("binary.bmp",thresholded);

    //--------------------------------------------------------
/*
    //haremos el histograma mas plano posible, mas uniformidad para aprovechar los colores
    cv::Mat eq= h.equalize(image);
    cv::namedWindow("Equalized Image");
    cv::imshow("Equalized Image",eq);

    cv::namedWindow("Equalized H");
    cv::imshow("Equalized H",h.getHistogramImage(eq));
*/
    //-----------------------------------------------------
/*

    cv::Mat str= h.stretch(image,0.01f);
    cv::namedWindow("Stretched Image");
    cv::imshow("Stretched Image",str);

    cv::namedWindow("Stretched H");
    cv::imshow("Stretched H",h.getHistogramImage(str));

    //------------------------------------------------------
*/
/*
    cv::Mat lut(1,256,CV_8U); // 1x256 matrix
    for (int i=0; i<256; i++) {
        lut.at<uchar>(i)= 255-i;
    }
    cv::namedWindow("Negative image");
    cv::imshow("Negative image",h.applyLookUp(image,lut)); //aplicamos el cambiaso, llamado a el metodo applylokup
*/
    cv::waitKey();
    return 0;

}
