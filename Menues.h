#ifndef MENUES_H_INCLUDED
#define MENUES_H_INCLUDED

#define ESC 27
#define A_CLIENTES "clientes.dat"
#define A_CONSUMOS "consumos.dat"
#define VALOR_MIN 35.9
#define VALOR_EXTRA 0.85

typedef struct{
int id; /// campo único y autoincremental
int nroCliente;
char nombre[30];
char apellido[30];
char dni[10];
char email[30];
char domicilio[45];
char movil[12];
int eliminado; /// 0 si está activo - 1 si está eliminado
}stClientes;

typedef struct{
int id; /// campo único y autoincremental
int idCliente;
int anio;
int mes; /// 1 a 12
int dia; /// 1 a … dependiendo del mes
int datosConsumidos; /// expresados en mb.
int baja; /// 0 si está activo - 1 si está eliminado
}stConsumos;
///menus:
void menuInicial();
void consultaInfoCliente(char nombreDelArchivo[]);
void menuClientes(int id);
///menus ayuda:
void funcionAyuda();
///menu sistema
void menuSistema();
void menuSwSistema(char opc);


#endif // MENUES_H_INCLUDED
