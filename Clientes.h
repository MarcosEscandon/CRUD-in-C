#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED





/// Muestra lista clientes
void muestraUnCliente(stClientes cliente,int i);
void listaClientes(FILE *arch);
int menorApellido(stClientes c[],int validos,int inicio);
void ordenaXApellido(stClientes c[],int validos);
void muestraArreglo(stClientes c[],int validos);
///sistema clientes:
void ingresaYValidaDni(FILE *arch, int *id, char *opcion);
void ingresaYValidaMovil(FILE *arch, int *id, char *opcion);
int validacionXNroCliente(FILE *arch, int nroClienteAux);
int buscaIdXDni(FILE *arch, char dni[]);
int buscaIdXMovil(FILE *arch, char movil[]);
void muestraInfoCliente(stClientes cli);
///carga clientes:
void cargaCliente(stClientes *a);
void cargaYValidaDni(FILE *archi, stClientes *cliente, char *opcion);
void cargaYValidaMovil(FILE *archi, stClientes *cliente, char *opcion);
void cargaYValidaNroCliente(FILE *archi, stClientes *cliente, char *opcion);
void cargaArchivoClientes(char nombreArchivo[]);
///modifica clientes:
void modificaYValidaDni(FILE *arch, stClientes *cli, char *opcion);
void modificaYValidaMovil(FILE *arch, stClientes *cli, char *opcion);
void modificaYValidaTodosDatos(FILE *arch, stClientes *cli, char *opcion);
void menuModificaDatosCliente(int id, char nombreDelArchivo[]);
///busca consumos por mes:
stConsumos buscaConsumoXMesAnio(FILE *arch, int idCli, int mes, int anio);
void listaConsumosCliente(int idCli, char nombreDelArchivo[]);
///cambia estado cliente:
void cambiaEstadoClientes(int idCli, char nombreDelArchivo[]);

#endif // CLIENTES_H_INCLUDED
