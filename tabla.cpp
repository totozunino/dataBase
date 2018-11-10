#include "bd.hh"
#include "columna.hh"
#include "tabla.hh"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * Tabla con Listas
struct _strTabla {
    char *nombre;
    Columna col;
    Tabla sig;
};
*/

// Tabla con arbol
struct _strTabla {
    char *nombre;
    Columna col;
    Tabla izq;
    Tabla der;
};

/*
 * Crear Tabla con Listas
Tabla crearTabla(const char *nombreTabla) {
  Tabla t = new _strTabla;
  char *nombre = new char[strlen(nombreTabla) + 1];
  strcpy(nombre, nombreTabla);
  t->nombre = nombre;
  t->sig = NULL;
  t->col = NULL;
  return t;
}
*/

/*
 * Agregar Tabla con Listas
Tabla agregarTabla(Tabla listaTb, const char *nombreTabla) {
  Tabla nueva = crearTabla(nombreTabla);
  nueva->sig = listaTb;
  listaTb = nueva;
  return listaTb;
}
*/

// Agregar Tabla con arbol
void agregarTabla(Tabla &arbolTb, const char *nombreTabla) {
  if (arbolTb == NULL) {
    Tabla t = new _strTabla;
    char *nombre = new char[strlen(nombreTabla) + 1];
    strcpy(nombre, nombreTabla);
    t->nombre = nombre;
    t->der = NULL;
    t->izq = NULL;
    t->col = NULL;
    arbolTb = t;
  } else {
    if (strcmp(arbolTb->nombre, nombreTabla) > 0) {
      agregarTabla(arbolTb->izq, nombreTabla);
    } else {
      agregarTabla(arbolTb->der, nombreTabla);
    }
  }
}

/*
 * Existe Tabla con Listas
bool existeTabla(Tabla listaTb, const char *nombreTabla) {
  if (listaTb == NULL)
    return false;
  else if (strcmp(listaTb->nombre, nombreTabla) == 0)
    return true;
  else
    return existeTabla(listaTb->sig, nombreTabla);
}
*/

// Existe Tabla con arbol
bool existeTabla(Tabla arbolTb, const char *nombreTabla) {
  if (arbolTb == NULL) {
    return false;
  } else if (strcmp(arbolTb->nombre, nombreTabla) == 0) {
    return true;
  } else if (strcmp(arbolTb->nombre, nombreTabla) > 0) {
    return existeTabla(arbolTb->izq, nombreTabla);
  } else {
    return existeTabla(arbolTb->der, nombreTabla);
  }
}

/*
 * Obtener Tabla con Listas
Tabla obtenerTabla(Tabla listaTb, const char *nombreTabla) {
  if (listaTb == NULL)
    return NULL;
  else if (strcmp(listaTb->nombre, nombreTabla) == 0)
    return listaTb;
  else
    return obtenerTabla(listaTb->sig, nombreTabla);
}
*/

// Obtener Tabla con arbol
Tabla obtenerTabla(Tabla arbolTb, const char *nombreTabla) {
  if (arbolTb == NULL) {
    return arbolTb;
  } else if (strcmp(arbolTb->nombre, nombreTabla) == 0) {
    return arbolTb;
  } else if (strcmp(arbolTb->nombre, nombreTabla) > 0) {
    return obtenerTabla(arbolTb->izq, nombreTabla);
  } else
    return obtenerTabla(arbolTb->der, nombreTabla);
}

bool existeColTabla(Tabla tb, const char *nombreCol) {
  return existeCol(tb->col, nombreCol);
}

void agregarColTabla(Tabla tb, const char *nombreCol, bool esEntero) {
  tb->col = agregarCol(tb->col, nombreCol, esEntero);
}

Columna obtenerListaCol(Tabla tb) {
  return tb->col;
}

/*
 * Eliminar Tabla con Listas
void eliminarTabla(Tabla &listaTb, char *nombreTabla) {
  Tabla anterior = NULL;
  Tabla actual = listaTb;
  bool encontre = false;
  while (actual != NULL && !encontre) {
    if (strcmp(actual->nombre, nombreTabla) != 0) {
      anterior = actual;
      actual = actual->sig;
    } else {
      encontre = true;
    }
  }
  if (anterior == NULL) {
    listaTb = actual->sig;
    delete[] actual->nombre;
    eliminarTodasCol(actual->col);
    delete actual;
  } else {
    anterior->sig = actual->sig;
    delete[] actual->nombre;
    eliminarTodasCol(actual->col);
    delete actual;
  }
}
*/

Tabla obtenerMinimo(Tabla arbolTb) {
  if (arbolTb == NULL) {
    return arbolTb;
  } else if (arbolTb->izq == NULL) {
    return arbolTb;
  } else {
    return obtenerMinimo(arbolTb->izq);
  }
}

// Eliminar Tabla con arbol
void eliminarTabla(Tabla &arbolTb, char *nombreTabla) {
  Tabla aux;
  if (existeTabla(arbolTb, nombreTabla) && arbolTb != NULL) {
    if (strcmp(nombreTabla, arbolTb->nombre) < 0) {
      eliminarTabla(arbolTb->izq, nombreTabla);
    } else {
      if (strcmp(nombreTabla, arbolTb->nombre) > 0) {
        eliminarTabla(arbolTb->der, nombreTabla);
      } else {
        if (arbolTb->izq == NULL) {
          aux = arbolTb;
          arbolTb = arbolTb->der;
          delete[] aux->nombre;
          delete aux;
        } else {
          if (arbolTb->der == NULL) {
            aux = arbolTb;
            arbolTb = arbolTb->izq;
            delete[] aux->nombre;
            delete aux;
          } else {
            aux = obtenerMinimo(arbolTb->der);
            strcpy(arbolTb->nombre, aux->nombre);
            eliminarTabla(arbolTb->der, arbolTb->nombre);
          }
        }
      }
    }
  }
}

void eliminarColTabla(Tabla &tb, Columna &listaCol, char *nombreCol) {
  tb->col = eliminarColumna(listaCol, nombreCol);
}

/*
 * Eliminar todas las Tablas con Listas
void eliminarTodasTablas(Tabla listaTb) {
  for (Tabla tb = listaTb; tb != NULL; tb = tb->sig) {
    eliminarTodasCol(tb->col);
  }
}
*/

// Eliminar todas las Tablas con arbol
void eliminarTodasTablas(Tabla &arbolTb) {
  if (arbolTb != NULL) {
    eliminarTodasTablas(arbolTb->izq);
    eliminarTodasTablas(arbolTb->der);
    eliminarTodasCol(arbolTb->col);
    delete[] arbolTb->nombre;
    delete arbolTb;
  }
}

void copiarColumnasTabla(Columna lcTabla, Tabla &nueva) {
  copiarColumnas(lcTabla, nueva->col);
}

void tuplasTabla(Columna lcTabla, Tabla &nueva) {
  copiarTodasTuplas(lcTabla, nueva->col);
}

void copiarTuplasTabla(Columna lcTabla, Tabla &nueva, char operador, char *strArray[]) {
  copiarTuplasIndice(lcTabla, nueva->col, operador, strArray);
}

void agregarColEspecificas(Tabla &nueva, Columna lcTabla, char *strArray[], int cantCols) {
  for (int i = 0; i < cantCols; i++) {
    bool tipo;
    char *nombreCol = new char[strlen(strArray[i]) + 1];
    strcpy(nombreCol, strArray[i]);
    Columna col = obtenerColumna(lcTabla, nombreCol);
    if (esEntero(col)) {
      tipo = true;
    } else {
      tipo = false;
    }
    agregarColTabla(nueva, nombreCol, tipo);
    delete[] nombreCol;
  }
}

void agregarDatosTabla(Tabla &nueva, Columna lcTabla, char *strArray[], int cantCols) {
  agregarCeldasCol(nueva->col, lcTabla, strArray, cantCols);
}
