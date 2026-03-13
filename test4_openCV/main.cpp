//1) Los includes
#include <opencv2/core/core.hpp> //core functionalities
#include <opencv2/imgproc/imgproc.hpp> //image processing functions
#include <opencv2/highgui/highgui.hpp> //image and video reading and writing functions, wuth interfaces
#include <iostream>
#include <unistd.h>

/*
 * Explorando el cv::Mat, la estructura escencial en openCV
 */

//2) creamos una nueva imagen en escala de grises
// para llamar a esta función debemos hacerlo: cv::Mat gray= function();
cv::Mat function() {
    cv::Mat ima(500,500,CV_8U,50);
    return ima;
}

int main() {

    //3) definimos 6 ventanas para mostrar, con susu nombres, porque si
    cv::namedWindow("Image 1");
    cv::namedWindow("Image 2");
    cv::namedWindow("Image 3");
    cv::namedWindow("Image 4");
    cv::namedWindow("Image 5");
    cv::namedWindow("Image");

    //4) creamos una nueva imagen de 240 rows y 320 columns
    cv::Mat image1(240, 320, CV_8U, 100); //1 byte pixel image, U=unsigned
    cv::imshow("Image", image1);
    cv::waitKey(0);

    //resize de una imagen
    image1.create(200, 200, CV_8U);
    image1 = 200;
    cv::imshow("Image", image1);
    cv::waitKey(0);

    // una imagen de solo colores rojos
    cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255)); //color image C3, 3 channels
    cv::imshow("Image", image2);
    cv::waitKey(0);

    //5) leer imagen, copiarla a otra variable mat: aquí hay varias formas
    cv::Mat image3 = cv::imread("/home/laila/Descargas/Vision_por_Computador/Codigo/test4_openCV/mundo.png");
    // ------- todas estas imágenes apuntan al mismo bloque de datos
    cv::Mat image4(image3);
    image1 = image3;
    // ------- estas imagenes son copias de la imagen fuente
    image3.copyTo(image2);
    cv::Mat image5 = image3.clone();
    //image1.convertTo(image2,CV_32F,1/255.0,0.0); copia con otro datatype: punto flotante image [0,1]

    //6) vamos a hacer un flip
    cv::flip (image3, image3, 1);

    //chequeamos las imagenes que han sido afectadas por esto
    cv::imshow("image3", image3);
    cv::imshow("image1", image1); //aff
    cv::imshow("image2", image2);
    cv::imshow("image4", image4); //aff
    cv::imshow("image5", image5);
    cv::waitKey(0);

    //7) usamos la funcion que definimos al inicio para generar una nueva
    //imagen en escala de grises
    cv::Mat gray = function();
    cv::imshow("Image", gray);
    cv::waitKey(0);

    //8) cargar una imagen de color y convertirla a escala de grises
    image1 = cv::imread("/home/laila/Descargas/Vision_por_Computador/Codigo/test4_openCV/mundo.png"
            , cv::IMREAD_GRAYSCALE);
    image1.convertTo(image2, CV_32F, 1/255.0, 0.0);
    cv::imshow("image", image2);
    cv::waitKey(0);

    return 0;
}
