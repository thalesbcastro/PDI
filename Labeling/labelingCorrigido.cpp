  #include <iostream>
  #include <opencv/highgui.h>
  #include <opencv2/core/core.hpp>
  #include <opencv2/highgui/highgui.hpp>
  #include <opencv2/imgproc/imgproc.hpp>

#define COR_FUNDO 50
#define COR_OBJ_MACICO 80
#define COR_OBJ_FURADO 200

using namespace cv;
using namespace std;

int main (int argc, char** argv) {

    //declaração das variaveis

    Mat image;
    int height, width;
    int objetosfurado = 0;
    int objetosmacicos = 0;

    CvPoint p;
    p.y = 0;

    image = imread("imagem2.png",CV_LOAD_IMAGE_GRAYSCALE); //chamada da função que lê a imagem em grayscale

    if(!image.data){
        std::cout << "Erro: Nao foi possivel carregar a imagem.\n"; //sinal de falha na leitura da imagem
        return(-1);
    }

    //pintar as bordas de branco
    for  (int i=0; i<height; i++) {
        image.at<uchar>(0,i) = 255;
        image.at<uchar>(height-1,i) = 255;
    }

    for (int i=0; i<width; i++) {
        image.at<uchar>(i,0) = 255;
        image.at<uchar>(i,width-1) = 255;
    }

    //remove as bordas e os objetos colados nela(pintando de preto)
    floodfill(image,p,0);
    //pinta o fundo com um tom de cinza 50, para que possamos achar bolhas nos objetos comparando os pixels com o valor 0.
    floodfill (image,p,COR_FUNDO);

    //agora que todos os objetos na borda foram rejeitados, procuraremos tons 255 na imagem pixel a pixel.
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
                if (image.at<uchar>(i,j) = 255) { //objeto encontrado
                    p.x = j;
                    p.y = i;
                    floodfill(image,p,COR_OBJ_MACICO);
                    objetosmacicos++; //os objetos com furo serão subtraídos posteriormente
                }
        }
    }

    for (int i = 0; i<height; i++) {
        for (int j = 0; j<width; j++) {

            //salva as coordenadas de do ponto caso ele pertença a um objeto
            if (image.at<uchar>(i,j) == COR_OBJ_FURADO || image.at<uchar>(i,j) == COR_OBJ_MACICO) {
                p.x = j;
                p.y = i;

            }

            else if (image.at<uchar>(p.y,p.x) == COR_OBJ_MACICO) { //se o objeto estiver marcado como um objeto maciço, ele será devidamente marcado como um objeto furado(e pintado com a cor adequada).
                if (image.at<uchar>(i,j) == 0) { //como o fundo está cinza(50) um ponto preto indica um furo.
                    objetosfurado++;
                    objetosmacicos--;
                    floodfill(image,p,COR_OBJ_FURADO);
                }
            }
        }
    }

    //voltar o fundo para a cor preta e exibir a imagem/dados processados
    p.x = 0;
    p.y = 0;
    floodfill(image,p,0);
    imshow("image", image);
    imwrite("labeling.png", image);
    cout << "Contagem dos objetos com furo: " << objetosfurado << endl;
    cout << "Contagem dos objetos macicos: " << objetosmacicos << endl;
    waitKey();
    return 0;
}
