#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int, char**){

    VideoCapture cap(0); // abre camera


    if(!cap.isOpened())  // checagem
        return -1;

    namedWindow("Imagem de vídeo", 1);

    for(;;)
    {
        Mat frame;

        //Vector de matrizes para guardar as cores R, G e B
        vector<Mat> planes;
        //Pega novo frame
        cap >> frame;
        //Pega as matrizes R, G e B dos frames e guarda no vetor de matrizes, faz o inverso do merge, que será descrito abaixo.
        //Pega matriz, frame, e retira as componentes R, G e B e guarda no vetor de matrizes.
        split (frame, planes);
        //Declara três matrizes (RGB)
        Mat B,G,R;

        //Calcular histograma h(rk), onde k pertence [0, L-1]
        //Calcular histograma acumulado ha(rk) = somatorio h(rj), j= 1, 2, 3, ..., k
        //Normalizar o histograma acumulado na faixa [0, L]: ha(rk) = ha(rk)/ ha(rl)
        //Transformar a imagem: s = ha(rk), k E [0, l-1 ]

        //Equaliza as componeste separadamente
        equalizeHist( planes[0], B );
        equalizeHist( planes[1], G );
        equalizeHist( planes[2], R );

        //Vector de matrizes
        vector<Mat> combined;
        //Adiona a matriz B equalizada ao vetor de matrizes combined
        combined.push_back(B);
        //Adiona a matriz G equalizada ao vetor de matrizes combined
        combined.push_back(G);
        //Adiona a matriz R equalizada ao vetor de matrizes combined
        combined.push_back(R);

        //Cria matriz para mostrar resultado equalizado
        Mat result;

        //combina as várias matrizes do vetor de matrizes combined (R,G e B) numa única matriz, result.
        merge(combined,result);
        //Mostra frame
        imshow("Video equalizado", result);
        imshow("Video", frame);

        if(waitKey(30) >= 0) break;
    }

      return 0;
}
