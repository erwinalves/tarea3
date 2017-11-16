#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

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

void leerTriangulos(int matriz[9665][3]){
  FILE *fichero;
  fichero = fopen("triangulos","r");
  if (fichero==NULL){
    printf( "No se puede abrir el fichero.\n" );
    system("pause");
    exit (EXIT_FAILURE);
  }
  int i = 0;
  while (1){
    if (feof(fichero))
      break;
    fscanf (fichero, "%d %d %d\n", &matriz[i][0], &matriz[i][1], &matriz[i][2]);
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
  int  i,j;
  int triangulos[9665][3];
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
  }
}

