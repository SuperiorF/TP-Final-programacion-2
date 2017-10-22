#include <string.h>
#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

void fCalculoInversa(double md[][2]);
int fDeterminante();
int fPass2Matrix(char texto[],int matrizTexto[][5]);
//void fMatrizEncripting(int m2[][5],int mp[][5],int mDim);
void fMatrizEncrypting(int m2[][5],int mp[][5],int mDim);
int fCalculoDimension(int m[][5]);
void fDecrypting(char pass[],int matrizPass[][5]);
int fMatrizDecrypting(double m1[][2],int m2[][5],int mp[][5]);

#endif // MATRIZ_H_INCLUDED
