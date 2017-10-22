#include "matriz.h"

const int MATRIZ[2][2]={{1,4},{-1,2}};

/********************************************************************
*
* Calcula la matriz inversa. Uso la matriz testigo que es constante y
* calcula su inversa
*
*********************************************************************/

void fCalculoInversa(double md[][2]){
    float det=0;
    det=(float)1/fDeterminante(2);
    md[0][0]=(double)MATRIZ[1][1]*det;
    md[0][1]=(double)(MATRIZ[0][1]*-1)*det;
    md[1][1]=(double)MATRIZ[0][0]*det;
    md[1][0]=(double)(MATRIZ[1][0]*-1)*det;
}

/************************************************************************
*
* Calcula el determinante de una matriz y lo retorna
* si el determinante es 0 la matriz no tiene inversa
* se usa para el calculo de matriz inversa
*
*************************************************************************/

int fDeterminante(int dim){
	int i, j, producto1, producto2, col, sumapos, sumaneg, det;
	sumapos = 0;
	sumaneg = 0;
	producto1 = 1;
	producto2 = 1;
	det = 0;
    for(i = 0; i < dim; i++){
        if(dim>2){
            producto1 = 1;
            producto2 = 1;
        }
        for(j = 0; j < dim; j++){
            col = j + i;
            if(col >= dim){
                col = col - dim;
            }
            producto1 = producto1 * MATRIZ[j][col];
            producto2 = producto2 * MATRIZ[dim-(j+1)][col];
        }
        sumapos = sumapos + producto1;
        sumaneg = sumaneg + producto2;
    }
	det = sumapos - sumaneg;
	return det;
}

/*******************************************************************
*
* Multiplico la matriz testigo por la matriz ASCII
*
********************************************************************/

void fMatrizEncrypting(int m2[][5],int mp[][5],int mDim){
    int i=0;
    int j=0;
    int k=0;
    /// Inicializo la matriz resultado
    for(i=0;i<2;i++){
        for(j=0;j<5;j++){
            mp[i][j]=0;
        }
    }
    for(i=0;i<2;i++){
        for(j=0;j<mDim;j++){
            mp[i][j]=0;
            for(k=0;k<2;k++){
                mp[i][j]=mp[i][j]+MATRIZ[i][k]*m2[k][j];
            }
        }
    }
}

/*************************************************************
*
* Calculo la dimension de la matriz encriptada que levanto del
* archivo. Esto por si no usaron los 10 caracteres del pass
*
**************************************************************/

int fCalculoDimension(int m[][5]){
    int j=0;
    while((m[0][j]!=0)&&(j<5)){
        j++;
    }
    return j;
}

/*************************************************************
*
* Desencripto la contraseña. Recibo la matriz levantada del archivo
* la multiplico por la inversa de la testigo y genero el string
*
**************************************************************/

void fDecrypting(char pass[],int matrizPass[][5]){
    int i=0;
    int j=0;
    int k=0;
    int z=0;
    int mDim;
    double mInversa[2][2];
    int matrizResult[2][5];
    char cadena[10];

    fCalculoInversa(mInversa);
    mDim=fMatrizDecrypting(mInversa,matrizPass,matrizResult);

    z=0;
    for(i=0;i<2;i++){
        for(j=0;j<mDim;j++){
            sprintf(cadena,"%i",matrizResult[i][j]);
            z=atoi(cadena);
            pass[k]=(char)z;
            k++;
        }
    }
    pass[k]='\0';
}

int fMatrizDecrypting(double m1[][2],int m2[][5],int mp[][5]){
    int i=0;
    int j=0;
    int k=0;
    int mDim;
    double temp;
    mDim=fCalculoDimension(m2);
    for(i=0;i<2;i++){
        for(j=0;j<mDim;j++){
            temp=0.0;
            for(k=0;k<2;k++){
                temp=temp+m1[i][k]*m2[k][j];
                mp[i][j]=(double)temp;
            }
        }
    }
    return mDim;
}

/**********************************************************************
*
* Paso el string pass a una matriz de 2x5 con los ASCII correspondientes
* y calculo y devuelvo la dimension de la matriz por si la cadena pass
* es menor a 10 caracteres
*
***********************************************************************/

int fPass2Matrix(char texto[],int matrizTexto[][5]){
    int i=0;
    int j=0;
    int z=0;
    int mDim=0;
    int largoTexto=strlen(texto);
    mDim=largoTexto/2+(largoTexto%2);
    /// Paso la cadena a una matriz ASCII
    for(z=0;z<largoTexto;z++){
        matrizTexto[i][j]=texto[z];
        j++;
        if(j==mDim){
            i=1;
            j=0;
        }
    }
    return mDim;
}
