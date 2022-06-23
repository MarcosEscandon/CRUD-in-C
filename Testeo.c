#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "Menues.h"
#include "Consumos.h"
#include "Clientes.h"
#include "Testeo.h"



void verArchClientes(){
    stClientes a;
    FILE *arch = fopen(A_CLIENTES,"rb");
    if(arch){
        while(fread(&a, sizeof(stClientes), 1, arch)>0 ){
            printf("\n id : %d", a.id);
            printf("\n nroCliente   ..........: %d", a.nroCliente);
            printf("\n Nombre y apellido......: %s, %s", a.apellido, a.nombre);
            printf("\n dni          ..........: %s", a.dni);
            printf("\n email        ..........: %s", a.email);
            printf("\n domicilio    ..........: %s", a.domicilio);
            printf("\n movil        ..........: %s", a.movil);
            printf("\n eliminado o no.........: %d", a.eliminado);
            printf("\n===================================================");
        }
        fclose(arch);
    }else{
        printf("\n\n   Hubo un error al abrir el archivo\n\n");
    }
    system("pause");
    system("cls");
}
void verArchConsumos(){
    stConsumos b;
    FILE *arch = fopen(A_CONSUMOS,"rb");
    if(arch){
        while(fread(&b, sizeof(stConsumos), 1, arch)>0){
            printf("\n id : %d", b.id);
            printf("\n idCliente    ..........: %d", b.idCliente);
            printf("\n Anio         ..........: %d", b.anio);
            printf("\n Mes          ..........: %d", b.mes);
            printf("\n Dia          ..........: %d", b.dia);
            printf("\n datosConsumidos    ....: %d", b.datosConsumidos);
            printf("\n baja         ..........: %d", b.baja);
            printf("\n===================================================");
        }
        fclose(arch);
    }else{
        printf("\n\n   Hubo un error al abrir el archivo\n\n");
    }
    system("pause");
    system("cls");
}

void cargaXConsumos(int carga){
    srand(time(NULL));
    int validos = tamanioArch(A_CLIENTES,sizeof(stClientes));
    int i=0;
    int j=1;
    FILE *arch = fopen(A_CONSUMOS, "w+b");
    int id = tamanioArch(A_CONSUMOS,sizeof(stConsumos));
    stConsumos cons;
    if(arch){
        printf("DD/MM/AA | IDcli | IDcon | C/CREADOS \n");
        while(i<carga){
            cons = creaConsumoRand(2022,id,validos);
            if (validacionxFecha(cons) && !validacionxId(cons.idCliente)){
                printf("%d/%d/%d | %d | %d  |  %d\n",cons.dia,cons.mes,cons.anio,cons.idCliente,cons.id,j);
                j++;
                if (!existeFecha(cons,arch)){
                    fwrite(&cons,sizeof(stConsumos),1,arch);
                    id++;
                    i++;
                }
            }
        }
        fclose(arch);
    }
    system("pause");
    system("cls");
}

stConsumos creaConsumoRand(int anio,int id, int validos){
    stConsumos a;
    a.id = id;
    a.dia = rand()%31 + 1;
    a.mes = rand()%12 + 1;
    a.idCliente = rand()%validos;
    a.anio = anio;
    a.datosConsumidos = rand()%1000 + 10;
    a.baja = 0;    /// carga alatoriamente valores para dias, mese, id y datos, el año actual y baja como 0
    return a;
}

void altaClientes(){
    FILE *arch = fopen("clientes.dat","r+b");
    stClientes aux;
    if(arch){
        while(fread(&aux,sizeof(stClientes),1,arch)>0){
            fseek(arch,-1*sizeof(stClientes),SEEK_CUR);
            printf("%d",aux.id);
            printf("%s",aux.apellido);
            aux.eliminado = 0;
            fwrite(&aux,sizeof(stClientes),1,arch);
            fseek(arch,sizeof(stClientes),SEEK_CUR);
            fseek(arch,-1*sizeof(stClientes),SEEK_CUR);
            system("pause");
        }
        fclose(arch);
    }
}
