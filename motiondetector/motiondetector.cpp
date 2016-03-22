#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;

  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histR_1;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }


  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  //Não precisa de mais um cálculo

  while(1){
    cap >> image;
    split (image, planes);

    //Calculando o histograma no instante
    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    histImgR.setTo(Scalar(0));


    for(int i=0; i<nbins; i++){
      line(histImgR, Point(i, histh),
           Point(i, cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);

    }
    histImgR.copyTo(image(Rect(0, 0,nbins, histh)));


    calcHist(&planes[0], 1, 0, Mat(), histR_1, 1,
              &nbins, &histrange,
              uniform, acummulate);

    normalize(histR_1, histR_1, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    //usando o primeiro método de comparação
    double comp = compareHist(histR, histR_1, 2);
    if(comp < 200){
      std::cout << "\a\a\a" << std::endl;
      std::cout << "ULTRAPASSOU O LIMITE ESTABELECIDO" << std::endl;

    }

    imshow("image", image);

     if(waitKey(30) >= 0) break;
   }


  return 0;
}
