#include "utilidades.hh"
#include <iostream>
#include <stdlib.h>
#include <string.h>

struct _strDArray {
  int *array;
  int tope;
  int tam;
};

DArray crearDArray() {
  DArray da = new _strDArray;
  da->array = new int[1];
  da->tam = 0;
  da->tope = 0;
  return da;
}

void redimDArray(DArray &da, int tam) {
  int *aux = new int[da->tam + tam];
  da->tam += tam;
  for (int i = 0; i < da->tope; i++) {
    aux[i] = da->array[i];
  }
  delete[] da->array;
  da->array = aux;
}

int cantDArray(DArray da) { return da->tope; }

void setTope(DArray &da, int tope) { da->tope += tope; }

void setArrayIndice(DArray &da, int indice, int pos) {
  da->array[indice] = pos;
}

int getValorDArray(DArray da, int pos) { return da->array[pos]; }

void eliminarDArray(DArray &da) {
  delete[] da->array;
  delete da;
}

int cantidadValores(const char *valores) {
  int cont = 0;
  char *copiaValores = new char[strlen(valores) + 1];
  strcpy(copiaValores, valores);
  char *valor = strtok(copiaValores, ":");
  while (valor != NULL) {
    valor = strtok(NULL, ":");
    cont++;
  }
  delete[] copiaValores;
  return cont;
}

void parsearValores(char *strArray[], int largo, const char *valores) {
  int indice = 0;
  char *copiaValores = new char[strlen(valores) + 1];
  strcpy(copiaValores, valores);
  char *valor;
  valor = strtok(copiaValores, ":");
  while ((valor != NULL) && (indice <= largo)) {
    strArray[indice] = valor;
    valor = strtok(NULL, ":");
    indice++;
  }
  delete[] copiaValores;
}

bool esNumero(const char *string) {
  int largo = strlen(string);
  for (int i = 0; i < largo; i++) {
    if (!isdigit(string[i])) {
      return false;
    }
  }
  return true;
}

int parsearCondicion(char *strArray[], int largo, const char *condicion) {
  int indice = 0;
  char *copiaCondicion = new char[strlen(condicion) + 1];
  strcpy(copiaCondicion, condicion);
  char *valor;
  valor = strtok(copiaCondicion, "=!><*");
  while (valor != NULL && indice <= largo) {
    strArray[indice] = valor;
    valor = strtok(NULL, "=!><*");
    indice++;
  }
  delete[] copiaCondicion;
  return indice;
}

int cantColumnas(char *nombreCols) {
  int cant = 0;
  char *copiaNombreColumas = new char[strlen(nombreCols) + 1];
  strcpy(copiaNombreColumas, nombreCols);
  char *valor = strtok(copiaNombreColumas, ":");
  while (valor != NULL) {
    valor = strtok(NULL, ":");
    cant++;
  }
  delete[] copiaNombreColumas;
  return cant;
}

char obtenerOperador(const char *condicion) {
  char retorno = 'a';
  char *copiaCondicion = new char[strlen(condicion) + 1];
  strcpy(copiaCondicion, condicion);
  int cont = 0;
  while (retorno != '=' && retorno != '!' && retorno != '>' && retorno != '<' &&
         retorno != '*') {
    retorno = copiaCondicion[cont];
    cont++;
  }
  delete[] copiaCondicion;
  return retorno;
}

bool compararPrefijoStr(char *dato, char *prefijo) {
  int cont = 0;
  bool iguales = true;
  if (strlen(dato) > strlen(prefijo)) {
    while (prefijo[cont] != '\0' && iguales) {
      if (dato[cont] != prefijo[cont]) {
        iguales = false;
      } else {
        cont++;
      }
    }
  } else {
    return false;
  }
  return iguales;
}

bool compararPrefijoInt(int dato, int prefijo) {
  bool iguales;
  while (prefijo < dato) {
    dato = dato / 10;
  }
  if (dato == prefijo) {
    iguales = true;
  } else {
    iguales = false;
  }
  return iguales;
}

bool preguntarTipoCol() {
  printf("Elija un tipo de dato para su columna:\n1)Enteros\n2)Strings\n");
  int opcion = 0;
  scanf("%d", &opcion);
  getchar();
  if (opcion == 1) {
    return true;
  } else {
    return false;
  }
}
