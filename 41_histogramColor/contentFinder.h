//
// Created by laila on 11-05-21.
//

#if !defined OFINDER
#define OFINDER


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/*
 * Multidim histogram son proyectados en una imagen
 */

class ContentFinder {
private:
    float hranges[2];
    const float* ranges[3];
    int channels[3];

    float threshold;           // decision threshold
    cv::Mat histogram;         //el histograma puede ser sparse o no
    cv::SparseMat shistogram;
    bool isSparse;

public:

    //el constructor de la clase
    ContentFinder() : threshold(0.1f), isSparse(false) {
        ranges[0]= hranges; //igual rango para BGR
        ranges[1]= hranges;
        ranges[2]= hranges;
    }

    // Sets the threshold on histogram values [0,1]
    void setThreshold(float t) {
        threshold= t;
    }
    // Gets the threshold
    float getThreshold() {
        return threshold;
    }
    void setHistogram(const cv::Mat& h) {
        isSparse= false;
        cv::normalize(h,histogram,1.0); //normalizacion histograma de 0 a 1 si no esta sparse
    }
    // Sets the reference histogram
    void setHistogram(const cv::SparseMat& h) {

        isSparse= true;
        cv::normalize(h,shistogram,1.0,cv::NORM_L2);
    }

    // Simplified version in which all channels used, with range [0,256[
    cv::Mat find(const cv::Mat& image) {
        cv::Mat result;

        hranges[0]= 0.0;	// default range [0,256[
        hranges[1]= 256.0;
        channels[0]= 0;		// the three channels
        channels[1]= 1;
        channels[2]= 2;

        return find(image, hranges[0], hranges[1], channels);
    }

    // Finds the pixels belonging to the histogram
    cv::Mat find(const cv::Mat& image, float minValue, float maxValue, int *channels) {

        cv::Mat result;

        hranges[0]= minValue;
        hranges[1]= maxValue;

        if (isSparse) { // call the right function based on histogram type

            for (int i=0; i<shistogram.dims(); i++)
                this->channels[i]= channels[i];

            cv::calcBackProject(&image,
                                1,            // una sola imagen al mismo tiempo
                                channels,     //vector que especifica qué dimensiones del histograma pertenecen a qué canales de imagen
                                shistogram,   // the histogram we are using
                                result,       // the resulting back projection image
                                ranges,       // the range of values, for each dimension
                                255.0         // the scaling factor is chosen such that a histogram value of 1 maps to 255
            );

        } else {

            for (int i=0; i<histogram.dims; i++)
                this->channels[i]= channels[i];

            cv::calcBackProject(&image,
                                1,            // we only use one image at a time
                                channels,     // vector specifying what histogram dimensions belong to what image channels
                                histogram,    // the histogram we are using
                                result,       // the resulting back projection image
                                ranges,       // the range of values, for each dimension
                                255.0         // the scaling factor is chosen such that a histogram value of 1 maps to 255
            );
        }

        // Threshold back projection to obtain a binary image
        if (threshold>0.0)
            cv::threshold(result, result, 255.0*threshold, 255.0, cv::THRESH_BINARY);

        return result;
    }

};


#endif