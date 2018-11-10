#ifndef UTILIDADES_HH
#define UTILIDADES_HH

typedef struct _strDArray *DArray;

DArray crearDArray();
// Crea un array dinamico

int cantDArray(DArray da);
// Retorna la cantidad de elementos del array dinamico

void eliminarDArray(DArray &da);
// Elimina el array dinamico

int cantidadValores(const char *valores);
// Retorna la cantidad de valores

void redimDArray(DArray &da, int tam);
// Redimensiona el array dinamico

void setTope(DArray &da, int tope);
// Setea el tope a un array dinamico

void setArrayIndice(DArray &da, int indice, int pos);
// Setea un valor en el array dinamico en la posicion indice

int getValorDArray(DArray da, int pos);
// Retona el valor de la posicion en el array

void parsearValores(char *strArray[], int largo, const char *valores);
// Separa los valores y los guarda en un array de strings

int cantColumnas(char *nombreCols);
// Retorna la cantidad de columnas

bool esNumero(const char *string);
// Retorna true si el string es un numero, false si no

int parsearCondicion(char *strArray[], int largo, const char *condicion);
// Separa la condicion y guarda los datos en un array de strings

char obtenerOperador(const char *condicion);
// Retorna el operador de la condicion

bool compararPrefijoStr(char *dato, char *prefijo);
// Compara dos strings y se fija si el prefijo esta contenido en el dato

bool compararPrefijoInt(int dato, int prefijo);
// Compara dos enteros y se fija si el prefijo esta contenido en el dato

bool preguntarTipoCol();
// Retorna true si la tabla es entero, false si es string

#endif
