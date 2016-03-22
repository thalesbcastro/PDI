#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(Mat &m){
  for(int i=0; i<m.size().height; i++){
    for(int j=0; j<m.size().width; j++){
      cout << m.at<float>(i,j) << ",";
    }
    cout << endl;
  }
}

void menu(){
  cout << "\npressione a tecla para ativar o filtro: \n"
	"a - calcular modulo\n"
    "m - media\n"
    "g - gauss\n"
    "v - vertical\n"
	"h - horizontal\n"
    "l - laplaciano\n"
      "t - laplaciano-gaussiano\n"
	"esc - sair\n";
}

int main(int argvc, char** argv){
  VideoCapture video;
  //Maskaras
  float media[] = {1,1,1,
				   1,1,1,
				   1,1,1};
  float gauss[] = {1,2,1,
				   2,4,2,
				   1,2,1};
  float horizontal[]={-1,0,1,
					  -2,0,2,
					  -1,0,1};
  float vertical[]={-1,-2,-1,
					0,0,0,
					1,2,1};
  float laplacian[]={0,-1,0,
					 -1,4,-1,
					 0,-1,0};
  //Declaração das variáveis do tipo Mat
  Mat cap, frame, frame32f, frameFiltered;
  Mat mask(3,3,CV_32F), mask1;
  Mat result, result1;
  // double width, height, min, max;
  int absolut;
  char key;

  video.open(0);
  if(!video.isOpened())
    return -1;


  namedWindow("filtroespacial",1);
  //Inicialmente a máscara vai receber a máscara da média
  mask = Mat(3, 3, CV_32F, media);
  //Retirei a ganho que se tinha pra media
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1); //Pra dar o ganho de 1/9 na máscara da mádia
  swap(mask, mask1);
  absolut=1; // calcs abs of the image

  menu();
  for(;;){
    video >> cap;
    //Converte cap em cinza e manda pra frame
    cvtColor(cap, frame, COLOR_BGR2GRAY);
    flip(frame, frame, 1);
    //Mostra imagens originais
    imshow("original", frame);
    //Frame é convertido pra ponto flutuante e jogado em frame32f
    //Filtra e joga em frameFiltered. Usa mask como maskara. A média inicialmente
    frame.convertTo(frame32f, CV_32F);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

    if(absolut){
      frameFiltered=abs(frameFiltered);
    }
    //Converte frameFiltered pra poder exibir
    frameFiltered.convertTo(result, CV_8U);
    imshow("filtroespacial", result);

    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
    case 'a':
	  menu();
      absolut=!absolut;
      break;
    case 'm':
	  menu();
      mask = Mat(3, 3, CV_32F, media);
      scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'g':
	  menu();
      mask = Mat(3, 3, CV_32F, gauss);
      scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'h':
	  menu();
      mask = Mat(3, 3, CV_32F, horizontal);
      printmask(mask);
      break;
    case 'v':
	  menu();
      mask = Mat(3, 3, CV_32F, vertical);
      printmask(mask);
      break;
    case 'l':
	  menu();
      mask = Mat(3, 3, CV_32F, laplacian);
      printmask(mask);

      break;
    case 't':
    menu();
        // mask recebe os coeficientes da matriz do laplaciano
        // Não precisa converter pra cv_32f, pois a imagem (frame) já entra convertida
        // depois disso se usa a função filter2D() para realizar o filtro do laplaciano. O código segue ainda dentro do case, onde agora
        // mask vai receber a máscara pro gaussiano, recebe um ganho através da função scaleAdd(), sai do break e volta pro começo do loop infinito
        // onde deve ser filtrada por filter2D()
        mask = Mat(3, 3, CV_32F, laplacian);
        filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);



        mask = Mat(3, 3, CV_32F, gauss);
        scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
        swap(mask, mask1);
        filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
        std::cout << "Laplaciano-gaussiano" << std::endl;
        break;

    default:
      break;
    }
  }
  return 0;
}
