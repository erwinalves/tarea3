#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float buscarTri(char fichero[],int linea, int triangulo[3])
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

int buscarL(char fichero[], int linea)//buscar una linea en el archivo 
{
    int lugar;
    FILE *datos=fopen(fichero,"r");
    int contar=linea-1;
    fseek(datos, 0, SEEK_SET);
    prueba:     
    if (contar>0)  
    { 
    while (fgetc (datos) != '\n');
        contar--;
        goto prueba;
    }
    lugar=ftell(datos);
    fclose(datos);
    return lugar;

}

void buscarPu(int triangulo, char fichero[], float punto[2]){
    int lado;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    int lugar;
    lugar=buscarlinea("puntos",triangulo);
    fseek(datos,lugar,SEEK_SET);
    fscanf(datos,"%d %f %f", &lado,&x,&y);
    if (lado==triangulo){
        punto[0]=x;
        punto[1]=y;
    }
    fclose(datos);
}

float sumaPerimetro (float punto1[2],float punto2[2],float punto3[2])
{
    float ladoA,ladoB,ladoC;

    ladoA= sqrt((puntos1[0]-puntos2[0])*(puntos1[0]-puntos2[0])+(puntos1[1]-puntos2[1])*(puntos1[1]-puntos2[1]));
    ladoB= sqrt((puntos2[0]-puntos3[0])*(puntos2[0]-puntos3[0])+(puntos2[1]-puntos3[1])*(puntos2[1]-puntos3[1]));
    ladoC= sqrt((puntos1[0]-puntos3[0])*(puntos1[0]-puntos3[0])+(puntos1[1]-puntos3[1])*(puntos1[1]-puntos3[1]));
    return ladoA+ladoB+ladoC;
}



int main(int argc, char* argv[])
{
    
    }  