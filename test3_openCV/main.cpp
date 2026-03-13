/*
 * Configuracion de openCV:
 * https://geekytheory.com/opencv-en-linux
 * https://docs.opencv.org/master/d7/d16/tutorial_linux_eclipse.html
 * https://cv-tricks.com/installation/opencv-4-1-ubuntu18-04/
 */

#include <opencv2/core/core.hpp> //core functionalities
#include <opencv2/imgproc/imgproc.hpp> //image processing functions
#include <opencv2/highgui/highgui.hpp> //image and video reading and writing functions, wuth interfaces
#include <iostream>
#include <unistd.h>

/* def functions */
void onMouse(int event, int x, int y, int flags, void* param){

    cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            std::cout << "at (" << x << "," << y << ") value is: "
                      << static_cast<int> (im->at<uchar> (cv::Point(x,y))) << std::endl;
            break;
    }
}

/* main prog */
int main ( int argc, char **argv ) {
    /*
     * 1 - Cargar imagen a la memoria, operaciones basicas
     *  sobre imagenes
     */

    cv::Mat image; //una imagen vacia 0x0
    std::cout << "This image is " << image.rows << " x " << image.cols << std::endl; // confirmar 0x0

    // Chequeamos que la imagen se cargue correctamente a la variable
    image = cv::imread("/home/laila/Descargas/Vision_por_Computador/Codigo/test3_openCV/mundo.png");
    if (image.empty()) {
        //error, cagamos
        std::cout << "The image dont charge correctly" << std::endl;
        return -1;
    }
    std::cout << "This image is " << image.rows << " x " << image.cols << std::endl; // confirmar

    // creamos una ventana para la imagen llamada original image
    cv::namedWindow("original image"); //def la ventana (opcional)
    cv::imshow("original image", image); //mostrar la imagen

    // callback function para esta imagen
    cv::setMouseCallback("original image", onMouse, reinterpret_cast<void*>(&image));


    cv::Mat result; //una nueva imagen 0x0
    cv::flip(image, result, 1); //pos horiz, 0 vertical, neg both
    cv::namedWindow("output image");
    cv::imshow("output image", result);

    cv::waitKey(0); // 0 to indefinitely wait for a key pressed, positive waint in ms

    //guardamos la imagen corroborando que el comando sea ejecutado correctamente
    bool control = false;
    try {
        result = cv::imwrite("/home/laila/Descargas/Vision_por_Computador/Codigo/test3_openCV/output.bmp",
                             result);
        printf("La imagen se ha guardado correctamente\n");
    }
    catch (const cv::Exception& ex) {
        fprintf(stderr, "No se pudo convertir la imagen: %s\n", ex.what());
    }

    /*
     * 2 - Re-read the image and configure to only grayscale
     */
    cv::namedWindow("Drawing on an Image"); // definir una nueva ventana

    // dibujamos sobre la nueva ventana
    cv::circle(image, cv::Point(155,110), 65, 0, 3);
    cv::putText(image, "This is a dog", cv::Point(40,200), cv::FONT_HERSHEY_PLAIN,
                2.0, 255, 2);


    cv::imshow("Drawing on an Image", image);
    cv::waitKey(0);
    return 0;
}