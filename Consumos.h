#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED



/// Ingresos de la empresa
void consumosEmpresa(FILE *arch,char i);
void sumaConsumos(stConsumos conMay[],int v,int con);
char menuIngresos();
///carga consumos:
stConsumos creaConsumo(int idCliente);
void cargaUnConsumo(int idCliente);
///validacion consumos:
int validacionxFecha(stConsumos con);
int validacionxId(int id);
int existeFecha(stConsumos c, FILE *arch);
///busca consumos por dia:
stConsumos buscaConsumoXDia(int idCli, int anio, int mes, int dia, FILE *arch);
void sumaConsumo(FILE *arch);
void muestraUnConsumo(stConsumos con);
void estadoConsumos(FILE *arch);
void buscarConsumosXDia(int idCli, char nombreDelArchivo[]);
///factura de un cliente:
stClientes buscaCliente(int id, char nombreDelArchivo[]);
void calculaMbs(stConsumos listaCon[], int vLista, int *mbExtra, int *diasPaso50, int *totalMb);
void arrayListaConsumosCliente(FILE *arch, int idCli, int *vLista, int mesFac, int anioFac, stConsumos listaCon[]);
void imprimeFactura(stConsumos listaCon[], int vLista, int idCli, int mesFac, int anioFac);
void muestraFacturaMes(int idCli, char nombreDelArchivo[]);
int tamanioArch(char nombreArch[], int dato);


#endif // CONSUMOS_H_INCLUDED
