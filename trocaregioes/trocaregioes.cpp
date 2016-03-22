#include <iostream>
//#include <cv.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
//using namespace std;

int main(int argc, char const *argv[]) {

  Mat imagem = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat imagem1, imagem2, imagem3, imagem4;

  int largura = imagem.rows;
  int altura = imagem.cols;
  Mat nova_imagem(0,0, altura, largura);
  nova_imagem = imagem;


  imagem1 = imagem(Rect(altura/2, largura/2, altura/2, largura/2));
  imagem2 = imagem(Rect(altura/2, 0, altura/2, largura/2));
  imagem3 = imagem(Rect(0, largura/2, altura/2, largura/2));
  imagem4 = imagem(Rect(0, 0, altura/2, largura/2));



  imagem1.copyTo(nova_imagem(Rect(0, 0, altura/2, largura/2)));
  imagem2.copyTo(nova_imagem(Rect(altura/2, largura/2, altura/2, largura/2)));
  imagem3.copyTo(nova_imagem(Rect(altura/2, 0, altura/2, largura/2)));
  imagem4.copyTo(nova_imagem(Rect(0, largura/2, altura/2, largura/2)));

  //p2.copyTo(nova_imagem(Rect(0, 0.5*largura, 0.5*altura, 0.5*largura)));
   imshow("Imagem", nova_imagem);
   waitKey();

  return 0;
}
