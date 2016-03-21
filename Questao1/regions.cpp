#include <iostream>
//#include <cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int, char**){

    Mat image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Size medida;
    medida = image.size();
    //i nao pode ser maior que largura
    //j nao pode ser maior que a altura
    //O primeiro par de coordenadas deve ser a origem do retângulo
    //O segundo par deve ser os lados do retângulo
    int x1, y1, x2, y2;


    std::cout << "Digite P1 (origem do seu retângulo) entre 0 e "<< medida.height<< std::endl;
    std::cin >> x1 >> y1;
    if (((x1 < 0) || (x1 > medida.height)) || ((y1 < 0) || (y1 > medida.width))){
      std::cout << "Ponto inválido\n" << std::endl;
      exit(0);
    }
    // Optei pra que o usuário inserisse apenas valores pro segundo ponto maiores
    // que os valores do primeiro
    std::cout << "Digite x2 maior que "<< x1 << " e menor que " << medida.width << std::endl;
    std::cin >> x2;
    std::cout << "Digite y2 maior que "<< y1 << " e menor que " << medida.width << std::endl;
    std::cin >> y2;
    if ( ((x2 <= x1) || (x2 > medida.height)) || ((y2 <= y1) || (y2 > medida.width))) {
      std::cout << "Ponto inválido\n" << std::endl;
      exit(0);
    }

    for(int i= x1; i < x2;i++){
      for(int j=y1; j< y2;j++){

          image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);

    }
  }
     imshow("Imagem", image);

     waitKey();
     return 0;
}
