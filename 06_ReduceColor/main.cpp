#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

/*
 *
 */
void colorReduce(cv::Mat image, int div = 64){
    int nl = image.rows; //numero de lineas
    int nc = image.cols * image.channels(); //numero de elementos por linea

    for (int j=0; j<nl; j++){
        uchar* data = image.ptr<uchar>(j); //la direccion de mem de la linea(row) j

        for (int i=0; i<nl; i++){
            data[i] = data[i]/div *div + div/2; //procesar el pixel
        }
    }
}

/*
 *  trata la image, que es la entrada, y opera sobre result, aplicando la
 *  trasformación de simplificacion de color
 */
void colorReduceIO(cv::Mat &image,
                   cv::Mat &result,
                   int div = 64){
    int nl = image.rows; //numero de lineas
    int nc = image.cols * image.channels(); //numero de elementos por linea
    int channels = image.channels();

    result.create(image.rows, image.cols, image.type());

    for (int j=0; j<nl; j++){

        //obtenemos la dir memoria de la fila j de la entrada y de la salida
        const uchar* data_in = image.ptr<uchar>(j);
        uchar* data_out = result.ptr<uchar>(j);

        for (int i=0; i < nc*channels; i++){
            data_out[i] = data_in[i]/div *div + div/2; //procesar el pixel
        }
    }
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
