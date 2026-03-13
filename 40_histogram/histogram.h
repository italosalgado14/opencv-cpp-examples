//
// Created by laila on 11-05-21.
//


//#ifndef INC_40_HISTOGRAM_HISTOGRAM_H
#if !defined HISTOGRAM

//#define INC_40_HISTOGRAM_HISTOGRAM_H
#define HISTOGRAM


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

//histogramas para imagenes en blanco y negro
class Histogram1D {
private:
    int histSize[1]; //numero de bins en histograma
    float hranges[2]; //rango de los valores
    const float* ranges[1]; //puntero para guardar los dos valores limites hranges
    int channels[1]; //numero de channels a ser examinados

public:
    //constructor
    Histogram1D(){
        histSize[0]= 256; //256 bins
        hranges[0]= 0.0; // desde el 0
        hranges[1]= 256.0; //hasta el 256
        ranges[0]= hranges; //asignamos el puntero a los dos limites
        channels[0]= 0; //vamos a mirar el channel 0
    }

    // setear el channel a desplegar en el histograma
    void setChannel(int c) {
        channels[0]= c;
    }

    //obtener el channel en uso actual
    int getChannel() {
        return channels[0];
    }

    //setear el rango para los valores de los pixeles
    void setRange(float minValue, float maxValue) {
        hranges[0]= minValue;
        hranges[1]= maxValue;
    }

    //obtener el minimo valor de los pixeles
    float getMinValue() {
        return hranges[0];
    }

    //obtener el maximo valor de los pixeles
    float getMaxValue() {
        return hranges[1];
    }

    //setear el numero de bins en el histograma
    void setNBins(int nbins) {
        histSize[0]= nbins;
    }

    //obtener el numero de beans en el histograma
    int getNBins() {
        return histSize[0];
    }

    // computa el histograma 1D
    cv::Mat getHistogram(const cv::Mat &image) {
        cv::Mat hist;
        cv::calcHist(&image,
                     1,
                     channels,
                     cv::Mat(),
                     hist,
                     1,
                     histSize,
                     ranges);
        return hist;
    };

    //computa el histograma 1D, y ademas retorna una imagen este
    cv::Mat getHistogramImage(const cv::Mat &image, int zoom = 1){
        cv::Mat hist = getHistogram(image);
        return Histogram1D::getImageOfHistogram(hist, zoom);
    }

    //estira la imagen de origen utilizando el numero minimo de count de bins
    cv::Mat stretch(const cv::Mat &image, int minValue = 0) {
        cv::Mat hist = getHistogram(image);
        int imin = 0;

        //aqui encontraremos el bin donde debemos practicar el corte para estrechar
        //el histograma: recorremos el histograma hasta lograr encontrar el valor mayor/menor
        //a el min/max value
        for (; imin < histSize[0]; imin++) {
            if (hist.at<float>(imin) > minValue) break; //ignorar bins con menos de minValue
        }
        int imax = histSize[0] - 1;
        for (; imax >= 0; imax--) {
            if (hist.at<float>(imax) > minValue) break;
        }

        // creamos la matriz que funcionara como lookup, la llenamos de 0s al inicio
        //y al final, luego aplicamos la transformacion lineal a los sobrevivientes para
        //lograr el rango de 0 a 255 en el subconjunto
        int dims[1] = { 256 };
        cv::Mat lookup(1, dims, CV_8U);
        for (int i = 0; i<256; i++) {
            if (i < imin) lookup.at<uchar>(i) = 0;
            else if (i > imax) lookup.at<uchar>(i) = 255;
            else lookup.at<uchar>(i) = cvRound(255.0*(i - imin) / (imax - imin));
        }

        //finalmente aplicamos el lookup
        cv::Mat result;
        result = applyLookUp(image, lookup);
        return result;
    }
    // tambien estrecha la imagen, pero en un porcentaje
    cv::Mat stretch(const cv::Mat &image, float percentile) {
        float number= image.total()*percentile;
        cv::Mat hist = getHistogram(image);
        int imin = 0;
        for (float count=0.0; imin < 256; imin++) {
            if ((count+=hist.at<float>(imin)) >= number) break;
        }

        int imax = 255;
        for (float count=0.0; imax >= 0; imax--) {
            if ((count += hist.at<float>(imax)) >= number) break;
        }

        int dims[1] = { 256 };
        cv::Mat lookup(1, dims, CV_8U);
        for (int i = 0; i<256; i++) {
            if (i < imin) lookup.at<uchar>(i) = 0;
            else if (i > imax) lookup.at<uchar>(i) = 255;
            else lookup.at<uchar>(i) = cvRound(255.0*(i - imin) / (imax - imin));
        }

        cv::Mat result;
        result = applyLookUp(image, lookup);
        return result;
    }

    //STATIC
    //Un método estático es lo más parecido a lo que son las funciones en los lenguajes estructurados
    // Crea una imagen que representa un histograma
    static cv::Mat getImageOfHistogram(const cv::Mat &hist, int zoom) {
        // obtener el min y el max valor de los bins
        double maxVal = 0;
        double minVal = 0;
        cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

        //iniciar una imagen cuadrada en la que mostrar el histograma
        int histSize = hist.rows;
        cv::Mat histImg(histSize*zoom, histSize*zoom, CV_8U, cv::Scalar(255));

        //
        int hpt = static_cast<int>(0.9*histSize);
        for (int h = 0; h < histSize; h++) {
            float binVal = hist.at<float>(h); //util en 1, 2 o 3 dimensiones por metodo at
            if (binVal>0) {
                int intensity = static_cast<int>(binVal*hpt / maxVal);
                cv::line(histImg,
                         cv::Point(h*zoom, histSize*zoom),
                         cv::Point(h*zoom, (histSize - intensity)*zoom),
                         cv::Scalar(0),
                         zoom);
            }
        }
        return histImg;
    }

    //
    static cv::Mat equalize(const cv::Mat &image) {
        cv::Mat result;
        cv::equalizeHist(image,result);
        return result;
    }

    //modificador de pixeles de la misma forma. lookup es una 1x256 uchar matrix
    static cv::Mat applyLookUp(const cv::Mat& image, const cv::Mat& lookup) {
        cv::Mat result;
        cv::LUT(image,lookup,result);
        return result;
    }
    static cv::Mat applyLookUpWithIterator(const cv::Mat& image, const cv::Mat& lookup) {
        cv::Mat result(image.rows,image.cols,CV_8U);
        cv::Mat_<uchar>::iterator itr= result.begin<uchar>();

        cv::Mat_<uchar>::const_iterator it= image.begin<uchar>();
        cv::Mat_<uchar>::const_iterator itend= image.end<uchar>();

        for ( ; it!= itend; ++it, ++itr) {
            *itr= lookup.at<uchar>(*it);
        }
        return result;
    }


};



#endif //HISTOGRAM
