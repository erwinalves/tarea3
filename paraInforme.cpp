#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;

int es_primo(int N)
{
   int k, raiz;
   raiz = (int) sqrt(N); /*  N es un numero primo si sólo es divisible por N o por la unidad. */
   for( k=2; N%k && k<=raiz; k++);/* Si se llego a dividir N entre todos los numeros menores que su raíz cuadrada entonces es un primo */
   if(k==raiz+1)
      return 1;
   return 0; /* no es primo */
}

 
int main(int argc, char *argv[]){
 
    MPI_Status estado;
    int status,rank_actual,cant_proce;
    int limite[2];
    int numero = atoi(argv[1]);//guarda el argumento pasado por consola
    if(numero < 2){
      cout<<"Ingrese un número válido."<<endl;//uno no es primo
    }
    else{//si se ingresa un numero valido empieza a trabajar
      MPI_Init(&argc, &argv);  // Inicio de MPI   
      MPI_Comm_size(MPI_COMM_WORLD, &cant_proce);  // numero de procesadores
      MPI_Comm_rank(MPI_COMM_WORLD, &rank_actual); // rango de procesadores
      if(rank_actual == 0){//procesador 0 comienza a trabajar
        cout<<"Los numeros primos son:"<<endl;
        if(numero%2==0){//verificamos si el numero ingresado es par, ya que el limite superior tiene que cambiar para los numeros impares por el tema de los decimales
          for(int i=0; i<cant_proce; i++){
            limite[0] = ((numero/cant_proce)*i)+1;//limite inferior (dependiendo de la cantidad de proce dividimos los numeros a procesar) el uno no es primo
            limite[1] = ((numero/cant_proce)*(i+1));//limite superior
            status = MPI_Send(limite, 2, MPI_INT, i, 0, MPI_COMM_WORLD);//envio limites
          }
        }
        else{
          for(int i=0; i<cant_proce; i++){
            limite[0] = ((numero/cant_proce)*i)+1;//limite inferior (dependiendo de la cantidad de proce dividimos los numeros a procesar) el uno no es primo
            limite[1] = ((numero/cant_proce)*(i+1)+1);//limite superior +1 para el caso de los impares ya que dejara el ultimo numero fuera del limite
            status = MPI_Send(limite, 2, MPI_INT, i, 0, MPI_COMM_WORLD);//envio limites
          }
        }
        
        status = MPI_Recv(limite, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);//recibo limite para el proce 0
        for(int i=limite[0];i<=limite[1];i++){//recorremos los numeros entre los limites
          if (es_primo(i)){
            cout<<i<<endl;//mostramos los numeros que son primos
          }
        }
      }
      else{//para los demás procesadores
        status = MPI_Recv(limite, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);// reciben los limites enviados por 0
        for(int i=limite[0];i<=limite[1];i++){//recorremos los numeros entre los limites
          if (es_primo(i)){
            cout<<i<<endl;//mostramos los numeros que son primos
          }
        }
      }
      MPI_Finalize();
    }
}
