#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iomanip>
using namespace std;
using std::setw;

float calcularDistancia (float a[2], float b[2], float c[2], float y){
  y = y + sqrt((b[0] - a[0])*(b[0] - a[0] ) + (b[1] - a[1])*(b[1] - a[1]));
  //printf("El distancia es : %f \n", y);
  y = y + sqrt((c[0] - b[0])*(c[0] - b[0] ) + (c[1] - b[1])*(c[1] - b[1]));
  //printf("El PERIMETRO es : %f \n", y);
  y = y + sqrt((a[0] - c[0])*(a[0] - c[0] ) + (a[1] - c[1])*(a[1] - c[1]));
  //printf("El PERIMETRO es : %f \n", y);
  return y;
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

void leerTriangulos(float x, float matriz[5000][3]){
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
    printf("Los puntos son : %d %d %d\n", a,b,c);
    float A[2],B[2],C[2];
    A[0]=matriz[a-1][1];
    //printf("El X1 es : %f \n", A[0]);
    A[1]=matriz[a-1][2];
    //printf("El Y1 es : %f \n", A[1]);
    B[0]=matriz[b-1][1];
    //printf("El X2 es : %f \n", B[0]);
    B[1]=matriz[b-1][2];
    //printf("El Y2 es : %f \n", B[1]);
    C[0]=matriz[c-1][1];
    //printf("El X3 es : %f \n", C[0]);
    C[1]=matriz[c-1][2];
    //printf("El Y3 es : %f \n", C[1]);
    x = calcularDistancia(A, B, C, x);
    i++;
   }
   fclose(fichero);
   printf("La suma de todos los perimetros es : %f \n", x);
}
int main(){
  float puntos[5000][3];
  leerPuntos(puntos);
  float perimetro=0;
  leerTriangulos(perimetro, puntos);
}

