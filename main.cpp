#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iomanip>
using namespace std;
using std::setw;

void calcularDistancia (float a[2], float b[2], float c[2], float y){
  {
   cout <<"\n\nEste programa calcula la distancia entre dos puntos en el plano cartesiano. "<<endl;
   
   y = sqrt((a[1] - b[1])*(a[1] - b[1] ) + (a[2] - b[2])*(a[2] - b[2]));

   cout <<"\nLa distancia entre los puntos es: " << setw(10) <<y << endl;

   
   }            /* Cierra main */
}

void leerPuntos(float matriz[5000][3]){
  FILE *fichero;
  fichero = fopen("puntos","r");
  if (fichero==NULL){
    printf( "No se puede abrir el fichero.\n" );
    system("pause");
    exit (EXIT_FAILURE);
  }
  int i = 0;
  while (1){
    if (feof(fichero))
      break;
    fscanf (fichero, "%f %f %f\n", &matriz[i][0], &matriz[i][1], &matriz[i][2]);
    i++;
   }
   fclose(fichero);
}

void leerTriangulos(int x, float matriz[5000][3]){
  FILE *fichero;
  fichero = fopen("triangulos","r");
  if (fichero==NULL){
    printf( "No se puede abrir el fichero.\n" );
    exit (EXIT_FAILURE);
  }
  int i = 0;
  while (1){
    if (feof(fichero))
      break;
    int a,b,c;
    fscanf (fichero, "%d %d %d\n", &a, &b, &c);
    float A[2],B[2],C[2];
    A[0]=matriz[a][1];
    A[1]=matriz[a][2];
    B[0]=matriz[b][1];
    B[1]=matriz[b][2];
    C[0]=matriz[c][1];
    C[1]=matriz[c][2];
    i++;
   }
   fclose(fichero);
}

/*int buscarCoordenada (float matrizA[9665][3],float matrizB[5000][3]){
  int  i,j,k;
  for (i = 0; i < 9665; i++) {
    for (j = 0; j < 5000; j++){
      for(k = 0; k < 3; j++){
        if(matrizA[i][k]==matrizB[j][0]){
          matrizA[i][1]=matrizB[j][1];
          matrizA[i][2]=matrizB[j][2];
        }
      }
        
    }
  }
}*/

int main()
{
  float  j=0;
  float a[2],b[2],c[2],d[2];
  for(int i=0;i<2;i++){
    a[i]=(3+i)*i;
    b[i]=((2+i)*i)-3;
    c[i]=(6-i)+i*3;
  }
  calcularDistancia(a, b, c, j);

  /*int triangulos[9665][3];
  leerTriangulos(triangulos);
  //buscarCoordenada (triangulos,puntos);
  printf( "Contenido del fichero triangulos:\n" );
  for (i = 0; i < 9665; i++) {
    for (j = 0; j < 3; j++)
      printf ("%d ", triangulos[i][j]);
      printf ("\n");
  }
  float puntos[5000][3];

  leerPuntos(puntos);

  printf( "Contenido del fichero Puntos:\n" );
  
  for (i = 0; i < 5000; i++) {
    for (j = 0; j < 3; j++)
      printf ("%f ", puntos[i][j]);
      printf ("\n");
  }*/
}

