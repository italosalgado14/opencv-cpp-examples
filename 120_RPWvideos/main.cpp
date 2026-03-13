
#include <string>
#include <iostream>
#include <sstream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "videoprocessor.h"

void draw(const cv::Mat& img, cv::Mat& out) {

    img.copyTo(out);
    cv::circle(out, cv::Point(100,100),5,cv::Scalar(255,0,0),2);
}

// processing function
void canny(cv::Mat& img, cv::Mat& out) {

    // Convert to gray
    if (img.channels()==3)
        cv::cvtColor(img,out,cv::COLOR_BGR2GRAY);
    // Compute Canny edges
    cv::Canny(out,out,100,200);
    // Invert the image
    cv::threshold(out,out,128,255,cv::THRESH_BINARY_INV);
}

int main()
{

    cv::VideoCapture capture("/home/laila/programacion/C++/openCV/120_RPWvideos/DriftDogo.mp4"); //abrimos el archivo de video
    //cv::VideoCapture capture("http://www.laganiere.name/bike.avi"); //o lo abrimos a traves de la web
    if (!capture.isOpened()) //chequeamos que este correctamente abierto
        return 1;
    double rate= capture.get(cv::CAP_PROP_FPS); //obtenemos el frame rate
    std::cout << "Frame rate: " << rate << "fps" << std::endl;

    bool stop(false);
    cv::Mat frame; //video frame actual
    cv::namedWindow("Extracted Frame");

    // corresponds to video frame rate
    int delay= 1000/rate; //delay entre cada frame
    long long i=0;
    std::string b="bike";
    std::string ext=".bmp";

    while (!stop) { //para todos los frames en el video

        // read next frame if any
        if (!capture.read(frame))
            break;
        cv::imshow("Extracted Frame",frame);

        std::string name(b);
        std::ostringstream ss; ss << std::setfill('0') << std::setw(3) << i; name+= ss.str(); i++;
        name+=ext;

        std::cout << name <<std::endl;

        cv::Mat test;
        //      cv::resize(frame, test, cv::Size(), 0.2,0.2);
        //		cv::imwrite(name, frame);
        //		cv::imwrite(name, test);

        // introduce a delay
        // or press key to stop
        if (cv::waitKey(delay)>=0)
            stop= true;
    }

    // Close the video file
    capture.release();

    cv::waitKey();

    //---------------------------------------------------------------------
    //VideoProcessor class

    // Create instance
    VideoProcessor processor;

    // Open video file
    processor.setInput("/home/laila/programacion/C++/openCV/120_RPWvideos/DOGO.avi");

    // Declare a window to display the video
    processor.displayInput("Input Video");
    processor.displayOutput("Output Video");

    // Play the video at the original frame rate
    processor.setDelay(1000./processor.getFrameRate());

    // Set the frame processor callback function
    processor.setFrameProcessor(canny);


    // output a video
    processor.setOutput("/home/laila/programacion/C++/openCV/120_RPWvideos/Canny.avi");
    // stop the process at this frame
    processor.stopAtFrameNo(400);


    // Start the process
    processor.run();


    cv::waitKey();

    return 0;
}