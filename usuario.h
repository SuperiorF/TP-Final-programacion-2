#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> ///LIBRERIA PARA EL USO DE VALORES ASCII
#include <string.h>
#include "matriz.h"
#include "gotoxy.h"

///ESTRUCTURAS

typedef struct
{
    int id;
    char nombre[30];
    char apellido[30];
    char usuario[20];
    int pass[2][5];
    int eliminado;
} usuario;

///-------------------------------------------------DECLARACION FUNCIONES-------------------------------------------------------

///FUNCIONES CON LA ESTRUCTURA USUARIO
int asignaId();
int validaNombre(usuario mi_usuario);
int validaIdParaModificar(int id);
int iniciaSesion(int sesion);
void mostrarArchivoUsuariosActivos();
void mostrarArchivoUsuariosInactivos();
void mostrarUsuarios(usuario un_usuario);
void menuUsuarios();
void cargarUsuario();                         ///Alta
void bajaUsuario(int id);                           ///Baja
void menuModificacionUsuario(int id);               ///Modificacion
    usuario modificarNombreUsuario(usuario un_usuario);
    usuario modificarApellidoUsuario(usuario un_usuario);
    usuario modificarNomDeUsuario(usuario un_usuario);
    usuario modificarContraUsuario(usuario un_usuario);


#endif // USUARIO_H_INCLUDED
