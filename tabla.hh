#include "columna.hh"

#ifndef TABLA_HH
#define TABLA_HH

typedef struct _strTabla *Tabla;

Tabla crearTabla(const char *nombreTabla);
// Crea una tabla

void agregarTabla(Tabla &listaTb, const char *nombreTabla);
// Agrega una tabla a la lista de tablas tb

bool existeTabla(Tabla listaTb, const char *nombreTabla);
// Retorna true si la tabla existe, false si no existe

Tabla obtenerTabla(Tabla listaTb, const char *nombreTabla);
// Obtiene una tabla de la lista de tablas tb

bool existeColTabla(Tabla tb, const char *nombreCol);
// Retorna true si la columna existe en la tabla tb, false si no

void agregarColTabla(Tabla tb, const char *nombreCol, bool esEntero);
// Agrega una columna a la tabla tb

Columna obtenerListaCol(Tabla tb);
// Retorna la lista de columnas de una tabla

Tabla obtenerMinimo(Tabla arbolTb);
// Retona el arbol menor

void eliminarTabla(Tabla &listaTb, char *nombreTabla);
// Elimina una tabla

void eliminarTodasTablas(Tabla &listaTb);
// Elimina todas las tablas

void eliminarColTabla(Tabla &tb, Columna &listaCol, char *nombreCol);
// Elimina una columna en la tabla

void copiarColumnasTabla(Columna lcTabla, Tabla &nueva);
// Copia las columnas a una tabla

void copiarTuplasTabla(Columna lcTabla, Tabla &nueva, char operador, char *strArray[]);
// Copia las tuplas a la tabla

void tuplasTabla(Columna lcTabla, Tabla &nueva);
// Copia todas las tuplas a la tabla

void agregarColEspecificas(Tabla &nueva, Columna lcTabla, char *strArray[], int cantCols);
// Agrega las columnas especificadas

void agregarDatosTabla(Tabla &nueva, Columna lcTabla, char *strArray[], int cantCols);
// Agrega los datos a la tabla

#endif
