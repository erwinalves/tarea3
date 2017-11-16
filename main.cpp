#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
    file *fichero;
    char cadena[5000],constante=' ',aux[30];
    int matriz[5000][2];
    int i=0;
    for(int i=0;i<5000;i++)
        for(int j=0;j<2;j++)
            matriz[i][j]=0;

    fichero = fopen("puntos.txt","r");
    if(fichero==NULL){
        cout<<"no se puede abrir el fichero"<<endl;
        exit(EXIT_FAILURE);
    }

    ifstream fe("puntos.txt");
    fe.getline(cadena, 5000);
    for(int i=0;i<5000;i++){
        aux=cadena[i];
        for(int j=0;j<2;j++){
            matriz[i][j]=strtok(aux,constante);
        }
    }
    return 0;
}
