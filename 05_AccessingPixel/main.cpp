#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>

/*
 * reiterpret_cast: convierte entre tipos, reinterpretando el patron de bits subyacente.
 * es usado para casting como operador en C++
 * data_type *var_name = reinterpret_cast <data_type *>(pointer_variable);
 */

//Ruido tipo sal a una imagen
void salt(cv::Mat image, int n){

    //seccion para generar numeros aleatorios
    std::default_random_engine generator;
    std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
    std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

    int i,j;
    for (int k=0; k<n; k++) {

        //generador de coordenadas de una imagen
        i = randomCol(generator);
        j = randomRow(generator);

        if (image.type() == CV_8UC1){ //si es dato tipo gris
            image.at<uchar>(j,i) = 255;
        }
        else if (image.type() == CV_8UC3){ //si es un dato tipo color (3 canales)
            image.at<cv::Vec3b>(j, i)[0] = 255;
            image.at<cv::Vec3b>(j, i)[1] = 255;
            image.at<cv::Vec3b>(j, i)[2] = 255;
            //image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
        }
    }
}

/*
 * Esta es una versión extra de la función salt.
 * Solo funciona con imagenes de 1 canal
 */
void salt2(cv::Mat image, int n){
    CV_Assert(image.type() == CV_8UC1);

    //generador de numeros aleatorios
    std::default_random_engine generator;
    std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
    std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

    cv::Mat_<uchar> img(image);
    //cv::Mat_<uchar>& img2 = reinterpret_cast<cv::Mat_<uchar>&> (image);

    int i,j;
    for (int k=0; k<n ; k++){
        i = randomCol(generator);
        j = randomRow(generator);

        img(j,i) = 255;
    }
}

int main() {

    cv::Mat image = cv::imread("/home/laila/programacion/C++/openCV/05_AccessingPixel/pessoa.png",
                               1); //abrimos la imagen, con color

    //anadir ruido
    salt(image, 3000);

    cv::namedWindow("Image");
    cv::imshow("Image", image);
    cv::waitKey();

    cv::Mat image2 = cv::imread("/home/laila/programacion/C++/openCV/05_AccessingPixel/pessoa.png",0);

    //anadir ruido con la segunda funcion
    salt2(image2, 6000);

    cv::namedWindow("image2");
    cv::imshow("image2", image2);
    cv::waitKey();


    return 0;
}
