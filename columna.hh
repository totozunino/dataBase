#include "celda.hh"
#include "utilidades.hh"

#ifndef COLUMNA_HH
#define COLUMNA_HH

typedef struct _strColumna *Columna;

Columna crearCol(const char *nombreColumna, bool esEntero);
// Crea una columna

Columna agregarCol(Columna listaCol, const char *nombreColumna, bool esEntero);
// Agrega una columna

bool existeCol(Columna listaCol, const char *nombreColumna);
// Retorna true si la columna ya existe, false si no

int cantidadCol(Columna listaCol);
// Retorna la cantidad de columnas

void crearTupla(Columna listaCol);
// crea una tupla

bool esEntero(Columna col);
// Retorna true si la columna es de tipo entero, false si no

void insertarTuplaOrdenada(Columna listaCol, char *datos[]);
// Inserta la tupla por orden ascendente

Celda obtenerListaCel(Columna col);
// Retorna la celda de la columna

bool checkTipos(Columna listaCol, char *valores[], int indice);
// Retorna true si los valores a ingresar son correctos, false si no

bool existenColumnas(Columna listaCol, char *strArray[], int cantCols);
// Retorna true si existen las columnas, false si no

void imprimirCols(Columna listaCol, bool tipof);
// Imprime los nombres de las columnas

void imprimirTuplas(Columna listaCol);
// Imprime todas las tuplas

void imprimirTupla(Columna listaCol, int pos);
// Imprime una tupla en la posicion pos

void eliminarTuplasIndice(Columna listaCol, char operador, char *strArray[]);
// Elimina las tuplas que cumplen con la condicion

void eliminarTuplaCol(Columna &listaCol, int indice);
// Elimina la tupla segun el indice indicado

Columna eliminarColumna(Columna &listaCol, char *nombreColumna);
// Elimina la columna

void eliminarTodasCol(Columna &listaCol);
// Elimina todas las columnas

bool esPk(Columna listaCol, char *nombreColumna);
// Retorna true si es pk y la siguiete columna es NULL, false si no

bool esUnicaCol(Columna listaCol, char *nombreColumna);
// Retorna true si es la unica columna, false si no

void eliminarTodasTuplas(Columna &listaCol);
// Elimina todas las tuplas

Columna obtenerColumna(Columna listaCol, char *nombreColumna);
// Retorna la columna con el nombre especificado

bool existeListaCel(Columna listaCol);
// Retorna true si existe una lista de celdas, false si no

void updateTupla(Columna listaCol, int pos, char *nombreCol, char *valor);
// Modifica una tupla

void updateTuplasIndice(Columna listaCol, char operador, char *strArray[], char *nombreCol, char *valor);
// Modifica la tupla indicada

int checkearDatos(Celda listaCel, char *valor, char operador, bool tipo);
// Checkea cuantos datos iguales a valor hay en la lista de celdas

bool checkearValor(Celda listaCel, char *valor, bool tipo);
// Checkea si ls tipos de los valores son correctos

void obtenerDatos(char *datos[], Columna listaCol, int cont);
// Obtiene los datos de una tupla

void obtenerPosicionesTuplas(Columna listaCol, char operador, char *strArray[], DArray &da);
// Obtiene todas las posiciones de las tuplas que cumplen la condicion y las guarda en un array

void copiarColumnas(Columna lctabla, Columna &lcnueva);
// Copia todas las columnas de una tabla a la otra

void copiarTuplasIndice(Columna lctabla, Columna &lcnueva, char operador, char *strArray[]);
// Copia las tuplas que cumplen la condicion de una tabla a la otra

void copiarTodasTuplas(Columna lctabla, Columna &lcnueva);
// Copia todas las tuplas de una tabla a la otra

void agregarCeldasCol(Columna &lcNueva, Columna lcTabla, char *strArray[], int cantCols);
// Agrega las celdas a la columna correspondientes

bool mismaPk(Columna lcTabla1, Columna lcTabla2);
// Retorna true si las columnas tienen las mismas pks, false si no

bool columnasRepetidas(Columna lcTabla1, Columna lcTabla2);
// Retorna true si hay columnas repetidas, flase si no

Columna obtenerColSig(Columna lcTabla2);
// Retorna la lista de columna siguiente

void copiarDatosColumnas(Columna &lcNueva, Columna lcTabla1, Columna lcTabla2sig);
// Copia los datos a las columnas

void agregarDatosIndice(Columna &lcNueva, Columna lcTabla1, int pos1, Columna lcTabla2, int pos2);
// Agrega los datos de dichas posiciones

bool mismasColumnas(Columna lcTabla1, Columna lcTabla2);
// Retorna true si tienen las mismas columnas, false si no

bool mismosDatos(Columna lcTabla1, Columna lcTabla2);
// Retorna true si tienen los mismos datos, false si no

bool mismosTipos(Columna lcTabla1, Columna lcTabla2);
// Retorna true si las columnas tienen el mismo tipo de dato, false si no

#endif
