#ifndef CELDA_HH
#define CELDA_HH

typedef struct _strCelda *Celda;
typedef union _unionTipo tipoU;

Celda crearCelda();
// Crea una celda

Celda agregarCelda(Celda listaCel);
// Agrega una celda

void setDatoInt(Celda &cel, int dato);
// Setea el dato de tipo entero a la celda

void setDatoStr(Celda &cel, char *dato);
// Setea el dato de tipo string a la celda

bool pkDuplicada(Celda listaCel, char *dato);
// Retorna true si la pk existe, false si no

int getDatoInt(Celda cel);
// Retorna el dato de tipo entero de la celda

char *getDatoStr(Celda cel);
// Retorna el dato de tipo string de la celda

Celda getCeldaSig(Celda cel);
// Retorna la celda siguiente de cel

void setCeldaSig(Celda cel, Celda sig);
// Setea la celda siguiente a la celda cel

int insertarCeldaOrdenada(Celda &listaCelda, bool esEntero, char *dato);
// Inserta la celda ordenadamente

void insertarCeldaIndice(Celda &listaCel, bool esEntero, char *dato, int indice);
// Inserta la celda en el indice

int cantidadTuplas(Celda listaCel);
// Retorna la cantidad de tuplas

void eliminarCeldasCol(Celda &listaCel);
// Elimina la lista de celdas

void eliminarCelda(Celda &cel, int indice);

#endif
