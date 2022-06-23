#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "Menues.h"
#include "Consumos.h"
#include "Clientes.h"



// ============================== menus =============================================== //

void menuInicial(){
    char opcion;
    do{
        system("cls");
        printf("\n       Menu Inicial\n\n");
        printf("\n Ingrese lo que desea hacer:");
        printf("\n                            1.Consultar informacion de un cliente");
        printf("\n                            2.Informacion del sistema");
        printf("\n                            3.Ayuda");
        printf("\n                            ESC Para finalizar el programa\n");
        opcion = getch();

        switch(opcion){
            case ESC:
                // finaliza el programa, va vacio asi no entra al default
                break;
            case 49:
                consultaInfoCliente(A_CLIENTES);
                break;
            case 50:

                printf("menu sistema");
                menuSistema();
                break;
            case 51:
                funcionAyuda();
                break;
        }
    }while(opcion!=ESC);
}

void consultaInfoCliente(char nombreDelArchivo[]){
    FILE *arch = fopen(nombreDelArchivo, "rb");
    char opcion = 0;
    int id = -1;

    if(arch){
        do{
            system("cls");
            printf("\n       Menu Inicial -> Consultar informacion de un cliente\n\n");
            printf("\n 1. Buscar por Dni");
            printf("\n 2. Buscar por Movil\n");
            printf("\n ESC para cancelar\n");
            opcion = getch();
        }while(opcion!=ESC && opcion!=49 && opcion!=50);

        switch(opcion){
            case ESC:
                // para salir de este menu
                break;
            case 49:
                ingresaYValidaDni(arch, &id, &opcion);
                break;
            case 50:
                ingresaYValidaMovil(arch, &id, &opcion);
                break;
        }
        fclose(arch);
    }else{
        printf("\n\n   No se pudo abrir el archivo de clientes. ");
        system("pause");
    }
    if(opcion != ESC){
        menuClientes(id);
    }
}

void menuClientes(int id){
    char opcion;
    stClientes cli;

    do{
        system("cls");
        printf("\n       Menu Inicial -> Consultar informacion de un cliente\n\n");
        printf("\n Ingrese 1: Informacion del cliente");
        printf("\n Ingrese 2: Modificar Datos del cliente");
        printf("\n Ingrese 3: Para buscar un consumo por dia");
        printf("\n Ingrese 4: Para buscar consumos por mes");
        printf("\n Ingrese 5: Para dar de baja/alta");
        printf("\n Ingrese 6: Para ver la factura de un mes en particular");
        printf("\n Ingrese 7: Para crear un nuevo consumo");
        printf("\n ingrese ESC para volver al menu principal");
        opcion = getch();

        switch(opcion){
            case ESC:
                // para salir de este menu, va vacio asi no entra al default
                break;
            case 49:
                system("cls");
                cli = buscaCliente(id, A_CLIENTES);
                printf("\n       Menu Inicial -> Consultar informacion de un cliente\n\n");
                muestraInfoCliente(cli);
                printf("\n\n");
                system("pause");
                break;
            case 50:
                menuModificaDatosCliente(id, A_CLIENTES);
                break;
            case 51:
                buscarConsumosXDia(id, A_CONSUMOS);
                break;
            case 52:
                listaConsumosCliente(id, A_CONSUMOS);
                break;
            case 53:
                cambiaEstadoClientes(id, A_CLIENTES);
                break;
            case 54:
                muestraFacturaMes(id, A_CONSUMOS);
                break;
            case 55:
                cargaUnConsumo(id);
                break;
        }
    }while(opcion!=ESC);
}

// ============================== menus ayuda =============================================== //

void funcionAyuda(){
    system("cls");
    printf("\n       Menu Inicial -> Menu ayuda\n\n");
    printf("\n En el menu clientes vas a encontrar herramientas para la manipulacion y modificacion de un cliente en especifico,\n este se busca por su numero de DNI.");
    printf("\n Las operaciones que se pueden efectuar en este menu son:\n\n");
    printf("    %c Informacion del cliente.\n    %c Modificacion de los datos del cliente.\n    %c Informacion y manipulacion de los consumos del cliente (se pueden dar de baja o crear nuevos).\n    %c Las facturas mensuales del cliente.", 249, 249, 249, 249);
    printf("\n\n En el menu sistemas vas a encontrar herramientas para cargar nuevos clientes y ver informacion relevante de todos\n los clientes.\n Las operaciones que se pueden efectuar en este menu son:\n\n");
    printf("    %c Creacion de un nuevo cliente.\n    %c Listado de todos los clientes.\n    %c Ingresos percibidos", 249, 249, 249);
    printf("\n\n\n Siempre que se termine una operacion seras llevado al menu anterior de esta y para salir de cada menu es necesario\n presionar la tecla ESC.");
    printf("\n Para el correcto funcionamiento del programa asegurese tener los archivos de datos \"clientes.dat\" y \"consumos.dat\".");

    printf("\n\n\n   Ingrese cualquier tecla para continuar");
    getch();
}

// ============================== menus sistema =============================================== //
void menuSistema(){
    char opc;
   do{
        system("cls");
        printf("\n       Menu Inicial -> Informacion del sistema\n\n");
        printf("\n Ingrese lo que desea hacer:");
        printf("\n                            1. Ingresar nuevo cliente");
        printf("\n                            2. Consultar lista de clientes");
        printf("\n                            3. Ingresos percibidos");
        printf("\n                            ESC Para volver al menu principal\n");
        opc = getch();
        menuSwSistema(opc);
   }while(opc!=ESC);
}

void menuSwSistema(char opc){
    FILE *arch;
    char i;
    switch (opc){
        case ESC:
            break;
        case 49:
            cargaArchivoClientes(A_CLIENTES);
            break;
        case 50:
            arch=fopen(A_CLIENTES, "rb");
            system("cls");
            printf("\n       Menu Inicial -> Informacion del sistema\n\n");
            listaClientes(arch);
            fclose(arch);
            break;
        case 51:
            arch=fopen(A_CONSUMOS,"rb");
            do{
                i=menuIngresos();
                consumosEmpresa(arch,i);
            }while((i<49 && i>50) || i != ESC);
            fclose(arch);
            break;
    }
}
