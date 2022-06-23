#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "Menues.h"
#include "Consumos.h"
#include "Clientes.h"

// ============================== Muestra lista clientes =============================================== //

void muestraUnCliente(stClientes cliente,int i){
    printf("\n %d\t%d\t          %s %s, %s  ",i,cliente.nroCliente,cliente.dni, cliente.apellido,cliente.nombre);
}

void listaClientes(FILE *arch){
    stClientes c[100];
    int validos = 0;
    stClientes aux;
    while(fread(&aux,sizeof(stClientes),1,arch)>0 && validos < 100){
        if(aux.eliminado==0){
            c[validos] = aux;
            validos++;
        }
    }
    ordenaXApellido(c,validos);
    muestraArreglo(c,validos);
}

int menorApellido(stClientes c[],int validos,int inicio){
    stClientes menor = c[inicio];
    int posMenor = inicio;
    for(int i = inicio + 1; i<validos; i++){
        if(strcmpi(menor.apellido,c[i].apellido)>0){
            menor = c[i];
            posMenor = i;
        }
    }
    return posMenor;
}

void ordenaXApellido(stClientes c[],int validos){
    stClientes aux;
    int pos;
    for(int i=0; i<validos-1;i++){
        pos = menorApellido(c,validos,i);
        aux = c[pos];
        c[pos] = c[i];
        c[i] = aux;
    }
}

void muestraArreglo(stClientes c[],int validos){
    printf("\n Nro. | Nro. de Cliente |   DNI   | Apellido y Nombre  ");
    for(int i=0; i<validos; i++){
      muestraUnCliente(c[i],i+1);
    }
    printf("\n");
    system("pause");
}

// ============================== sistema clientes =============================================== //

void ingresaYValidaDni(FILE *arch, int *id, char *opcion){
    char dni[10];
    do{
        system("cls");
        printf("\n       Menu Inicial -> Consultar informacion de un cliente\n\n");
        printf("\n\n Ingrese el numero de documento del cliente: ");
        fflush(stdin);
        gets(dni);
        *id = buscaIdXDni(arch, dni);
        if(*id == -1){
            printf("\n\n   Ingreso un dni invalido, presione cualquier tecla y vuelva a intentarlo, ESC para cancelar");
            *opcion = getch();
        }
    }while(*opcion!=ESC && *id==-1);
}

void ingresaYValidaMovil(FILE *arch, int *id, char *opcion){
    char movil[12];
    do{
        system("cls");
        printf("\n       Menu Inicial -> Consultar informacion de un cliente\n\n");
        printf("\n\n Ingrese el movil del cliente: ");
        fflush(stdin);
        gets(movil);
        *id = buscaIdXMovil(arch, movil);
        if(*id == -1){
            printf("\n\n   Ingreso un numero invalido, presione cualquier tecla y vuelva a intentarlo, ESC para cancelar");
            *opcion = getch();
        }
    }while(*opcion!=ESC && *id==-1);
}

int validacionXNroCliente(FILE *arch, int nroClienteAux){
    rewind(arch);
    stClientes aux;
    int flag = 0;
    while(flag == 0 && fread(&aux,sizeof(stClientes),1,arch)>0){
        if(aux.nroCliente == nroClienteAux){
            flag = 1;
        }
    }
    return flag;
}

int buscaIdXDni(FILE *arch, char dni[]){
    rewind(arch);
    int flag = 1;
    int id = -1;
    stClientes cli;

    while(flag == 1 && fread(&cli, sizeof(stClientes), 1, arch)>0){
        if(strcmpi(dni,cli.dni)==0){
            flag=0;
            id=cli.id;
        }
    }
    return id;
}

int buscaIdXMovil(FILE *arch, char movil[]){
    rewind(arch);
    int flag = 1;
    int id = -1;
    stClientes cli;

    while(flag == 1 && fread(&cli, sizeof(stClientes), 1, arch)>0){
        if(strcmpi(movil,cli.movil)==0){
            flag=0;
            id=cli.id;
        }
    }
    return id;
}

void muestraInfoCliente(stClientes cli){
    printf("\n Cliente Nro..............: %d", cli.nroCliente);
    printf("\n Apellido y Nombre........: %s, %s", cli.apellido,cli.nombre);
    printf("\n DNI......................: %s", cli.dni);
    printf("\n E-Mail...................: %s", cli.email);
    printf("\n Domicilio................: %s", cli.domicilio);
    printf("\n Movil....................: %s", cli.movil);
    if(cli.eliminado){
        printf("\n Cliente inactivo");
    }else{
        printf("\n Cliente activo");
    }
}

// ============================== carga clientes =============================================== //


void cargaCliente(stClientes *a){
    printf("\n Nombre.......: ");
    fflush(stdin);
    gets(a->nombre); /// Por las dudas que tenga varios
    printf("\n Apellido.....: ");
    fflush(stdin);
    gets(a->apellido); /// Por las dudas que tenga varios
    printf("\n E-mail.......: ");
    fflush(stdin);
    gets(a->email);
    printf("\n Domicilio....: ");
    fflush(stdin);
    gets(a->domicilio);
    a->eliminado = 0;
}

void cargaYValidaDni(FILE *archi, stClientes *cliente, char *opcion){
    int id = 0;
    while(*opcion != ESC && id!=-1){
        system("cls");
        printf("\n Ingrese los datos del cliente:\n");
        printf("\n DNI..........: ");
        fflush(stdin);
        gets(cliente->dni);
        id = buscaIdXDni(archi,cliente->dni);
        if(id != -1){
            printf("\n Ya existe un cliente con el DNI cargado, presione cualquier tecla y vuelva\n a intentarlo, ESC para cancelar la carga del cliente");
            *opcion = getch();
        }
    }
}

void cargaYValidaMovil(FILE *archi, stClientes *cliente, char *opcion){
    int id = 0;
    while(*opcion != ESC && id!=-1){
        system("cls");
        printf("\n Ingrese los datos del cliente:\n");
        printf("\n Movil........: ");
        fflush(stdin);
        gets(cliente->movil);
        id = buscaIdXMovil(archi,cliente->movil);
        if(id!=-1){
            printf("\n Ya existe un cliente con el movil cargado, presione cualquier tecla y vuelva\n a intentarlo, ESC para cancelar la carga del cliente");
            *opcion = getch();
        }
    }
}

void cargaYValidaNroCliente(FILE *archi, stClientes *cliente, char *opcion){
    int yaExiste = 1;
    while(*opcion != ESC && yaExiste){
        system("cls");
        printf("\n Ingrese los datos del cliente:\n");
        printf("\n Nro. de Cliente....: ");
        fflush(stdin);
        scanf("%d", &cliente->nroCliente);
        yaExiste = validacionXNroCliente(archi,cliente->nroCliente);
        if(yaExiste){
            printf("\n Ya existe un cliente con el Nro. de Cliente cargado, presione cualquier tecla y vuelva\n a intentarlo, ESC para cancelar la carga del cliente");
            *opcion = getch();
        }
    }
}

void cargaArchivoClientes(char nombreArchivo[]){
    FILE *archi = fopen(nombreArchivo, "r+b");
    if(!archi){
        archi = fopen(nombreArchivo,"wb");
        fclose(archi);
        archi = fopen(nombreArchivo,"r+b");
    }
    fseek(archi, 0, SEEK_END);
    int id = ftell(archi)/sizeof(stClientes);
    stClientes cliente;
    char opcion = 0;

    if(archi){
            /** Carga el dni y valida que no exista en el archivo: */
            cargaYValidaDni(archi, &cliente, &opcion);
            /** Si cargo bien el dni, entra al while de la siguiente funcion, carga movil y valida que no exista en el archivo: */
            cargaYValidaMovil(archi, &cliente, &opcion);
            /** Si cargo bien el dni y movil, entra al while de la siguiente, carga nroCliente y valida que no exista en el archivo: */
            cargaYValidaNroCliente(archi, &cliente, &opcion);

            /** Si cargo bien dni, movil y nroCliente, guardo en el archivo: */
            if(opcion != ESC){
                    cliente.id = id;
                    cargaCliente(&cliente);
                    fwrite(&cliente, sizeof(stClientes), 1, archi);
            }

        fclose(archi);
    }else{
        printf("\n\n   No se pudo abrir el archivo de clientes. ");
        system("pause");
    }
}

// ============================== modifica clientes =============================================== //

void modificaYValidaDni(FILE *arch, stClientes *cli, char *opcion){
    char textoAux[60];
    int id;
    *opcion = 0;
    do{
            system("cls");
            printf("\n Ingrese el DNI:\n");
            fflush(stdin);
            gets(textoAux);
            id = buscaIdXDni(arch, textoAux);
            if(id!=-1 && strcmp(textoAux, cli->dni)!=0){
                printf("\n Ya existe un cliente con el DNI cargado, presione cualquier tecla y vuelva\n a intentarlo, ESC para cancelar la modificacion");
                *opcion = getch();
            }else{
                id = -1;
                strcpy(cli->dni, textoAux);
            }
    }while(id!=-1 && *opcion != ESC);
}

void modificaYValidaMovil(FILE *arch, stClientes *cli, char *opcion){
    char textoAux[60];
    int id;
    *opcion = 0;
    do{
            system("cls");
            printf("\n Ingrese el Movil:\n");
            fflush(stdin);
            gets(textoAux);
            id = buscaIdXMovil(arch, textoAux);
            if(id!=-1 && strcmp(textoAux, cli->movil)!=0){
                printf("\n Ya existe un cliente con el movil cargado, presione cualquier tecla y vuelva\n a intentarlo, ESC para cancelar la modificacion");
                *opcion = getch();
            }else{
                id = -1;
                strcpy(cli->movil, textoAux);
            }
    }while(id!=-1 && *opcion != ESC);
}

void modificaYValidaTodosDatos(FILE *arch, stClientes *cli, char *opcion){
    char textoAuxDni[60];
    strcpy(textoAuxDni, cli->dni);
    *opcion = 0;

    modificaYValidaDni(arch, cli, opcion);
    if(*opcion != ESC){
        modificaYValidaMovil(arch, cli, opcion);
    }
    if(*opcion!=ESC){
            printf("\n Ingrese el Apellido:\n");
            fflush(stdin);
            gets(cli->apellido);
            printf("\n Ingrese el/los Nombre/s:\n");
            fflush(stdin);
            gets(cli->nombre);
            printf("\n Ingrese el E-Mail:\n");
            fflush(stdin);
            gets(cli->email);
            printf("\n Ingrese el Domicilio:\n");
            fflush(stdin);
            gets(cli->domicilio);
            *opcion = 55;
    }else{
        strcpy(cli->dni, textoAuxDni);
    }
}

void menuModificaDatosCliente(int id, char nombreDelArchivo[]){
    char opcion;
    stClientes cli;
    FILE *arch = fopen(nombreDelArchivo,"r+b");
    if(arch){
            fseek(arch, id*sizeof(stClientes), SEEK_SET);
            fread(&cli, sizeof(stClientes), 1, arch);

            do{
                system("cls");
                muestraInfoCliente(cli);
                printf("\n\n Seleccione el campo que desea modificar:");
                printf("\n 1. Apellido");
                printf("\n 2. Nombre");
                printf("\n 3. DNI");
                printf("\n 4. E-Mail");
                printf("\n 5. Domicilio");
                printf("\n 6. Movil");
                printf("\n 7. Modificar todos los campos\n");
                printf("\n ESC. Volver al menu de clientes\n");
                opcion=getch();

                system("cls");
                fflush(stdin); /// fflush afecta a cada primer dato que se ingrese en cada case
                switch(opcion){
                    case ESC:
                        // para salir de este menu, va vacio asi no entra al default
                    break;
                    case 49:
                        printf("\n Ingrese el Apellido:\n");
                        gets(cli.apellido);
                        break;
                    case 50:
                        printf("\n Ingrese el/los Nombre/s:\n");
                        gets(cli.nombre);
                        break;
                    case 51:
                        modificaYValidaDni(arch, &cli, &opcion);
                        break;
                    case 52:
                        printf("\n Ingrese el E-Mail:\n");
                        gets(cli.email);
                        break;
                    case 53:
                        printf("\n Ingrese el Domicilio:\n");
                        gets(cli.domicilio);
                        break;
                    case 54:
                        modificaYValidaMovil(arch, &cli, &opcion);
                        break;
                    case 55:
                        modificaYValidaTodosDatos(arch, &cli, &opcion);
                        break;
                    default:
                        system("cls");
                        printf("\n\n Opcion no valida, presione cualquier tecla y vuelva a intentar \n");
                        getch();
                        break;
                }
                if(opcion != ESC && opcion != 55){
                    system("cls");
                    printf("\n\n Desea realizar alguna otra modificacion? Si es asi presione cualquier tecla, sino ESC ");
                    fflush(stdin);
                    opcion = getch();
                }

            }while(opcion != ESC && opcion != 55);
            fseek(arch, id*sizeof(stClientes), SEEK_SET);
            fwrite(&cli,sizeof(stClientes),1,arch);
            fclose(arch);
    }else{
        printf("\n\n   No se pudo abrir el archivo de clientes, presione cualquier tecla para continuar");
        getch();
    }
}

// ============================== busca consumos por mes =============================================== //

stConsumos buscaConsumoXMesAnio(FILE *arch, int idCli, int mes, int anio){
    int flag = 0;
    stConsumos consumo;
    while(flag==0 && fread(&consumo, sizeof(stConsumos), 1, arch)>0){
        if(consumo.idCliente==idCli && consumo.anio==anio && consumo.mes==mes){
            flag = 1;
        }
    }
    if(flag == 0){
        consumo.id = -1;
    }
    return consumo;
}

void listaConsumosCliente(int idCli, char nombreDelArchivo[]){
    int mes = 0;
    int anio;
    int entro = 0;
    char opcion = 0;
    stConsumos con;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    do{
        system("cls");
        printf("\n  Ingrese el anio del cual quiere ver los consumos: ");
        scanf("%d", &anio);
        if(anio<1900 || anio>(tm->tm_year + 1900)){
            printf("\n El anio que ingreso no es valido, presione una tecla y vuelva a intentarlo, ESC para cancelar");
            opcion = getch();
        }
    }while((anio<1900 || anio>(tm->tm_year + 1900)) && opcion!=ESC);

    while((mes<1 || mes>12 || (mes > tm->tm_mon + 1 && anio == (tm->tm_year + 1900))) && opcion!=ESC){
        system("cls");
        printf("\n  Ingrese el mes del cual quiere ver los consumos: ");
        scanf("%d", &mes);
        if(mes<1 || mes>12 || (mes > tm->tm_mon + 1 && anio == (tm->tm_year + 1900))){
            printf("\n El mes que ingreso no es valido, presione una tecla y vuelva a intentarlo, ESC para cancelar");
            opcion = getch();
        }
    }

    if(opcion != ESC){
        FILE *arch = fopen(nombreDelArchivo, "rb");
        if(arch){
            con = buscaConsumoXMesAnio(arch, idCli, mes, anio);
            while(con.id != -1){
                if(con.baja == 0){
                    muestraUnConsumo(con);
                    entro = 1;
                }
                con = buscaConsumoXMesAnio(arch, idCli, mes, anio);
            }
            if(!entro){
                printf("\n No existen consumos en el mes %d, anio %d. ", mes, anio);
            }
            system("pause");
            fclose(arch);
        }else{
            printf("\n\n   Hubo un error al abrir el archivo de consumos. ");
            system("pause");
        }
    }
}

// ============================== cambia estado cliente =============================================== //

void cambiaEstadoClientes(int idCli, char nombreDelArchivo[]){
    stClientes cli;
    char opcionBaja;
    FILE *arch = fopen(nombreDelArchivo, "r+b");
    system("cls");
    if(arch){
        fseek(arch, idCli*sizeof(stClientes), SEEK_SET);
        fread(&cli, sizeof(stClientes), 1, arch);
        if(cli.eliminado == 1){
                printf("\n\n   Esta seguro que desea dar de alta al cliente? Presione cualquier tecla para confirmar, ESC para cancelar  ");
                opcionBaja = getch();

                if(opcionBaja != ESC){
                    cli.eliminado = 0;
                }else{
                    printf("\n\n   Operacion cancelada. ");
                    system("pause");
                }
        }else{
                printf("\n\n Esta seguro que desea dar de baja al cliente? Presione cualquier tecla para confirmar, ESC para cancelar");
                opcionBaja = getch();

                if(opcionBaja != ESC){
                    cli.eliminado = 1;
                }else{
                    printf("\n\n   Operacion cancelada. ");
                    system("pause");
                }
        }
        fseek(arch, sizeof(stClientes)*-1, SEEK_CUR);
        fwrite(&cli, sizeof(stClientes), 1, arch);
        fclose(arch);
        if(opcionBaja != ESC){
            printf("\n\n   El cliente se cambio de estado con exito!! ");
            system("pause");
        }
    }else{
        printf("\n\n   Hubo un error al abrir el archivo de clientes, ");
        system("pause");
    }
}



