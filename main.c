#include <stdio.h>
#include <stdlib.h>
#include "gotoxy.h"
#include "matriz.h"
#include "usuario.h"


///CONSTANTES
const int TextoNegro = 240;
const int TextoRojo = 252;



int main()
{
    int sesion = 0, elec, i;

    color(TextoNegro);
    hidecursor(0);

    for(i = 0; i < 60; i++)
    {
        gotoxy(0, i);
        printf(" ");
    }

    do
    {
        system("cls");
        sesion = iniciaSesion(sesion);
    }
    while(sesion != 1);

    while(elec!=9)
    {
        system("cls");
        for(i=0; i<60; i++)
        {
            gotoxy(i,0);
            printf("%c",196);
        }
        for(i=0; i<20; i++)
        {
            gotoxy(0,i);
            printf("%c",179);
        }
        for(i=0; i<20; i++)
        {
            gotoxy(60,i);
            printf("%c",179);
        }
        for(i=0; i<60; i++)
        {
            gotoxy(i,20);
            printf("%c",196);
        }
        for(i=0; i<60; i++)
        {
            gotoxy(i,4);
            printf("%c",196);
        }
        gotoxy(0,0);
        printf("%c",218);
        gotoxy(60,0);
        printf("%c",191);
        gotoxy(0,20);
        printf("%c",192);
        gotoxy(60,20);
        printf("%c",217);
        gotoxy(0,4);
        printf("%c",195);
        gotoxy(60,4);
        printf("%c",180);
        gotoxy(23,2);
        printf("MEN%c PRINCIPAL",163);
        gotoxy(23,3);
        for(i=0; i<14; i++)
        {
            printf("%c",238);
        }
        gotoxy(8,6);
        printf("Elija una opci%cn:",162);
        gotoxy(20,8);
        printf("1.- Opcion 1.");
        gotoxy(20,9);
        /*printf("2.- Opcion 2.");
        gotoxy(20,10);
        printf("3.- Opcion 3.");
        gotoxy(20,11);
        printf("4.- ");
        gotoxy(20,12);
        printf("5.- ");
        gotoxy(20,13);
        printf("6.- ");
        gotoxy(20,14);
        printf("7.- ");
        gotoxy(20,15);
        printf("8.- ");*/
        gotoxy(20,16);
        printf("9.- Salir");
        gotoxy(26,6);
        scanf("%d",&elec);

        switch(elec)
        {
        case 1:

            break;
        case 9:
            system("cls");
            printf("Hasta pronto!\n");
            system("pause");
            break;
        }
    }
    return 0;
}
