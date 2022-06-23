#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "Menues.h"
#include "Consumos.h"
#include "Clientes.h"


void consumosEmpresa(FILE *arch,char i){
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    stConsumos aux;
    stConsumos conMay[2000];
    int v=0;
    int con=0;
    int anio = tm->tm_year+1900;
    int mesPasado = tm->tm_mon;
    if(mesPasado == 0){
        mesPasado = 12;
        anio=anio-1;
    }
    rewind(arch);
    switch(i){
        case ESC:
            break;
        case 49:
            while (fread(&aux,sizeof(stConsumos),1,arch)>0){
                if (aux.baja==0 && mesPasado==aux.mes && anio==aux.anio){
                    if(aux.datosConsumidos>50){
                        conMay[v]=aux;
                        v++;
                    }
                    con++;
                }
            }
            sumaConsumos(conMay,v,con);
            break;
        case 50:
            while (fread(&aux,sizeof(stConsumos),1,arch)>0){
                if (aux.baja==0 && anio==aux.anio){
                    if(aux.datosConsumidos>50){
                        conMay[v]=aux;
                        v++;
                    }
                    con++;
                }
            }
            sumaConsumos(conMay,v,con);
            break;
        default:
            system("cls");
            printf("\n Opcion incorrecta intente denuevo\n");
            system("pause");
            break;
    }
}

void sumaConsumos(stConsumos conMay[],int v,int con){
    system("cls");
    float total;
    int mbExtra=0;
    for(int i=0;i<v;i++){
        mbExtra=mbExtra+conMay[i].datosConsumidos-50;
    }
    total=con*VALOR_MIN+mbExtra*VALOR_EXTRA;
    printf("\n  Planes   | Ingresos |");
    printf("\n  %d     =  %.2f ",con,con*VALOR_MIN);
    printf("\n Mb Extras | Ingresos |");
    printf("\n  %d   =  %.2f ",mbExtra,mbExtra*VALOR_EXTRA);
    printf("\n Ganancias Totales = %.2f",total);
    printf("\n");
    system("pause");
}

char menuIngresos(){
    char opc;
        system("cls");
        printf("\n Si desea ver los ingresos de:");
        printf("\n                              1. El ultimo mes");
        printf("\n                              2. El ultimo anio");
        printf("\n                              ESC. Finalizar");
        opc = getch();
    return opc;
}



// ============================== carga consumos =============================================== //

stConsumos creaConsumo(int idCliente){
    stConsumos a;
    a.id = tamanioArch(A_CONSUMOS,sizeof(stConsumos));
    a.idCliente = idCliente;
    int opcion = 0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    printf(" Si deseas cargar un consumo para el dia vijente precione 1 de ser cualquier otro dia precione 2 \n");
    do{
            opcion = getch();
            if(opcion == 49){
                    a.dia = tm->tm_mday;
                    a.mes = tm->tm_mon + 1;
                    a.anio = tm ->tm_year + 1900;
                    printf("\n Ingrese la cantidad de MB consumidos: ");
                    scanf("%d",&a.datosConsumidos);
                    a.baja = 0;
            }else if(opcion == 50){
                    printf("\n Ingrese el dia\n");
                    scanf("%d",&a.dia);
                    printf("\n Ingrese el mes\n");
                    scanf("%d",&a.mes);
                    printf("\nIngrese el anio\n");
                    scanf("%d",&a.anio);
                    printf("\n Ingrese la cantidad de MB consumidos: ");
                    scanf("%d",&a.datosConsumidos);
                    a.baja = 0;    /// carga alatoriamente valores para dias, mese, id y datos, el año actual y baja como 0
            }
       }while(opcion != 49 && opcion != 50);
    return a;
}

void cargaUnConsumo(int idCliente){
    system("cls");
    stConsumos con = creaConsumo(idCliente);
    system("cls");
    FILE *arch = fopen(A_CONSUMOS,"r+b");
    if(arch){
        if(validacionxFecha(con) && !validacionxId(con.idCliente)){
               if(!existeFecha(con,arch)){
                    fwrite(&con,sizeof(stConsumos),1,arch);
                }
        }else if(!validacionxFecha(con)){
            printf("\nno se cargo el consumo porque la fecha no existe\n");
            system("pause");
        }else{
             printf("\nno se cargo el consumo porque el cliente esta dado de baja\n");
             system("pause");
        }
        fclose(arch);
    }

}

// ============================== validacion de consumos =============================================== //


int validacionxFecha(stConsumos con){
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t); /// toma la fecha de la computadora y la pasan a una struct
    if((con.anio == (tm->tm_year +1900)  && (((tm->tm_mon + 1) == con.mes  && tm->tm_mday < con.dia) || (tm->tm_mon + 1) < con.mes)) || con.anio < 1900 || con.anio > (tm->tm_year + 1900)){     /// compara la fecha actual con la generada alatoriamente para ver si esta no es futura
            return 0;
        }

    switch (con.mes){        ///verifica que el dia exista en el mes (tiene en cuenta si el año es bisiesto o no)
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(con.dia <= 31 && con.dia > 0)
                return 1;
            else
                return 0;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(con.dia <= 30 && con.dia > 0)
                return 1;
            else
                return 0;
            break;
        case 2:
            if((con.anio%4 == 0 && con.anio%100 != 0) || con.anio%400 == 0){
                   if(con.dia <= 29 && con.dia > 0)
                    return 1;
                else
                    return 0;
            }else{
                if(con.dia <= 28 && con.dia >0)
                    return 1;
                else
                    return 0;
            }
            break;
    }
    return 0;
}

int validacionxId(int id){
    stClientes aux = buscaCliente(id,A_CLIENTES);
    if (aux.id==-1){
        aux.eliminado=1;
    }
    return aux.eliminado;
}



int existeFecha(stConsumos c, FILE *arch){
    int flag = 0;
    stConsumos aux;
    rewind(arch);
    aux = buscaConsumoXDia(c.idCliente,c.anio,c.mes,c.dia,arch);
    if(aux.id != -1){
        if(aux.baja == 0){
            aux.datosConsumidos += c.datosConsumidos;
        }else{
            aux.datosConsumidos = c.datosConsumidos;
            aux.baja = 0;
        }
        fseek(arch,aux.id*sizeof(stConsumos),SEEK_SET);
        fwrite(&aux,sizeof(stConsumos),1,arch);
        flag = 1;
    }
    fseek(arch,0,SEEK_END);
    return flag;
}


// ============================== busca consumos por dia =============================================== //

stConsumos buscaConsumoXDia(int idCli, int anio, int mes, int dia, FILE *arch){
    int flag = 0;
    stConsumos consumo;
    while(flag == 0 && fread(&consumo, sizeof(stConsumos), 1, arch)>0){
        if(consumo.idCliente==idCli && consumo.dia==dia && consumo.mes==mes && consumo.anio==anio){
            flag = 1;
        }
    }
    if(flag == 0){
        consumo.id = -1;
    }
    return consumo;
}

void sumaConsumo(FILE *arch){ ///esto puede usarse paraa comprobar si el consumo ya existe y si hay que sumarlo o crearlo, esta incompleto
    system("cls");
    int mb;
    stConsumos consumo;
    printf("\n Ingrese la cantidad de Mb a agregar: ");
    scanf("%d", &mb);
    fread(&consumo, sizeof(stConsumos), 1, arch);
    fseek(arch, sizeof(stConsumos)*-1, SEEK_CUR);
    consumo.datosConsumidos += mb;
    fwrite(&consumo, sizeof(stConsumos), 1, arch);
    printf("\n\n   Operacion realizada con exito! Presione cualquier tecla para continuar\n");
    getch();
}

void muestraUnConsumo(stConsumos con){
    printf("\n |    Fecha    | Consumo |");
    printf("\n  %d / %d / %d    %d Mb\n\n",con.dia,con.mes,con.anio,con.datosConsumidos);
    if(con.baja==1){
        printf("   Este consumo fue dado de baja\n\n");
    }
}

void estadoConsumos(FILE *arch){
    stConsumos con;
    fread(&con,sizeof(stConsumos),1,arch);
    con.baja=1;
    fseek(arch, sizeof(stConsumos)*-1, SEEK_CUR);
    fwrite(&con, sizeof(stConsumos), 1, arch);
    printf("\n\n   Operacion realizada con exito! Presione cualquier tecla para continuar\n");
    getch();
}

void buscarConsumosXDia(int idCli, char nombreDelArchivo[]){
    FILE *arch = fopen(nombreDelArchivo,"r+b");
    stConsumos con;
    if(arch){
        int dia,mes,anio;
        int opc;
        printf("\n\n Ingrese el dia:\n");
        scanf("%d",&dia);
        printf("\n Ingrese el mes:\n");
        scanf("%d",&mes);
        printf("\n Ingrese el anio:\n");
        scanf("%d",&anio);
        con = buscaConsumoXDia(idCli, anio, mes, dia, arch);
        if(con.id!=-1){
            system("cls");
            muestraUnConsumo(con);
            printf("\n Presione cualquier tecla para continuar");
            getch();
            if(con.baja==0){
                fseek(arch, sizeof(stConsumos)*-1, SEEK_CUR);

                do{
                        printf("\n\n Ingrese:");
                        printf("\n         1. Si desea borrar este consumo");
                        printf("\n         2. Si desea agregar un consumo en esta fecha");
                        printf("\n         ESC para volver al menu anterior\n");
                        opc=getch();

                        switch(opc){
                        case ESC:
                            // para salir de este menu, va vacio asi no entra al default
                            break;
                        case 49:
                            estadoConsumos(arch);
                            break;
                        case 50:
                            sumaConsumo(arch);
                            break;
                        default:
                            system("cls");
                            printf("\n\n Opcion no valida, presione cualquier tecla y vuelva a intentar \n");
                            getch();
                            break;
                        }
                }while(opc!=50 && opc!=49 && opc!=ESC);
            }
        }else{
            printf("\n No existen consumos en esta fecha. ");
            system("pause");
        }
        fclose(arch);
    }else{
        printf("\n\n   No se pudo abrir el archivo de consumos. ");
        system("pause");
    }
}




// ============================== factura de un cliente =============================================== //

stClientes buscaCliente(int id, char nombreDelArchivo[]){ /// ES   LA MISMA QUE   YA ESTABA SOLO   QUE DEVUELVE   CLIENTE, SE   PUEDE  USAR SOLO   ESTA, VER   LA ANTERIOR"void infoCliente"
    stClientes cli;
    cli.id = -1;
    FILE *arch = fopen(nombreDelArchivo,"rb");
    if(arch){
        fseek(arch, id*sizeof(stClientes), SEEK_SET);
        fread(&cli, sizeof(stClientes), 1, arch);
        fclose(arch);
    }
    else{
       printf("\n El archivo no se pudo abrir correctamente. Presione cualquier tecla para continuar");
       getch();
    }
    return cli;
}


void calculaMbs(stConsumos listaCon[], int vLista, int *mbExtra, int *diasPaso50, int *totalMb){
    for(int i=0; i<vLista; i++){
        *totalMb = *totalMb + listaCon[i].datosConsumidos;
        if(listaCon[i].datosConsumidos>50){
            *mbExtra = *mbExtra + listaCon[i].datosConsumidos - 50;
            *diasPaso50 = *diasPaso50 + 1;
        }
    }
}

void arrayListaConsumosCliente(FILE *arch, int idCli, int *vLista, int mesFac, int anioFac, stConsumos listaCon[]){
    int i = 0;
    stConsumos auxCon;
    auxCon.id = 0;
    auxCon = buscaConsumoXMesAnio(arch, idCli, mesFac, anioFac);
    while(auxCon.id != -1){
        if(auxCon.baja==0){
            listaCon[i] = auxCon;
            i++;
        }
        auxCon = buscaConsumoXMesAnio(arch, idCli, mesFac, anioFac);
    }
    *vLista = i;
}

void imprimeFactura(stConsumos listaCon[], int vLista, int idCli, int mesFac, int anioFac){
    stClientes cliente;
    int mbExtra = 0;
    int totalMb = 0;
    int diasPaso50 = 0;
    cliente = buscaCliente(idCli, A_CLIENTES);
    if(cliente.id != -1){
        system("cls");
        printf("______________Resumen mes %d, anio %d de la cuenta______________\n\n", mesFac, anioFac);
        muestraInfoCliente(cliente);
        if(vLista != 0){
            calculaMbs(listaCon, vLista, &mbExtra, &diasPaso50, &totalMb);
        }
        printf("\n\n\n\n   Valor x50MB:                         $ %.2f", VALOR_MIN);
        printf("\n   Valor MB extra:                      $ %.2f", VALOR_EXTRA);
        printf("\n\n   Total Datos consumidos:                %d MB", totalMb);
        printf("\n   Total de MB extra consumidos:          %d MB", mbExtra);
        printf("\n   Dias que paso los 50MB:                %d", diasPaso50);
        printf("\n   A pagar por dias que consumio datos: $ %.2f", vLista*VALOR_MIN);
        printf("\n   A pagar por MB extra consumidos:     $ %.2f", mbExtra*VALOR_EXTRA);
        printf("\n\n   Total a pagar:                       $ %.2f", (vLista*VALOR_MIN + mbExtra*VALOR_EXTRA));
        printf("\n\n\n\n   Ingrese cualquier tecla para continuar...");
        getch();
    }
}

void muestraFacturaMes(int idCli, char nombreDelArchivo[]){
    stConsumos listaCon[31];
    int vLista;
    int mesFac = 0;
    int anioFac;
    char opcion = 0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    do{
        system("cls");
        printf("\n  Ingrese el anio del cual quiere ver la factura: ");
        scanf("%d", &anioFac);
        if(anioFac<1900 || anioFac>(tm->tm_year + 1900)){
            printf("\n El anio que ingreso no es valido, presione una tecla y vuelva a intentarlo, ESC para cancelar");
            opcion = getch();
        }
    }while((anioFac<1900 || anioFac>(tm->tm_year + 1900)) && opcion!=ESC);

    while((mesFac<1 || mesFac > 12 || (mesFac>(tm->tm_mon + 1) && anioFac == (tm->tm_year + 1900))) && opcion!=ESC){
        system("cls");
        printf("\n  Ingrese el mes del cual quiere ver la factura: ");
        scanf("%d", &mesFac);
        if(mesFac<1 || mesFac > 12  || (mesFac > tm->tm_mon + 1 && anioFac == (tm->tm_year + 1900))){
            printf("\n El mes que ingreso no es valido, presione una tecla y vuelva a intentarlo, ESC para cancelar");
            opcion = getch();
        }else if(mesFac==tm->tm_mon + 1 && anioFac == (tm->tm_year + 1900)){
            printf("\n Podra consultar la factura de este mes al finalizar el mismo. ");
            system("pause");
        }
    }
    if(opcion!=ESC){
        FILE *arch = fopen(nombreDelArchivo, "rb");
        if(arch){
            arrayListaConsumosCliente(arch, idCli, &vLista, mesFac, anioFac, listaCon);
            fclose(arch);
            imprimeFactura(listaCon, vLista, idCli, mesFac, anioFac);
        }else{
            system("cls");
            printf("\n Hubo un error al abrir el archivo de consumos. ");
            system("pause");
        }
    }
}

int tamanioArch(char nombreArch[], int dato){
    FILE *arch = fopen(nombreArch,"rb");
    int tamanio = 0;
    if(arch){
        fseek(arch,0,SEEK_END);
        tamanio = ftell(arch)/dato;
        fclose(arch);
    }
    return tamanio;
}
