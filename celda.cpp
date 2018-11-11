#include "celda.hh"
#include "columna.hh"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

union _unionTipo {
    int datoInt;
    char *datoStr;
};

struct _strCelda {
    tipoU dato;
    Celda sig;
};

Celda crearCelda() {
  Celda cel = new _strCelda();
  cel->sig = NULL;
  return cel;
}

Celda agregarCelda(Celda listaCel) {
  Celda nueva = crearCelda();
  nueva->sig = listaCel;
  listaCel = nueva;
  return listaCel;
}

void setDatoInt(Celda &cel, int dato) {
  cel->dato.datoInt = dato;
}

void setDatoStr(Celda &cel, char *dato) {
  cel->dato.datoStr = dato;
}

int getDatoInt(Celda cel) {
  return cel->dato.datoInt;
}

char *getDatoStr(Celda cel) {
  return cel->dato.datoStr;
}

Celda getCeldaSig(Celda cel) {
  return cel->sig;
}

void setCeldaSig(Celda cel, Celda sig) {
  cel->sig = sig;
}

bool pkDuplicada(Celda listaCel, char *dato) {
  if (listaCel == NULL) {
    return false;
  } else if (listaCel->dato.datoStr == dato || listaCel->dato.datoInt == atoi(dato)) {
    return true;
  } else {
    return pkDuplicada(listaCel->sig, dato);
  }
}

void insertarCeldaIndice(Celda &listaCel, bool esEntero, char *dato, int indice) {
  Celda actual = listaCel;
  Celda anterior = NULL;
  for (int i = indice; i > 0; i--) {
    anterior = actual;
    actual = actual->sig;
  }
  Celda nueva = crearCelda();
  if (esEntero) {
    setDatoInt(nueva, atoi(dato));
  } else {
    setDatoStr(nueva, dato);
  }
  if (anterior == NULL) {
    setCeldaSig(nueva, actual);
    listaCel = nueva;
  } else {
    setCeldaSig(anterior, nueva);
    setCeldaSig(nueva, actual);
  }
}

int insertarCeldaOrdenada(Celda &listaCel, bool esEntero, char *dato) {
  Celda nueva = crearCelda();
  if (esEntero) {
    setDatoInt(nueva, atoi(dato));
  } else {
    setDatoStr(nueva, dato);
  }
  Celda actual = listaCel;
  Celda anterior = NULL;
  int indice = 0;
  if (listaCel == NULL) {
    listaCel = nueva;
  } else {
    if (esEntero) {
      while (actual != NULL && getDatoInt(actual) < atoi(dato)) {
        anterior = actual;
        actual = getCeldaSig(actual);
        indice++;
      }
    } else {
      while (actual != NULL && strcmp(getDatoStr(actual), dato) < 0) {
        anterior = actual;
        actual = getCeldaSig(actual);
        indice++;
      }
    }
    if (anterior == NULL) {
      setCeldaSig(nueva, actual);
      listaCel = nueva;
    } else {
      setCeldaSig(anterior, nueva);
      setCeldaSig(nueva, actual);
    }
  }
  return indice;
}

int cantidadTuplas(Celda listaCel) {
  if (listaCel != NULL) {
    return 1 + cantidadTuplas(listaCel->sig);
  } else {
    return 0;
  }
}

void eliminarCeldasCol(Celda &listaCel) {
  if (listaCel != NULL) {
    eliminarCeldasCol(listaCel->sig);
    delete listaCel;
  }
  listaCel = NULL;
}


void eliminarCelda(Celda &cel, int indice) {
  Celda aux = cel;
  Celda anterior = NULL;
  if (aux != NULL) {
    for (int i = 0; i < indice; i++) {
      anterior = aux;
      aux = getCeldaSig(aux);
    }
    if (anterior == NULL) {
      cel = getCeldaSig(cel);
      delete aux;
    } else {
      if (getCeldaSig(aux) == NULL) {
        setCeldaSig(anterior, NULL);
        delete aux;
      } else {
        setCeldaSig(anterior, getCeldaSig(aux));
        delete aux;
      }
    }
  }
}
