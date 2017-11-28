#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int buscarL(char fichero[], int linea)//buscar una linea en el archivo deseado
{
    int lugar;
    FILE *datos=fopen(fichero,"r");
    int contar=linea-1;
    fseek(datos, 0, SEEK_SET);//fseek situa el cursor en un lugar deseado
    prueba:     
    if (contar>0)  
    { 
    while (fgetc (datos) != '\n');
        contar--;
        goto prueba;
    }
    lugar=ftell(datos);//fteel para determinar el lugar del cursor de escritura/lectura
    fclose(datos);
    return lugar;

}
void buscarPu(int triangulo, char fichero[], float punto[2]){//busca el valor de las cordenadas de los puntos de un triangulo
    int lado;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    int lugar;
    lugar=buscarL("puntos",triangulo);
    fseek(datos,lugar,SEEK_SET);
    fscanf(datos,"%d %f %f", &lado,&x,&y);
    if (lado==triangulo){
        punto[0]=x;
        punto[1]=y;
    }
    fclose(datos);
}

float sumaPerimetro (float punto1[2],float punto2[2],float punto3[2])//suma el valor de cada una de las distancias de los puntos
{
    float ladoA,ladoB,ladoC;
    ladoA= sqrt((punto1[0]-punto2[0])*(punto1[0]-punto2[0])+(punto1[1]-punto2[1])*(punto1[1]-punto2[1]));
    ladoB= sqrt((punto2[0]-punto3[0])*(punto2[0]-punto3[0])+(punto2[1]-punto3[1])*(punto2[1]-punto3[1]));
    ladoC= sqrt((punto1[0]-punto3[0])*(punto1[0]-punto3[0])+(punto1[1]-punto3[1])*(punto1[1]-punto3[1]));
    return ladoA+ladoB+ladoC;
}

float buscarTri(char fichero[],int linea, int triangulo[3])//obtiene los valores de los puntos que conforman el triangulo, para obtener
//las cordenadas y sumar sus distancias para ir calculando cada uno de los perimetros
{
    float perimetro, punto1[2], punto2[2], punto3[2];
    FILE *datos = fopen(fichero,"r");
    if(!feof(datos)){
        int lugar;
        lugar=buscarL("triangulos",linea); 
        fseek(datos,lugar,SEEK_SET);
        fscanf(datos,"%d %d %d\n",&triangulo[0],&triangulo[1],&triangulo[2]);
        buscarPu(triangulo[0],"puntos",punto1);
        buscarPu(triangulo[1],"puntos",punto2);
        buscarPu(triangulo[2],"puntos",punto3);
        perimetro=sumaPerimetro(punto1,punto2,punto3);        
        fclose(datos);
        return perimetro;
    }
    else{
        return 0;
    }
}

int main(int argc, char* argv[])
{   

    int rank_Actual, cant_Proce;
    int triangulo[3]={0,0,0};
    int A=0;
    int B=0;
    float C=0;
    float perimetro=0;
    float perimetro_Total=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &cant_Proce ); //cantidad de proces
    MPI_Comm_rank( MPI_COMM_WORLD, &rank_Actual );     // rank actual  
    if(9665%cant_Proce==0){//se trabaja diferente para procesadores pares e impares.
        A=9665/cant_Proce;
    }
    else{   
        A=9665/cant_Proce;
        B=9665%cant_Proce;
    }
    if(rank == 0){
        for(int i=1;i<=A+B;i++){
            perimetro=buscarTri("triangulos",i,triangulo);
            C+=perimetro;
            printf("procesador : %d numero de linea %d= %f\n",rank_Actual,i,perimetro);
        }
        MPI_Reduce(&C,&perimetro_Total,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);//mpi_reduce reduce un valor de un grupo de procesos en un único proceso
        printf("%f\n",perimetro_Total);
    }
    else{
        for(int i =A*rank_Actual+B+1;i<=A*rank_Actual+A+B;i++){
            perimetro=buscarTri("triangulos",i,triangulo);
            C+=perimetro;
            printf("procesador : %d numero de linea %d= %f\n",rank_Actual,i,perimetro);
        }
        MPI_Reduce(&C,&perimetro_Total,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);          
    }
    MPI_Finalize();
    return 0;  
}