#include "celda.hh"
#include "columna.hh"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "utilidades.hh"

struct _strColumna {
    char *nombre;
    Celda cel;
    bool esEntero;
    Columna sig;
};

Columna crearCol(const char *nombreColumna, bool esEntero) {
  Columna col = new _strColumna;
  char *nombre = new char[strlen(nombreColumna) + 1];
  strcpy(nombre, nombreColumna);
  col->nombre = nombre;
  col->esEntero = esEntero;
  col->sig = NULL;
  col->cel = NULL;
  return col;
}

Columna agregarCol(Columna listaCol, const char *nombreColumna, bool esEntero) {
  if (listaCol == NULL) {
    Columna nueva = crearCol(nombreColumna, esEntero);
    return nueva;
  } else {
    listaCol->sig = agregarCol(listaCol->sig, nombreColumna, esEntero);
    return listaCol;
  }
}

bool existeCol(Columna listaCol, const char *nombreColumna) {
  if (listaCol == NULL)
    return false;
  else if (strcmp(listaCol->nombre, nombreColumna) == 0)
    return true;
  else
    return existeCol(listaCol->sig, nombreColumna);
}

Columna obtenerColumna(Columna listaCol, char *nombreColumna) {
  if (listaCol != NULL) {
    if (strcmp(listaCol->nombre, nombreColumna) == 0) {
      return listaCol;
    } else {
      return obtenerColumna(listaCol->sig, nombreColumna);
    }
  } else {
    return NULL;
  }
}

bool esEntero(Columna col) {
  return col->esEntero;
}

bool esUnicaCol(Columna listaCol, char *nombreColumna) {
  return strcmp(listaCol->nombre, nombreColumna) == 0 && listaCol->sig == NULL;
}

bool esPk(Columna listaCol, char *nombreColumna) {
  return strcmp(listaCol->nombre, nombreColumna) == 0;
}

int cantidadCol(Columna listaCol) {
  if (listaCol == NULL) {
    return 0;
  } else {
    return 1 + cantidadCol(listaCol->sig);
  }
}

void crearTupla(Columna listaCol) {
  if (listaCol != NULL) {
    if (listaCol->cel == NULL) {
      listaCol->cel = crearCelda();
      crearTupla(listaCol->sig);
    } else {
      listaCol->cel = agregarCelda(listaCol->cel);
      crearTupla(listaCol->sig);
    }
  }
}

void insertarTuplaOrdenada(Columna listaCol, char *datos[]) {
  int posDato = 0;
  int indice = insertarCeldaOrdenada(listaCol->cel, listaCol->esEntero, datos[posDato]);
  posDato++;
  for (Columna c = listaCol->sig; c != NULL; c = c->sig) {
    insertarCeldaIndice(c->cel, c->esEntero, datos[posDato], indice);
    posDato++;
  }
}

Celda obtenerListaCel(Columna col) {
  return col->cel;
}

bool existeListaCel(Columna listaCol) {
  return listaCol->cel != NULL;
}

bool checkTipos(Columna listaCol, char *valores[], int indice) {
  if (listaCol != NULL) {
    if (esEntero(listaCol) && esNumero(valores[indice])) {
      return checkTipos(listaCol->sig, valores, indice + 1);
    } else if (!esEntero(listaCol) && !esNumero(valores[indice])) {
      return checkTipos(listaCol->sig, valores, indice + 1);
    } else {
      return false;
    }
  } else {
    return true;
  }
}

bool existenColumnas(Columna listaCol, char *strArray[], int cantCols) {
  bool existe = true;
  for (int i = 0; i < cantCols; i++) {
    if (!existeCol(listaCol, strArray[i])) {
      existe = false;
    }
  }
  return existe;
}

void imprimirCols(Columna listaCol) {
  if (listaCol != NULL) {
    printf("%s", listaCol->nombre);
    if (listaCol->sig != NULL) {
      printf(":");
    }
    imprimirCols(listaCol->sig);
  }
}

void imprimirTuplas(Columna listaCol) {
  for (int i = 0; i < cantidadTuplas(listaCol->cel); i++) {
    imprimirTupla(listaCol, i);
  }
}

void imprimirTupla(Columna listaCol, int pos) {
  for (Columna c = listaCol; c != NULL; c = c->sig) {
    Celda aux = c->cel;
    for (int i = 0; i < pos; i++) {
      c->cel = getCeldaSig(c->cel);
    }
    if (esEntero(c)) {
      printf("%d", getDatoInt(c->cel));
      c->cel = aux;
    } else {
      printf("%s", getDatoStr(c->cel));
      c->cel = aux;
    }
    if (c->sig != NULL) {
      printf(":");
    } else {
      printf("\n");
    }
  }
}

void eliminarTodasCol(Columna &listaCol) {
  if (listaCol != NULL) {
    eliminarTodasCol(listaCol->sig);
    eliminarCeldasCol(listaCol->cel);
    delete[] listaCol->nombre;
    delete listaCol;
  }
}

Columna eliminarColumna(Columna &listaCol, char *nombreColumna) {
  Columna anterior = NULL;
  Columna actual = listaCol;
  bool encontre = false;
  while (actual != NULL && !encontre) {
    if (strcmp(actual->nombre, nombreColumna) != 0) {
      anterior = actual;
      actual = actual->sig;
    } else {
      encontre = true;
    }
  }
  if (anterior == NULL) {
    if (actual->sig != NULL) {
      listaCol = actual->sig;
      delete[] actual->nombre;
      eliminarCeldasCol(actual->cel);
      delete actual;
    } else {
      delete[] listaCol->nombre;
      eliminarCeldasCol(actual->cel);
      delete listaCol;
      listaCol = NULL;
    }
  } else {
    anterior->sig = actual->sig;
    delete[] actual->nombre;
    eliminarCeldasCol(actual->cel);
    delete actual;
  }
  return listaCol;
}

void obtenerPosicionesTuplas(Columna listaCol, char operador, char *strArray[], DArray &da) {
  Columna col = obtenerColumna(listaCol, strArray[0]);
  int pos = 0;
  int indice = 0;
  for (Celda cel = col->cel; cel != NULL; cel = getCeldaSig(cel)) {
    switch (operador) {
      case '=':
        if (esEntero(col)) {
          if (getDatoInt(cel) == atoi(strArray[1])) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        } else {
          if (strcmp(getDatoStr(cel), strArray[1]) == 0) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        }
        break;
      case '!':
        if (esEntero(col)) {
          if (getDatoInt(cel) != atoi(strArray[1])) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        } else {
          if (strcmp(getDatoStr(cel), strArray[1]) != 0) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        }
        break;
      case '<':
        if (esEntero(col)) {
          if (getDatoInt(cel) < atoi(strArray[1])) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        } else {
          if (strcmp(getDatoStr(cel), strArray[1]) < 0) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        }
        break;
      case '>':
        if (esEntero(col)) {
          if (getDatoInt(cel) > atoi(strArray[1])) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        } else {
          if (strcmp(getDatoStr(cel), strArray[1]) > 0) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        }
        break;
      case '*':
        if (esEntero(col)) {
          if (compararPrefijoInt(getDatoInt(cel), atoi(strArray[1]))) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        } else {
          if (compararPrefijoStr(getDatoStr(cel), strArray[1])) {
            redimDArray(da, 1);
            setTope(da, 1);
            setArrayIndice(da, indice, pos);
            pos++;
            indice++;
          } else {
            pos++;
          }
        }
        break;
    }
  }
}

void eliminarTuplasIndice(Columna listaCol, char operador, char *strArray[]) {
  DArray da = crearDArray();
  obtenerPosicionesTuplas(listaCol, operador, strArray, da);
  int cantEliminadas = 0;
  for (int i = 0; i < cantDArray(da); i++) {
    eliminarTuplaCol(listaCol, getValorDArray(da, i) - cantEliminadas);
    cantEliminadas++;
  }
  eliminarDArray(da);
}

void eliminarTuplaCol(Columna &listaCol, int indice) {
  for (Columna col = listaCol; col != NULL; col = col->sig) {
    eliminarCelda(col->cel, indice);
  }
}

void eliminarTodasTuplas(Columna &listaCol) {
  for (Columna col = listaCol; col != NULL; col = col->sig) {
    eliminarCeldasCol(col->cel);
  }
}

void updateTuplasIndice(Columna listaCol, char operador, char *strArray[], char *nombreCol, char *valor) {
  DArray da = crearDArray();
  obtenerPosicionesTuplas(listaCol, operador, strArray, da);
  for (int i = 0; i < cantDArray(da); i++) {
    updateTupla(listaCol, getValorDArray(da, i), nombreCol, valor);
  }
  eliminarDArray(da);
}

void updateTupla(Columna listaCol, int pos, char *nombreCol, char *valor) {
  Columna col = obtenerColumna(listaCol, nombreCol);
  Celda cel = col->cel;
  for (int x = 0; x < pos; x++) {
    cel = getCeldaSig(cel);
  }
  if (esEntero(col)) {
    setDatoInt(cel, atoi(valor));
  } else {
    setDatoStr(cel, valor);
  }
}

int checkearDatos(Celda listaCel, char *valor, bool tipo) {
  if (listaCel != NULL) {
    if (tipo) {
      if (getDatoInt(listaCel) == atoi(valor)) {
        return 1 + checkearDatos(getCeldaSig(listaCel), valor, tipo);
      } else {
        return 0 + checkearDatos(getCeldaSig(listaCel), valor, tipo);
      }
    } else {
      if (strcmp(getDatoStr(listaCel), valor) == 0) {
        return 1 + checkearDatos(getCeldaSig(listaCel), valor, tipo);
      } else {
        return 0 + checkearDatos(getCeldaSig(listaCel), valor, tipo);
      }
    }
  } else {
    return 0;
  }
}

bool checkearValor(Celda listaCel, char *valor, bool tipo) {
  if (listaCel != NULL) {
    if (tipo) {
      if (getDatoInt(listaCel) == atoi(valor)) {
        return false;
      } else {
        return checkearValor(getCeldaSig(listaCel), valor, tipo);
      }
    } else {
      if (strcmp(getDatoStr(listaCel), valor) == 0) {
        return false;
      } else {
        return checkearValor(getCeldaSig(listaCel), valor, tipo);
      }
    }
  } else {
    return true;
  }
}

void obtenerDatos(char *datos[], Columna listaCol, int pos) {
  int indice = 0;
  for (Columna col = listaCol; col != NULL; col = col->sig) {
    Celda cel = col->cel;
    for (int i = 0; i < pos; i++) {
      cel = getCeldaSig(col->cel);
    }
    if (esEntero(col)) {
      sprintf(datos[indice], "%d", getDatoInt(cel));
    } else {
      datos[indice] = getDatoStr(cel);
    }
    indice++;
  }
}

void copiarColumnas(Columna lcTabla, Columna &lcNueva) {
  for (Columna col = lcTabla; col != NULL; col = col->sig) {
    char *nombreColumna = new char[strlen(col->nombre) + 1];
    strcpy(nombreColumna, col->nombre);
    lcNueva = agregarCol(lcNueva, nombreColumna, col->esEntero);
    delete[] nombreColumna;
  }
}

void copiarTuplasIndice(Columna lcTabla, Columna &lcNueva, char operador, char *strArray[]) {
  DArray da = crearDArray();
  obtenerPosicionesTuplas(lcTabla, operador, strArray, da);
  char *datos[cantidadCol(lcTabla)];
  for (int i = 0; i < cantDArray(da); i++) {
    obtenerDatos(datos, lcTabla, getValorDArray(da, i));
    insertarTuplaOrdenada(lcNueva, datos);
  }
  eliminarDArray(da);
}

void copiarTodasTuplas(Columna lcTabla, Columna &lcNueva) {
  char *datos[cantidadCol(lcTabla)];
  for (int i = 0; i < cantidadTuplas(lcTabla->cel); i++) {
    obtenerDatos(datos, lcTabla, i);
    insertarTuplaOrdenada(lcNueva, datos);
  }
}

void agregarCeldasCol(Columna &lcNueva, Columna lcTabla, char *strArray[], int cantCols) {
  for (int i = 0; i < cantCols; ++i) {
    Columna colNueva = obtenerColumna(lcNueva, strArray[i]);
    Columna colTabla = obtenerColumna(lcTabla, strArray[i]);
    for (Celda cel = colTabla->cel; cel != NULL; cel = getCeldaSig(cel)) {
      colNueva->cel = agregarCelda(colNueva->cel);
      if (esEntero(colTabla)) {
        setDatoInt(colNueva->cel, getDatoInt(cel));
      } else {
        setDatoStr(colNueva->cel, getDatoStr(cel));
      }
    }
  }
}
