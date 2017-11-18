#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void leerPuntos(int matriz[5000][3]){
  FILE *fichero;
  fichero = fopen("puntos","r");
  if (fichero==NULL){
    printf( "No se puede abrir el fichero.\n" );
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

void leerCoordenada(int matriz[5000][2]){
  FILE *fichero;
  fichero = fopen("coordenada.txt","r");
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

/*void buscarCoordenada (int arrayA[2],int arrayB[2],matriz[5000][2]){
  int  i,j;
  for (i = 0; i < 5000; i++) {
    for (j = 0; j < 2; j++)
      if (arrayA[0]==matriz[i][0]){
        arrayB[0]=matriz[i][1];
        arrayB[1]=matriz[i][2]
        i=5000;
      }
  }esta es una prueba*/

int main()
{
  int puntos[5000][3];
  leerPuntos(puntos);
  printf( "Contenido del fichero:\n" );
  int  i,j;
  for (i = 0; i < 5000; i++) {
    for (j = 0; j < 3; j++)
      printf ("%d ", puntos[i][j]);
      printf ("\n");
  }
}
