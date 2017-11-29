#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

unsigned t0, t1;

int buscar_linea(char fichero[], int li)//buscar una linea en el archivo deseado
{
    int lu;
    FILE *datos=fopen(fichero,"r");
    int cont=li-1;
    fseek(datos, 0, SEEK_SET);//fseek situa el cursor en un lugar deseado
    proof:     
    if (cont>0)  
    { 
    while (fgetc (datos) != '\n');
        cont--;
        goto proof;
    }
    lu=ftell(datos);//fteel para determinar el lugar del cursor de escritura/lectura
    fclose(datos);
    return lu;

}
void buscar_punto(int Tri, char fichero[], float p[2]){//busca el valor de las cordenadas de los puntos de un triangulo
    int la;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    int lu;
    lu=buscar_linea("puntos",Tri);
    fseek(datos,lu,SEEK_SET);
    fscanf(datos,"%d %f %f", &la,&x,&y);
    if (la==Tri){
        p[0]=x;
        p[1]=y;
    }
    fclose(datos);
}

float suma_peri (float p1[2],float p2[2],float p3[2])//suma el valor de cada una de las distancias de los puntos
{
    float laA,laB,laC;
    laA= sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
    laB= sqrt((p2[0]-p3[0])*(p2[0]-p3[0])+(p2[1]-p3[1])*(p2[1]-p3[1]));
    laC= sqrt((p1[0]-p3[0])*(p1[0]-p3[0])+(p1[1]-p3[1])*(p1[1]-p3[1]));
    return laA+laB+laC;
}

float buscar_tri(char fichero[],int li, int Tri[3])//obtiene los valores de los puntos que conforman el triangulo, para obtener
//las cordenadas y sumar sus distancias para ir calculando cada uno de los perimetros
{
    float peri, p1[2], p2[2], p3[2];
    FILE *datos = fopen(fichero,"r");
    if(!feof(datos)){
        int lug;
        lug=buscar_linea("triangulos",li); 
        fseek(datos,lug,SEEK_SET);
        fscanf(datos,"%d %d %d\n",&Tri[0],&Tri[1],&Tri[2]);
        buscar_punto(Tri[0],"puntos",p1);
        buscar_punto(Tri[1],"puntos",p2);
        buscar_punto(Tri[2],"puntos",p3);
        peri=suma_peri(p1,p2,p3);        
        fclose(datos);
        return peri;
    }
    else{
        return 0;
    }
}

int main(int argc, char* argv[])
{   
    t0=clock();
    int rank_actual, cant_proce;
    int Tri[3]={0,0,0};
    int A=0;
    int B=0;
    float C=0;
    float peri=0;
    float peri_total=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &cant_proce ); //cantidad de proces
    MPI_Comm_rank( MPI_COMM_WORLD, &rank_actual );     // rank actual  
    if(9665%cant_proce==0){//se trabaja diferente para procesadores pares e impares.
        A=9665/cant_proce;
    }
    else{   
        A=9665/cant_proce;
        B=9665%cant_proce;
    }
    if(rank_actual == 0){
        for(int i=1;i<=A+B;i++){
            peri=buscar_tri("triangulos",i,Tri);
            C+=peri;
            printf("procesador : %d numero de linea %d= %f\n",rank_actual,i,peri);
        }
        MPI_Reduce(&C,&peri_total,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);//mpi_reduce reduce un valor de un grupo de procesos en un único proceso
        printf("%f\n",peri_total);
    }
    else{
        for(int i =A*rank_actual+B+1;i<=A*rank_actual+A+B;i++){
            peri=buscar_tri("triangulos",i,Tri);
            C+=peri;
            printf("procesador : %d numero de linea %d= %f\n",rank_actual,i,peri);
        }
        MPI_Reduce(&C,&peri_total,1,MPI_REAL,MPI_SUM,0,MPI_COMM_WORLD);          
    }
    MPI_Finalize();
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    printf("Execution Time: %f\n" ,time);
    return 0;  
}