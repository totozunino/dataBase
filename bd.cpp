#include "bd.hh"
#include "tabla.hh"
#include "columna.hh"
#include "celda.hh"
#include "utilidades.hh"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"

using namespace std;

struct _strBase {
    Tabla tb;
    char *modificadas[MAX_MODIFICADAS];
};

Base crearBase() {
  Base bd = new _strBase;
  bd->tb = NULL;
  return bd;
}

TipoRet createTable(Base bd, char *nombreTabla) {
  if (!(existeTabla(bd->tb, nombreTabla))) {
    agregarTabla(bd->tb, nombreTabla);
    return OK;
  } else
    return ERROR;
}

TipoRet dropTable(Base bd, char *nombreTabla) {
  if (existeTabla(bd->tb, nombreTabla)) {
    eliminarTabla(bd->tb, nombreTabla);
    return OK;
  } else {
    return ERROR;
  }
}

TipoRet addCol(Base bd, char *nombreTabla, char *nombreColumna) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    if (!existeColTabla(tabla, nombreColumna)) {
      Columna listaCol = obtenerListaCol(tabla);
      bool esEntero;
      if (listaCol == NULL) {
        esEntero = preguntarTipoCol();
        agregarColTabla(tabla, nombreColumna, esEntero);
        return OK;
      } else {
        if (!existeListaCel(listaCol)) {
          esEntero = preguntarTipoCol();
          agregarColTabla(tabla, nombreColumna, esEntero);
          return OK;
        } else {
          return ERROR;
        }
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet dropCol(Base bd, char *nombreTabla, char *nombreColumna) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    if (existeColTabla(tabla, nombreColumna)) {
      Columna listaCol = obtenerListaCol(tabla);
      if (esUnicaCol(listaCol, nombreColumna)) {
        eliminarColTabla(tabla, listaCol, nombreColumna);
        return OK;
      } else {
        if (!esPk(listaCol, nombreColumna)) {
          eliminarColTabla(tabla, listaCol, nombreColumna);
          return OK;
        } else {
          return ERROR;
        }
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet insertInto(Base bd, char *nombreTabla, char *valores) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    Columna listaCol = obtenerListaCol(tabla);
    if (cantidadCol(listaCol) == cantidadValores(valores)) {
      char *strArray[cantidadValores(valores)];
      parsearValores(strArray, cantidadValores(valores), valores);
      Celda cel = obtenerListaCel(listaCol);
      if (checkTipos(listaCol, strArray, 0)) {
        if (!pkDuplicada(cel, strArray[0])) {
          insertarTuplaOrdenada(listaCol, strArray);
          if (bd->modificadas[0] == NULL) {
            bd->modificadas[0] = nombreTabla;
          } else {
            checkModificadas(nombreTabla, bd->modificadas);
            insertarModificadas(nombreTabla, bd->modificadas, 0);
          }
          return OK;
        }
        return ERROR;
      } else {
        return ERROR;
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet printDataTable(Base bd, char *nombreTabla) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    printf("%s\n", nombreTabla);
    Columna listaCol = obtenerListaCol(tabla);
    bool tipof = false;
    if (listaCol != NULL) {
      imprimirCols(listaCol, tipof);
      printf("\n");
      imprimirTuplas(listaCol);
      return OK;
    } else {
      return OK;
    }
  } else {
    return ERROR;
  }
}

TipoRet deleteFrom(Base bd, char *nombreTabla, char *condicion) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    char *strArray[2];
    int cantParseos = parsearCondicion(strArray, 2, condicion);
    if (strcmp(condicion, "\"\"") == 0) {
      Columna listaCol = obtenerListaCol(tabla);
      eliminarTodasTuplas(listaCol);
      if (bd->modificadas[0] == NULL) {
        bd->modificadas[0] = nombreTabla;
      } else {
        checkModificadas(nombreTabla, bd->modificadas);
        insertarModificadas(nombreTabla, bd->modificadas, 0);
      }
      return OK;
    } else {
      if (cantParseos == 2) {
        if (existeColTabla(tabla, strArray[0])) {
          char operador = obtenerOperador(condicion);
          Columna listaCol = obtenerListaCol(tabla);
          eliminarTuplasIndice(listaCol, operador, strArray);
          if (bd->modificadas[0] == NULL) {
            bd->modificadas[0] = nombreTabla;
          } else {
            checkModificadas(nombreTabla, bd->modificadas);
            insertarModificadas(nombreTabla, bd->modificadas, 0);
          }
          return OK;
        } else {
          return ERROR;
        }
      } else {
        return ERROR;
      }
    }
  } else {
    return ERROR;
  }
}

TipoRet update(Base bd, char *nombreTabla, char *condicion, char *nombreCol, char *valor) {
  if (existeTabla(bd->tb, nombreTabla)) {
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    char *strArray[2];
    int cantParseos = parsearCondicion(strArray, 2, condicion);
    if (cantParseos == 2) {
      if (existeColTabla(tabla, strArray[0])) {
        char operador = obtenerOperador(condicion);
        Columna listaCol = obtenerListaCol(tabla);
        if (!esPk(listaCol, nombreCol)) {
          updateTuplasIndice(listaCol, operador, strArray, nombreCol, valor);
          if (bd->modificadas[0] == NULL) {
            bd->modificadas[0] = nombreTabla;
          } else {
            checkModificadas(nombreTabla, bd->modificadas);
            insertarModificadas(nombreTabla, bd->modificadas, 0);
          }
          return OK;
        } else {
          Columna col = obtenerColumna(listaCol, strArray[0]);
          Celda cel = obtenerListaCel(col);
          bool tipo = false;
          if (esEntero(col)) {
            tipo = true;
          }
          if (checkearDatos(cel, strArray[1], operador, tipo) > 1) {
            return ERROR;
          } else {
            if (checkearValor(cel, valor, tipo)) {
              updateTuplasIndice(listaCol, operador, strArray, nombreCol, valor);
              if (bd->modificadas[0] == NULL) {
                bd->modificadas[0] = nombreTabla;
              } else {
                checkModificadas(nombreTabla, bd->modificadas);
                insertarModificadas(nombreTabla, bd->modificadas, 0);
              }
              return OK;
            } else {
              return ERROR;
            }
          }
        }
      } else {
        return ERROR;
      }
    } else {
      return ERROR;
    }

  } else {
    return ERROR;
  }
}

TipoRet selectWhere(Base bd, char *nombreTabla2, char *condicion, char *nombreTabla) {
  if (existeTabla(bd->tb, nombreTabla)) {
    if (!existeTabla(bd->tb, nombreTabla2)) {
      Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
      Columna lctabla = obtenerListaCol(tabla);
      if (strcmp(condicion, "\"\"") == 0) {
        agregarTabla(bd->tb, nombreTabla2);
        Tabla nueva = obtenerTabla(bd->tb, nombreTabla2);
        copiarColumnasTabla(lctabla, nueva);
        tuplasTabla(lctabla, nueva);
        return OK;
      } else {
        char *strArray[2];
        int cantParseos = parsearCondicion(strArray, 2, condicion);
        if (cantParseos == 2) {
          char operador = obtenerOperador(condicion);
          agregarTabla(bd->tb, nombreTabla2);
          Tabla nueva = obtenerTabla(bd->tb, nombreTabla2);
          copiarColumnasTabla(lctabla, nueva);
          copiarTuplasTabla(lctabla, nueva, operador, strArray);
          return OK;
        } else {
          return ERROR;
        }
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet select(Base bd, char *nombreTabla2, char *nombreCols, char *nombreTabla1) {
  if (existeTabla(bd->tb, nombreTabla1)) {
    if (!existeTabla(bd->tb, nombreTabla2)) {
      Tabla tabla = obtenerTabla(bd->tb, nombreTabla1);
      Columna lcTabla = obtenerListaCol(tabla);
      int cantCols = cantColumnas(nombreCols);
      char *strArray[cantCols];
      parsearValores(strArray, cantCols, nombreCols);
      if (existenColumnas(lcTabla, strArray, cantCols)) {
        agregarTabla(bd->tb, nombreTabla2);
        Tabla nueva = obtenerTabla(bd->tb, nombreTabla2);
        agregarColEspecificas(nueva, lcTabla, strArray, cantCols);
        agregarDatosTabla(nueva, lcTabla, strArray, cantCols);
        return OK;
      } else {
        return ERROR;
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet join(Base bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3) {
  if (existeTabla(bd->tb, nombreTabla1)) {
    if (existeTabla(bd->tb, nombreTabla2)) {
      if (!existeTabla(bd->tb, nombreTabla3)) {
        Tabla tabla1 = obtenerTabla(bd->tb, nombreTabla1);
        Tabla tabla2 = obtenerTabla(bd->tb, nombreTabla2);
        Columna lcTabla1 = obtenerListaCol(tabla1);
        Columna lcTabla2 = obtenerListaCol(tabla2);
        if (lcTabla1 != NULL && lcTabla2 != NULL) {
          if (mismaPk(lcTabla1, lcTabla2)) {
            if (!columnasRepetidas(lcTabla1, lcTabla2)) {
              agregarTabla(bd->tb, nombreTabla3);
              Tabla nueva = obtenerTabla(bd->tb, nombreTabla3);
              copiarColumnasTabla(lcTabla1, nueva);
              Columna lcTabla2sig = obtenerColSig(lcTabla2);
              copiarColumnasTabla(lcTabla2sig, nueva);
              Columna lcNueva = obtenerListaCol(nueva);
              copiarDatosColumnas(lcNueva, lcTabla1, lcTabla2);
              return OK;
            } else {
              return ERROR;
            }
          } else {
            return ERROR;
          }
        } else {
          return ERROR;
        }
      } else {
        return ERROR;
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet equalTables(Base bd, char *nombreTabla1, char *nombreTabla2, bool &iguales) {
  if (existeTabla(bd->tb, nombreTabla1)) {
    if (existeTabla(bd->tb, nombreTabla2)) {
      Tabla tabla1 = obtenerTabla(bd->tb, nombreTabla1);
      Tabla tabla2 = obtenerTabla(bd->tb, nombreTabla2);
      Columna lcTabla1 = obtenerListaCol(tabla1);
      Columna lcTabla2 = obtenerListaCol(tabla2);
      if (mismosTipos(lcTabla1, lcTabla2)) {
        if (mismasColumnas(lcTabla1, lcTabla2)) {
          if (mismosDatos(lcTabla1, lcTabla2)) {
            iguales = true;
            return OK;
          } else {
            iguales = false;
            return OK;
          }
        } else {
          iguales = false;
          return OK;
        }
      } else {
        return ERROR;
      }
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

TipoRet printTables(Base bd) {
  if (bd == NULL) {
    printf("No hay tablas en la base de datos\n");
    return OK;
  } else {
    imprimirTablasOrd(bd->tb);
    return OK;
  }
}

TipoRet printMetadata(Base bd, char *nombreTabla) {
  if (existeTabla(bd->tb, nombreTabla)) {
    printf("%s\n", nombreTabla);
    Tabla tabla = obtenerTabla(bd->tb, nombreTabla);
    Columna listaCol = obtenerListaCol(tabla);
    bool tipof = true;
    if (listaCol != NULL) {
      imprimirCols(listaCol, tipof);
      printf("\n");
      return OK;
    } else {
      printf("No hay columnas en %s\n", nombreTabla);
      return OK;
    }
  } else {
    return ERROR;
  }
}

TipoRet recent(Base bd) {
  if (bd->modificadas[0] == NULL) {
    printf("No hay tablas modificadas\n");
    return OK;
  } else {
    int cont = 0;
    while (bd->modificadas[cont] != NULL && cont < MAX_MODIFICADAS) {
      printf("%s\n", bd->modificadas[cont]);
      cont++;
    }
    return OK;
  }
}

Base eliminarBase(Base &bd) {
  eliminarTodasTablas(bd->tb);
  delete bd;
  return NULL;
}
