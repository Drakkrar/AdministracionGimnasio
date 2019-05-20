//Programa: 	CONTROL ADMINISTRATIVO WGP (WORLD GYM PROVIDENCIA)
//Elaborado:	Jose Francisco Daniel Ramos Sepulveda
//Fecha de entrega:	22 de mayo de 2018
/*************************************************************************/
/*
    GIMNASIO, en donde se administren los clientes, sus expedientes, así como
    el control de pago mensual de cada cliente. Los datos de los clientes, de
    los expedientes y de los pagos deben de estar contenidos en arreglos de
    estructuras. Para optimizar las estructuras debes de realizar relaciones
    entre las estructuras.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX 50



/*************************************************************************/
//          Estructuras;
typedef struct
{
    int id;
    char* nombre[20];
    char* sexo;
    char* fechaNacimiento[8];
    char* tipoSangre[2];
    char* email[30];
    char* seguroSocial[11];
    char* curp[18];
    //

}customers;

typedef struct
{

    char* fechaPago[8];
    int abono;
    // Trabajando en esto...
}pagos;

typedef struct
{
    int cliente;
    int membresiaActiva;
    int tipoMembresia;
    int costoMembresia;
    int indiceControlPagos;
    char* fechaRegistro[8];
    char* ultimaVisita[24];
    int adeudo;
    //
    pagos controlPagos[4];
}registro;

/*************************************************************************/
//      Archivos.
FILE *ptrCliente;
FILE *ptrExpedientes;
FILE *ptrPagos;

/*************************************************************************/
//      Variables globales:
//  Registro.
 registro expedientes[MAX];
int opcionRegistro, opcionSubmenuRegistro;
int banderaExpedienteEncontrado, banderaMenuOpcionModificaRegistro;
int indiceDeRegistro=0, folioRegistro= 1, capturadosTotales=0, codigoBusquedaRegistro;
char eliminarRegistro;
//  Clientes.
 customers cliente[MAX];
int opcionClientes, opcionSubmenuClientes;
int banderaClienteEncontrado, banderaMenuOpcionModificar;
int codigoBusquedaCliente, indiceCliente;
int ultimoVisitante;
//  Extras
char* fechaActual[8];
int inicioPrograma = 0;
int indicesEliminados[50], controlIndiceEliminados = 0;
/*************************************************************************/
//          Funciones
//  Menus
void verClientes();
void verRegistros();
void verPagos();
// Clientes
void clienteInfo();
void clienteModificar();
void registrarEntradas();
// Registros.
void registrosIniciarExpediente();
void registrosBorrar();
// Pagos
void pagosRegistrar();
void pagosConsultar();
void pagosVisualizar();
// Extras
int calcularCosto(int _tipoMembresia);
/*************************************************************************/
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
int main()
{
    int opcion_menu_principal;
    capturadosTotales++;
    //
    //      Inicializador de prueba
    //  Cliente

    cliente[0].id = 23;
    expedientes[0].cliente = 23;
    strcpy(cliente[0].nombre,"Jose Ramos");
    cliente[0].sexo = 'M';
    strcpy(cliente[0].fechaNacimiento,"03/09/98\0");
    strcpy(cliente[0].tipoSangre,"O+\0");
    strcpy(cliente[0].email,"jramossepulveda3@gmail.com\0");
    strcpy(cliente[0].seguroSocial,"11111111111\0");
    strcpy(cliente[0].curp,"RASF980903HJCMPR02\0");
    //  Expediente
    expedientes[0].cliente = cliente[0].id;
    expedientes[0].membresiaActiva = 1;
    expedientes[0].indiceControlPagos = 0;
    strcpy(expedientes[0].controlPagos->fechaPago,"05/16/19");
    expedientes[0].adeudo = -300;
    //


	do
    {
        if (inicioPrograma == 0)
        {
            printf("\tVersion 1.0-a\nPor favor ingrese la fecha actual en el siguiente formato: dd/mm/aa (01/12/19)\n:   ");
            scanf("%8s", fechaActual);
            printf("Fecha actual:  %s\n\n", fechaActual);
            inicioPrograma++;

        }
        else
        {
            printf("\nMENU PRINCIPAL\n1. Clientes \n2. Registro \n3. Control de pagos. \n4. Reporte.\n5. Salir.\n\n");
            printf("Selecciona una opcion: ");
            scanf("%i",&opcion_menu_principal);
            switch (opcion_menu_principal)
                {
                    case 1:	verClientes();
                            break;
                    case 2:	verRegistros();
                            break;
                    case 3:	verPagos();
                            break;
                    case 4:	printf("\nEstoy haciendo algo ahhhh....");
                            return 0;
                    default: printf("\nError, opcion equivocada\n\n");
                            system("pause");
                }
            system ("cls");
        }
	}while(opcion_menu_principal!=5);
	return 0;
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
/*************************************************************************/
//                        Todo lo que tiene que ver con clientes

void verClientes()
{
    int opcion_menu_clientes;
    opcionSubmenuClientes = opcion_menu_clientes;

    do
    {
        system("CLS");
        fflush(stdin);
        printf("CLIENTES: \n\t1.- Ver todos los clientes actuales.\n\t2.- Modificar informacion personal.\n\t3.- Iniciar proceso de entrada.\n\t4.- Regresar.\n");
        printf("Ingrese una opcion:\t");
        scanf("%i", &opcion_menu_clientes);
        switch (opcion_menu_clientes)
        {
            case 1:
                clienteInfo();
                break;
            case 2:
                clienteModificar();
                break;
            case 3:
                registrarEntradas();
                break;
            case 4:
                printf("Saliendo...\n");
                return;
            default:
                printf("Algo ingresaste mal...");
        }
    }while(opcion_menu_clientes != 4);

    system("CLS");
}

void clienteInfo()
{

    int opcion_clienteInfo;
    char buffer[30];
    buffer[0] = '\0';

    do
    {
        system("CLS");
        fflush(stdin);

        if (capturadosTotales == 0)
            printf("\nActualmente, no existe NINGUN cliente capturado.\n");
        else
        {
            for (int i = 0; i < capturadosTotales; i++)
            {
                fflush(stdin);
                fflush(stdout);
                printf("----------------------------------------------------\n");
                printf("Codigo:\t\t %i \t|INDICE| \t%i\n",cliente[i].id,i);
                printf("Nombre:\t\t %s\n",cliente[i].nombre);
                printf("Sexo:\t\t %c\n",cliente[i].sexo);
                printf("Fecha de nacimiento:\t\t %s\n\0",cliente[i].fechaNacimiento);
                printf("Tipo de Sangre:\t\t %s\n\0",cliente[i].tipoSangre);
                printf("Email:\t\t %s\n\0",cliente[i].email);
                printf("IMSS:\t\t %s\n\0",cliente[i].seguroSocial);
                printf("CURP:\t\t %s\n\0",cliente[i].curp);
                printf("\n");
                printf("Fecha ultimo Pago:\t\t %s\n",expedientes[i].controlPagos->fechaPago);
                printf("Adeudo:\t\t %i\n",expedientes[i].adeudo);
                printf("Fecha de Registro:\t\t %s\n",expedientes[i].fechaRegistro);
                printf("Membresia Activa:\t\t %i\n",expedientes[i].membresiaActiva);
                printf("----------------------------------------------------\n");
                printf("Ultima visita:\t\t %s\n",expedientes[i].ultimaVisita);
                printf("----------------------------------------------------\n");

            }
        }

        printf("Clientes: %i\n", capturadosTotales);
        printf("Presione ESC para salir, cualquier otra letra para continuar");
        opcion_clienteInfo = getch();
        fflush(stdin);
    }while(opcion_clienteInfo != 27);
}


/*************************************************************************/

void clienteModificar()
{
    int opcion_clienteModificar, opcionSwitchModificar;
    int booleano;

    do
    {
        system("CLS");
        fflush(stdin);
        if (capturadosTotales == 0)
            printf("\nActualmente, no se ha registrado NINGUN cliente.\n");
        else
        {
            printf("Codigo del cliente a visualizar:        ");
            scanf("%i",&codigoBusquedaCliente);
            // Opcion....
            //
            for (int i = 0; i < capturadosTotales; i++)
            {
                    if (codigoBusquedaCliente == cliente[i].id)
                    {
                        printf("Codigo encontrado.");
                        printf("----------------------------------------------------\n");
                        printf("Codigo:\t\t %i |INDICE| \t%i\n",cliente[i].id,i);
                        printf("Nombre:\t\t %s\n",cliente[i].nombre);
                        printf("Sexo:\t\t %c\n",cliente[i].sexo);
                        printf("Fecha de nacimiento:\t\t %s\n",cliente[i].fechaNacimiento);
                        printf("Tipo de Sangre:\t\t %s\n",cliente[i].tipoSangre);
                        printf("Email:\t\t %s\n",cliente[i].email);
                        printf("IMSS:\t\t %s\n",cliente[i].seguroSocial);
                        printf("CURP:\t\t %s\n",cliente[i].curp);
                        printf("----------------------------------------------------\n");
                        // Auxiliares.
                        banderaClienteEncontrado = 1;
                        indiceCliente = i;
                    }
                    else
                        banderaClienteEncontrado = 0;
            }
                if (banderaClienteEncontrado == 0)
                    printf("\nNo hay registros con el codigo: %i", codigoBusquedaCliente);
                else
                {
                    printf("\nSeleccione campo a editar:    ");
                    printf("\n(1) Tipo de Sangre\t(2) Email\t(3) IMSS\t(4) CURP\n");
                    scanf("%i",&opcionSwitchModificar);
                    fflush(stdin);
                    switch(opcionSwitchModificar)
                    {
                        case 1:
                            printf("Ingrese nuevo tipo de sangre:     ");
                            scanf("%2s", cliente[indiceCliente].tipoSangre);
                            fflush(stdin);
                            break;
                        case 2:
                            printf("Ingrese nuevo email:     ");
                            scanf("%30s", cliente[indiceCliente].email);
                            fflush(stdin);
                            break;
                        case 3:
                            printf("Ingrese nuevo numero de seguro social:     ");
                            scanf("%11s", cliente[indiceCliente].seguroSocial);
                            fflush(stdin);
                            break;
                        case 4:
                            printf("Ingrese nueva CURP:     ");
                            scanf("%18s", cliente[indiceCliente].curp);
                            fflush(stdin);
                            break;
                    }
                }
        }
        printf("\nPresione ESC para salir, cualquier otra letra para continuar");
        opcion_clienteModificar = getch();
        fflush(stdin);
    }while(opcion_clienteModificar != 27 );

    banderaClienteEncontrado = 0;
    codigoBusquedaCliente = 0;

}
/*************************************************************************/
void registrarEntradas()
{
    int opcion_registrarEntradas;

    do
    {
        system("CLS");
        fflush(stdin);

        if (capturadosTotales == 0)
            printf("\nNo hay clientes registrados...");
        else
            {
                printf("Codigo del cliente:        ");
                scanf("%i",&codigoBusquedaCliente);
                for (int i = 0; i < capturadosTotales; i++)
                {
                    if (codigoBusquedaCliente == cliente[i].id)
                    {
                        printf("Codigo encontrado.");
                        printf("----------------------------------------------------\n");
                        printf("Codigo:\t\t %i |INDICE| \t%i\n",cliente[i].id,i);
                        printf("Nombre:\t\t %s\n",cliente[i].nombre);
                        printf("Sexo:\t\t %c\n",cliente[i].sexo);
                        printf("----------------------------------------------------\n");
                        // auxiliares
                        indiceCliente = i;
                        banderaClienteEncontrado = 1;
                    }
                    else
                    {
                        printf("\nEl cliente | %i | no se encontro en nuestra base de datos\n", codigoBusquedaCliente);
                        banderaClienteEncontrado = 0;
                    }
                }
                if (banderaClienteEncontrado == 1 && expedientes[indiceCliente].membresiaActiva == 1)
                {
                    system("CLS");
                    printf("\n\n\n\t\tBienvenido!");
                    if (expedientes[indiceCliente].adeudo < 0)
                    {
                        printf("\n Tiene un saldo pendiente. Por favor liquide su cuenta para no perder los beneficios de su membresia\n");
                        printf("\nAdeudo actual: %i", expedientes[indiceCliente].adeudo);
                        ultimoVisitante = codigoBusquedaCliente;
                        strcpy(expedientes[indiceCliente].ultimaVisita, fechaActual);
                    }
                }
                else if (expedientes[indiceCliente].membresiaActiva != 1)
                    printf("\nSu membresia ha sido suspendida, por favor acuda administracion para solucionarlo cuanto antes\n");
            }
        printf("\nPresione ESC para salir, cualquier otra letra para continuar");
        opcion_registrarEntradas = getch();
        fflush(stdin);
    }while(opcion_registrarEntradas != 27);


    indiceCliente = 0;
    banderaClienteEncontrado = 0;

}
//          Fin de funciones para menu Cliente
/*************************************************************************/
//          Inicio de funciones para menu Registros.
void verRegistros()
{
    int opcion_menu_registro;

    do
    {
        system("CLS");
        fflush(stdin);
        printf("REGISTRO: \n\t1.- Abrir expediente nuevo.\n\t2.- Borrar expediente.\n\t3.- Salir.\nIngrese opcion a elegir:     ");
        scanf("%i", &opcion_menu_registro);
        switch (opcion_menu_registro)
        {
            case 1:
                registrosIniciarExpediente();
                break;
            case 2:
                printf("\a\nActualmente no es posible borrar informacion de clientes \n");
                getch();
                break;
            case 3:
                printf("\nSaliendo...\n");
                return;
            default:
                printf("\a\nAlgo ingresaste mal...\n");
        }
    }while(opcion_menu_registro != 3);

    system("CLS");
}
/*************************************************************************/
void registrosIniciarExpediente()
{

    int local_Indice, local_Id, opcion_iniciarExpediente;

    if (capturadosTotales >= 50)
    {
        printf("\a\t\nSe alcanzo el limite de memoria!\n");
        system("pause");
        return;
    }
    else
    {
        do
        {
            fflush(stdin);
            if (capturadosTotales > 0)
            {
                local_Indice = 1 + indiceDeRegistro;
                local_Id = 1 + folioRegistro;
            }
            else
            {
                local_Id = folioRegistro;
                local_Indice = indiceDeRegistro;
            }
            fflush(stdin);
            printf("----------------------------------------------------\n");
            printf("\tID: %i\t\t\t Indice: %i\n",local_Id, local_Indice);
            printf("----------------------------------------------------\n");
            // Inicio de formulario:
            printf("\nºIngrese el nombre:     ");
            gets(cliente[local_Indice].nombre);
            fflush(stdin);
            printf("\nºIngrese el sexo [M/F]:     ");
            scanf("%1c", &cliente[local_Indice].sexo);
            fflush(stdin);
            printf("\nºIngrese la fecha de nacimiento [dd/mm/aa]:     ");
            gets(cliente[local_Indice].fechaNacimiento);
            fflush(stdin);
            printf("\nºIngrese el tipo de sangre:     ");
            gets(cliente[local_Indice].tipoSangre);
            fflush(stdin);
            printf("\nºIngrese el correo electronico:     ");
            gets(cliente[local_Indice].email);
            fflush(stdin);
            printf("\nºIngrese numero de seguro social [IMSS]:     ");
            gets(cliente[local_Indice].seguroSocial);
            fflush(stdin);
            printf("\nºIngrese CURP:     ");
            gets(cliente[local_Indice].curp);
            fflush(stdin);
            printf("----------------------------------------------------\n");
            printf("\nIngrese tipo de membresia\n [1 - Normal] [2 - Estudiante] [3 - Trabajador] [4 - Coach] [5 - VIP]\n:  ");
            scanf("%i", &expedientes[local_Indice].tipoMembresia);
            // Valores inicializados por defecto.
            strcpy(expedientes[local_Indice].fechaRegistro, fechaActual);
            expedientes[local_Indice].indiceControlPagos = 0;
            expedientes[local_Indice].costoMembresia = calcularCosto(expedientes[local_Indice].tipoMembresia);
            expedientes[local_Indice].adeudo -= expedientes[local_Indice].costoMembresia;
            expedientes[local_Indice].cliente = local_Id;
            cliente[local_Indice].id = local_Id;
            printf("----------------------------------------------------\n");

            // Asignadores.
                indiceDeRegistro = local_Indice;
                folioRegistro = local_Id;

            capturadosTotales++;


            printf("\nPresione ESC para salir, cualquier otra letra para continuar capturando datos.");
            opcion_iniciarExpediente = getch();
            fflush(stdin);
        }while(opcion_iniciarExpediente != 27);

    }
}
/*************************************************************************/
//                      BUG DE MEMORIA AH!!!!!!!!!!!!!!!!!      -1073741819 (0xC0000005)
/* void registrosBorrar()
{
    int local_indiceCliente, local_banderaEncontrado;
    char* buffer[] = {"\0"};
    char confirmarEliminar;

    system("CLS");
    fflush(stdin);

    printf("Por seguridad, solo esta permitido eliminar 1 registro a la ves.\n\tCodigo a eliminar:      ");
    scanf("%i", &codigoBusquedaRegistro);
    for (int i = 0; i < MAX; i++)
    {
        if (codigoBusquedaRegistro == cliente[i].id)
        {
            local_indiceCliente = i;
            local_banderaEncontrado = 1;
        }
    }
    if (local_banderaEncontrado == 1)
    {
        fflush(stdin);
        printf("Se ha encontrad el codigo ingresado.");
        printf("----------------------------------------------------\n");
        printf("Codigo:\t\t %i |INDICE| \t%i\n",cliente[local_indiceCliente].id,local_indiceCliente);
        printf("Nombre:\t\t %s\n",cliente[local_indiceCliente].nombre);
        printf("Sexo:\t\t %c\n",cliente[local_indiceCliente].sexo);
        printf("Fecha de nacimiento:\t\t %s\n",cliente[local_indiceCliente].fechaNacimiento);
        printf("Tipo de Sangre:\t\t %s\n",cliente[local_indiceCliente].tipoSangre);
        printf("Email:\t\t %s\n",cliente[local_indiceCliente].email);
        printf("IMSS:\t\t %s\n",cliente[local_indiceCliente].seguroSocial);
        printf("CURP:\t\t %s\n",cliente[local_indiceCliente].curp);
        printf("----------------------------------------------------\n");
        printf("\t\a¿Esta seguro de que desea eliminar el registro? [s o S para SI]\n");
        scanf("%1c", &confirmarEliminar);
        if (confirmarEliminar == 's' || confirmarEliminar == 'S')
        {
            if (expedientes[local_indiceCliente].controlPagos->adeudo < 0)
            {
                fflush(stdin);
                printf("\nNo se puede eliminar ya que el cliente tiene un adeudo pendiente\n");
                system("pause");
            }
            else
            {
            // Estructura customers variable cliente[]

                strcpy(cliente[local_indiceCliente].nombre, buffer);
                strcpy(cliente[local_indiceCliente].sexo, buffer);
                strcpy(cliente[local_indiceCliente].fechaNacimiento, buffer);
                strcpy(cliente[local_indiceCliente].tipoSangre, buffer);
                strcpy(cliente[local_indiceCliente].email, buffer);
                strcpy(cliente[local_indiceCliente].seguroSocial, buffer);
                strcpy(cliente[local_indiceCliente].curp, buffer);
            // Estructura registro y controlPagos variable expedientes[]

                expedientes[local_indiceCliente].membresiaActiva = 0;
                expedientes[local_indiceCliente].controlPagos->costoMembresia = 0;
                expedientes[local_indiceCliente].controlPagos->tipoMembresia = 0;
                strcpy(expedientes[local_indiceCliente].fechaRegistro, buffer);
                strcpy(expedientes[local_indiceCliente].controlPagos->fechaPago, buffer);

                // Borrar ID y guardarlos

                indicesEliminados[controlIndiceEliminados] = cliente[local_indiceCliente].id;

                cliente[local_indiceCliente].id = 0;
                expedientes[local_indiceCliente].cliente = 0;

                controlIndiceEliminados++;
            }
        }
    }
    else
    {
        printf("\a\n No se ha encontrado al cliente: %i \n", codigoBusquedaRegistro);
        system("pause");
    }

}*/

//                  Fin de todo lo que tiene que ver con registros..
/*************************************************************************/
//                  Inicio de menu Pagos.
void verPagos()
{
    int opcion_menu_pagos;

    do
    {
        system("CLS");
        fflush(stdin);
        printf("PAGOS: \n\t1.- Registrar pago.\n\t2.- Consultar adeudo.\n\t3.- Ver registro de pagos.\n\t4.- Regresar.");
        scanf("%i", &opcion_menu_pagos);
        switch (opcion_menu_pagos)
        {
            case 1:
                pagosRegistrar();
                break;
            case 2:
                printf("Aqui consultare el adeudo.\n");
                break;
            case 3:
                printf("Aqui visualizare los ultimos 3 pagos.\n");
                break;
            case 4:
                printf("Saliendo...");
                return;
            default:
                printf("Algo ingresaste mal...");
        }
    }while(opcion_menu_pagos != 4);

    system("CLS");
}
/*************************************************************************/
void pagosRegistrar()
{
    int opcion_pagosRegistrar;
    int local_indiceControlPagos, local_ingreseDinero;

    do
    {
        system("CLS");
        fflush(stdin);

        printf("Codigo de cliente a registrar pago:    ");
        scanf("%i", &codigoBusquedaRegistro);
        for (int i = 0; i < capturadosTotales; i++)
        {
            if (codigoBusquedaRegistro == expedientes[i].cliente || codigoBusquedaRegistro == cliente[i].id)
            {
                indiceCliente = i;
                banderaClienteEncontrado = 1;
                local_indiceControlPagos = expedientes[i].indiceControlPagos;
            }
            else
            {
                banderaClienteEncontrado = 0;
                indiceCliente = 0;
                local_indiceControlPagos = 0;
            }
        }
        if (banderaClienteEncontrado == 0)
            printf("\n\a Cliente no encontrado\n");
        else if (banderaClienteEncontrado == 1)
        {
            if (expedientes[indiceCliente].adeudo > 0)
                printf("\n\tEl cliente no cuenta con adeudos.");
            else
            {
                fflush(stdin);
                printf("----------------------------------------------------\n");
                printf("\t\tAdeudo: %i\n", expedientes[indiceCliente].adeudo);
                printf("Dinero recibido :     ");
                scanf("%i", &local_ingreseDinero);
                printf("Regrese cambio: \t%i\n", local_ingreseDinero+expedientes[indiceCliente].adeudo);
                printf("----------------------------------------------------\n");

                // Asignadores de memoria.
                strcpy(expedientes[indiceCliente].controlPagos[local_indiceControlPagos].fechaPago,fechaActual);
                expedientes[indiceCliente].controlPagos[local_indiceControlPagos].abono = local_ingreseDinero;
                expedientes[indiceCliente].indiceControlPagos++;
            }
            // Aqui me quede 05/20/19
        }



        printf("\nPresione ESC para salir, cualquier otra letra para continuar capturando datos.");
        opcion_pagosRegistrar = getch();
        fflush(stdin);
    }while(opcion_pagosRegistrar != 27);
}

/*************************************************************************/
//          Extras

int calcularCosto(int _tipoMembresia)
{
    int costo;
    switch (_tipoMembresia)
    {
        case 1:
            costo = 300;        // Cualquier usuario normal.
            break;
        case 2: case 3:         // Estudiantes y familiares de colaboradores.
            costo = 150;
            break;
        case 4:
            costo = 200;        // Entrenadores, no reciben una paga pero se les permite cobrar sus servicios a los clientes.
            break;
        case 5:
            costo = 500;        // Reciben trato preferencial entre otros servicios.
            break;
    }
    return costo;
}
