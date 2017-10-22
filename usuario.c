#include "usuario.h"

///CONSTANTES

const char ArchiUsers[] = "usuario.dat";
const char Guion = 196;


void cargarUsuario()
{
    int check = 0;
    int id;
    ///VARIABLES DE LA CONTRASEÑA
    int passAscii[2][5];
    int passEncriptada[2][5];
    int dimensionContra;
    int errores = 0;
    char contra[10];
    ///VARIABLES PARA EL FOR
    int i,j;

    usuario un_usuario;
    FILE * archi;

    id = asignaId();

    archi = fopen(ArchiUsers, "ab");


    printf("ID asignado de nuevo usuario: %d\n", id);
    printf("Ingrese el nombre: ");
    fflush(stdin);
    gets(un_usuario.nombre);
    printf("Ingrese el apellido: ");
    fflush(stdin);
    gets(un_usuario.apellido);
    do
    {
        if(check != 0)
        {
            color(252);
            printf("ERROR! El nombre de usuario ya fue utilizado, por favor, seleccione otro.\n");
            color(240);
        }
        check = 0;
        printf("Ingrese nombre de usuario: ");
        fflush(stdin);
        gets(un_usuario.usuario);
        check = validaNombre(un_usuario);;
    }
    while(check != 0);

    do
    {
        if(errores != 0)
        {
            color(252);
            printf("Error! La contrase%ca ingresada no es valida.\n", 164);
            color(240);
            errores = 0;
            for(i=0; i<strlen(contra); i++)
            {
                contra[i]=0;
            }
        }
        printf("Ingrese la contrase%ca: ", 164);
        fflush(stdin);
        gets(contra);
        if(strlen(contra) > 10 || strlen(contra) < 1)
        {
            errores = 1;
        }
        else
        {
            for(i=0; i<strlen(contra); i++)
            {
                if(!isalnum(contra[i]) && !isspace(contra[i]))
                {
                    errores = 1;
                }
            }
        }
    }
    while(errores != 0);
    dimensionContra = fPass2Matrix(contra, passAscii);
    fMatrizEncrypting(passAscii, passEncriptada, dimensionContra);

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 5; j++)
        {
            un_usuario.pass[i][j] = passEncriptada[i][j];
        }
    }

    un_usuario.id = id;
    un_usuario.eliminado = 0;

    fwrite(&un_usuario, sizeof(usuario), 1, archi);

    fclose(archi);
}

int asignaId()
{
    int id = 1;

    FILE * archi;
    usuario un_usuario;

    archi = fopen(ArchiUsers, "r+b");
    if(archi)
    {
        /*fseek(archi, 0, SEEK_END);
        fseek(archi, sizeof(usuario)*-1, SEEK_CUR);
        fread(&un_usuario, sizeof(usuario), 1, ArchiUsers);*/
        ///recorre todo el archivo y se queda con el ultimo usuario activo
        if(fread(&un_usuario, sizeof(usuario), 1, archi) > 0)
        {
            fseek(archi, 0, SEEK_END);
            fseek(archi, sizeof(usuario) * -1, SEEK_CUR);
            fread(&un_usuario, sizeof(usuario), 1, archi);

        }

        id = un_usuario.id + 1;
    }
    fclose(archi);
    return id;
}

void mostrarArchivoUsuariosActivos()
{
    usuario un_usuario;
    FILE * archi;

    archi = fopen(ArchiUsers, "rb");

    if(archi != NULL)
    {
        while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0)
        {
            if(un_usuario.eliminado == 0)
            {
                mostrarUsuarios(un_usuario);
            }
        }
        system("pause");
    }
}

void mostrarArchivoUsuariosInactivos()
{
    usuario un_usuario;
    FILE * archi;

    archi = fopen(ArchiUsers, "rb");

    if(archi != NULL)
    {
        while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0)
        {
            mostrarUsuarios(un_usuario);
        }
        system("pause");
    }
}

void mostrarUsuarios(usuario un_usuario)
{
    int i;
    char password[10];

    printf("Id:      \t%d\n", un_usuario.id);
    printf("Nombre: \t%s\n", un_usuario.nombre);
    printf("Apellido: \t%s\n", un_usuario.apellido);
    printf("Usuario: \t%s\n", un_usuario.usuario);


    fDecrypting(password, un_usuario.pass);
    printf("Contra:  \t%s\n", password);


    printf("Activo: \t");
    if(un_usuario.eliminado == 0)
    {
        printf("Si\n");
    }
    else
    {
        printf("No\n");
    }
    printf("\n");
    for(i = 0; i < 20; i++)
    {
        printf("%c", Guion);
    }
    printf("\n\n");
}

int validaNombre(usuario mi_usuario)
{
    int check = 0;

    FILE * archi;
    usuario un_usuario;

    archi = fopen(ArchiUsers, "r+b");

    while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0)
    {
        if(strcmp(mi_usuario.usuario, un_usuario.usuario) == 0)
        {
            check++;
        }
    }

    fclose(archi);

    return check;
}

void bajaUsuario(int id)
{
    int existe = 0;

    FILE * archi;
    usuario un_usuario;

    archi = fopen(ArchiUsers, "r+b");

    if(archi)
    {
        while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0 && existe != 1)
        {
            if(id == un_usuario.id)
            {
                un_usuario.eliminado = 1;
                fseek(archi, sizeof(usuario) * -1, SEEK_CUR);
                fwrite(&un_usuario, sizeof(usuario), 1, archi);
                existe = 1;
            }
        }

        if(existe == 1)
        {
            printf("Usuario correctamente eliminado.");
        }
        else
        {
            printf("El Id ingresado no existe o esta mal ingresado.");
        }
        system("pause");
    }
    fclose(archi);
}

int validaIdParaModificar(int id)
{
    int encontrado = 0;

    FILE * archi;
    usuario un_usuario;

    archi = fopen(ArchiUsers, "rb");

    while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0 && encontrado == 0)
    {
        if(id == un_usuario.id && un_usuario.eliminado == 0)
        {
            encontrado = 1;
        }
    }

    if(encontrado == 0)
    {
        color(252);
        printf("Error! La id se encuentra inactiva o no es correcta.\n");
        color(240);
    }
    return encontrado;
}

void menuModificacionUsuario(int id)
{
    int elec, existe = 1;

    FILE * archi;
    usuario un_usuario;

    archi = fopen(ArchiUsers, "r+b");

    if(archi != NULL)
    {
        while(fread(&un_usuario, sizeof(usuario), 1, archi) > 0 && existe == 1)
        {
            if(id == un_usuario.id)
            {
                while(elec != 5)
                {
                    system("cls");
                    mostrarUsuarios(un_usuario);
                    printf("Que campo quiere modificar?\n");
                    printf("1.- Nombre.\n");
                    printf("2.- Apellido.\n");
                    printf("3.- Nombre de usuario.\n");
                    printf("4.- Contrase%ca.\n", 164);
                    printf("5.- Cancelar.\n");
                    gotoxy(28, 9);
                    scanf("%d", &elec);

                    switch(elec)
                    {
                    case 1:
                        system("cls");
                        un_usuario = modificarNombreUsuario(un_usuario);
                        printf("Usuario correctamente modificado. ");
                        break;
                    case 2:
                        system("cls");
                        un_usuario = modificarApellidoUsuario(un_usuario);
                        printf("Usuario correctamente modificado. ");
                        break;
                    case 3:
                        system("cls");
                        un_usuario = modificarNomDeUsuario(un_usuario);
                        printf("Usuario correctamente modificado. ");
                        break;
                    case 4:
                        system("cls");
                        un_usuario = modificarContraUsuario(un_usuario);
                        printf("Usuario correctamente modificado. ");
                        break;
                    }
                    fseek(archi, sizeof(usuario) * -1, SEEK_CUR);
                    fwrite(&un_usuario, sizeof(usuario), 1, archi);
                    existe = 0;
                }
            }
        }

        if(existe == 1)
        {
            printf("El Id ingresado no existe o esta mal ingresado. ");
        }
        gotoxy(0,15);
        system("pause");
    }
    fclose(archi);

}

usuario modificarNombreUsuario(usuario un_usuario)
{
    printf("Nombre actual: %s\n", un_usuario.nombre);
    printf("Ingrese el nuevo nombre del usuario: ");
    fflush(stdin);
    gets(un_usuario.nombre);
    return un_usuario;
}

usuario modificarApellidoUsuario(usuario un_usuario)
{
    printf("Apellido actual: %s\n", un_usuario.apellido);
    printf("Ingrese el nuevo apellido del usuario: ");
    fflush(stdin);
    gets(un_usuario.apellido);
    return un_usuario;
}

usuario modificarContraUsuario(usuario un_usuario)
{
    int passAscii[2][5];
    int passEncriptada[2][5];
    int dimensionContra;
    int errores = 0;
    int i, j;
    char contra[10];

    do
    {
        if(errores != 0)
        {
            color(252);
            printf("Error! La contrase%ca ingresada no es valida.\n", 164);
            color(240);
            errores = 0;
            for(i=0; i<strlen(contra); i++)
            {
                contra[i]=0;
            }
        }
        printf("Ingrese la nueva contrase%ca del usuario: ", 164);
        fflush(stdin);
        gets(contra);
        if(strlen(contra) != 10)
        {
            errores = 1;
        }
        else
        {
            for(i=0; i<strlen(contra); i++)
            {
                if(!isalnum(contra[i]) && !isspace(contra[i]))
                {
                    errores = 1;
                }
            }
        }
    }
    while(errores != 0);

    dimensionContra = fPass2Matrix(contra, passAscii);
    fMatrizEncrypting(passAscii, passEncriptada, dimensionContra);

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 5; j++)
        {
            un_usuario.pass[i][j] = passEncriptada[i][j];
        }
    }

    return un_usuario;
}

usuario modificarNomDeUsuario(usuario un_usuario)
{
    int check = 0;
    printf("Nombre de usuario actual: %s\n", un_usuario.usuario);
    do
    {
        printf("Ingrese el nuevo nombre de usuario: ");
        fflush(stdin);
        gets(un_usuario.usuario);
        check = validaNombre(un_usuario);
        if(check != 0)
        {
            color(252);
            printf("Error! El nombre ingresado ya esta en uso.");
            color(240);
            system("pause");
            check = 0;
        }
    }
    while(check != 0);

    return un_usuario;
}

int iniciaSesion(int sesion)
{
    char nombreDusuario[20], contraaComprobar[10], contraDecodificada[11], elec = 's';
    int error = 0, i;

    usuario un_usuario;
    FILE * archi;

    archi = fopen(ArchiUsers, "rb");

    if(archi)
    {
        do
        {
            if(error != 0)
            {
                color(252);
                printf("Error! El nombre ingresado no existe.\n");
                color(240);
                error = 0;
                fseek(archi, 0, SEEK_SET);
            }
            printf("Ingrese el nombre de usuario: ");
            fflush(stdin);
            gets(nombreDusuario);
            do
            {
                fread(&un_usuario, sizeof(usuario), 1, archi);
            }
            while (strcmp(un_usuario.usuario, nombreDusuario) != 0 && !feof(archi));

            if(feof(archi))
            {
                error = 1;
            }
            else
            {
                do
                {
                    if(error != 0)
                    {
                        color(252);
                        printf("Error! La contrase%ca ingresada no es correcta.\n", 164);
                        color(240);
                        error = 0;
                    }
                    printf("Ingrese la contrase%ca: ", 164);
                    fflush(stdin);
                    gets(contraaComprobar);
                    fDecrypting(contraDecodificada, un_usuario.pass);

                    if(strlen(contraDecodificada) < strlen(contraaComprobar))
                    {
                        error = 1;
                    }
                    else
                    {
                        if(strncmp(contraDecodificada, contraaComprobar, strlen(contraDecodificada) - 1) == 0)
                        {
                            sesion = 1;
                            printf("Inicio de sesion exitoso!\n");
                        }
                        else
                        {
                            error = 1;
                        }
                    }
                }
                while(error != 0);
            }
        }
        while(error != 0);
    }
    else
    {
        printf("Imposible iniciar sesion, archivo inexistente.\n");
        printf("Desea crear un nuevo usuario? s/n\n");
        fflush(stdin);
        scanf("%c", &elec);
        if(elec != 'n')
        {
            system("cls");
            cargarUsuario();
        }
        else
        {
            printf("Hasta pronto!");
            exit(0);
        }
    }
    system("pause");
    return sesion;
}

///MENU USUARIOS

void menuUsuarios()
{
    int elec=0, i, id = 0;
    while(elec != 5)
    {
        system("cls");
        for(i=0; i<60; i++)
        {
            gotoxy(i,0);
            printf("%c", 196);
        }
        for(i=0; i<20; i++)
        {
            gotoxy(0,i);
            printf("%c", 179);
        }
        for(i=0; i<20; i++)
        {
            gotoxy(60,i);
            printf("%c", 179);
        }
        for(i=0; i<60; i++)
        {
            gotoxy(i,20);
            printf("%c", 196);
        }
        for(i=0; i<60; i++)
        {
            gotoxy(i,4);
            printf("%c", 196);
        }
        gotoxy(0,0);
        printf("%c", 218);
        gotoxy(60,0);
        printf("%c", 191);
        gotoxy(0,20);
        printf("%c", 192);
        gotoxy(60,20);
        printf("%c", 217);
        gotoxy(0,4);
        printf("%c", 195);
        gotoxy(60,4);
        printf("%c", 180);
        gotoxy(23,2);
        printf("MEN%c USUARIOS", 163);
        gotoxy(23,3);
        for(i=0; i<13; i++)
        {
            printf("%c", 238);
        }
        gotoxy(8,6);
        printf("Elija una opci%cn:", 162);
        gotoxy(20,8);
        printf("1.- Cargar Usuario.");
        gotoxy(20,9);
        printf("2.- Mostrar Archivo Usuarios.");
        gotoxy(20,10);
        printf("3.- Dar de baja un usuario.");
        gotoxy(20,11);
        printf("4.- Modificar usuario.");
        gotoxy(20,12);
        printf("5.- Volver");
        gotoxy(26,6);
        scanf("%d", &elec);

        switch(elec)
        {
        case 1:
            system("cls");
            id = asignaId();
            cargarUsuario(id);
            break;
        case 2:
            system("cls");
            char activos = 's';
            printf("Desea mostrar los usuarios inactivos? s/n\n");
            fflush(stdin);
            scanf("%c", &activos);
            if(activos == 's')
            {
                mostrarArchivoUsuariosInactivos();
            }
            else
            {
                mostrarArchivoUsuariosActivos();
            }
            break;
        case 3:
            system("cls");
            printf("Ingrese la ID del usuario a dar de baja: ");
            scanf("%d", &id);
            bajaUsuario(id);
            break;
        case 4:
            system("cls");
            int valido;
            do
            {
                printf("Ingrese la id del usuario a modificar: ");
                scanf("%d", &id);
                valido = validaIdParaModificar(id);
            }
            while (valido == 0);
            menuModificacionUsuario(id);
            break;
        }
    }
}
