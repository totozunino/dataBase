///////////////////////////////////////////////
//                                           //
//          Obligatorio EDA Parte 1          //
//          Integrantes: Braian Romero       //
//                       Mateo Sayas         //
//                       Mathias Zunino      //
//          Tecnologo  Año 2018              //
//                                           //
///////////////////////////////////////////////
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "bd.hh"
#include "define.hh"

using namespace std;

int main() {
  Base bd = crearBase();
  createTable(bd, "Personas");
  createTable(bd, "Trabajan");
  addCol(bd, "Trabajan", "CI");
  addCol(bd, "Trabajan", "Nombre");
  addCol(bd, "Personas", "CI");
  addCol(bd, "Personas", "Nombre");
  insertInto(bd, "Trabajan", "666:toto");
  insertInto(bd, "Personas", "666:toto");
  insertInto(bd, "Trabajan", "662:pepe");
  insertInto(bd, "Personas", "662:pepe");
  selectWhere(bd, "Personas2", "CI>664", "Personas");
  select(bd, "Putos", "Nombre:CI", "Personas");
  join(bd, "Personas", "Trabajan", "Trabajadores");


  char *comando = new (char[MAX_COMANDO]);
  char *pch, *pch1, *pch2, *pch3;
  TipoRet ret;
  bool ejecutado = false;
  bool iguales;

  bool salir = false;

  do {
    cout << "\tcreateTable (nombreTabla)\n";
    cout << "\tdropTable (nombreTabla)\n";
    cout << "\taddCol (nombreTabla, NombreCol)\n";
    cout << "\tdropCol (nombreTabla, NombreCol)\n";
    cout << "\tinsertInto (nombreTabla, valoresTupla)\n";
    cout << "\tdeleteFrom (nombreTabla, condicionEliminar)\n";
    cout << "\tupdate (nombreTabla, condicionModificar, columnaModificar, valorModificar)\n";
    cout << "\tprintdatatable (NombreTabla)\n";
    cout << "\tselectWhere (nomTabla2, condicion, nomTabla1)\n";
    cout << "\tselect (nomTabla2, nomColumnas, nomTabla1)\n";
    cout << "\tjoin (nomTabla1, nomTabla2, nomTabla3)\n";
    cout << "\tequalTables(nomTabla1, nomTabla2\n";
    cout << "\tprintTables ()\n";
    cout << "\tprintMetadata (nombreTabla)\n";
    cout << "\trecent()\n";
    cout << "\tsalir\n\n";
    cout << "> ";
    fflush(stdin);
    ejecutado = false;

    fgets(comando, MAX_COMANDO, stdin);

    pch = strtok(comando, "( ,)\n");

    if (strcasecmp(pch, "createTable") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        ret = createTable(bd, pch);
        ejecutado = true;
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "dropTable") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        ret = dropTable(bd, pch);
        ejecutado = true;
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "addCol") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          ret = addCol(bd, pch, pch1);
          ejecutado = true;
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "dropCol") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          ret = dropCol(bd, pch, pch1);
          ejecutado = true;
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "insertInto") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          ret = insertInto(bd, pch, pch1);
          ejecutado = true;
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "deleteFrom") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          ret = deleteFrom(bd, pch, pch1);
          ejecutado = true;
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "update") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          pch2 = strtok(NULL, "( ,)\n");
          if (pch2 != NULL) {
            pch3 = strtok(NULL, "( ,)\n");
            if (pch3 != NULL) {
              ret = update(bd, pch, pch1, pch2, pch3);
              ejecutado = true;
            } else
              cout << " - ERROR: Faltan Parametros.\n";
          } else
            cout << " - ERROR: Faltan Parametros.\n";
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "printdatatable") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        ret = printDataTable(bd, pch);
        ejecutado = true;
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "selectWhere") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          pch2 = strtok(NULL, "( ,)\n");
          if (pch2 != NULL) {
            ret = selectWhere(bd, pch, pch1, pch2);
            ejecutado = true;
          } else
            cout << " - ERROR: Faltan Parametros.\n";
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "select") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          pch2 = strtok(NULL, "( ,)\n");
          if (pch2 != NULL) {
            ret = select(bd, pch, pch1, pch2);
            ejecutado = true;
          } else
            cout << " - ERROR: Faltan Parametros.\n";
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "join") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          pch2 = strtok(NULL, "( ,)\n");
          if (pch2 != NULL) {
            ret = join(bd, pch, pch1, pch2);
            ejecutado = true;
          } else
            cout << " - ERROR: Faltan Parametros.\n";
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "equalTables") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        pch1 = strtok(NULL, "( ,)\n");
        if (pch1 != NULL) {
          ret = equalTables(bd, pch, pch1, iguales);
          ejecutado = true;
          if (ret == OK) {
            if (iguales)
              cout << " - Las tablas son iguales.\n";
            else
              cout << " - Las tablas son distintas.\n";
          }
        } else
          cout << " - ERROR: Faltan Parametros.\n";
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "printTables") == 0) {
      ret = printTables(bd);
      ejecutado = true;
    } else if (strcasecmp(pch, "printMetadata") == 0) {
      pch = strtok(NULL, "( ,)\n");
      if (pch != NULL) {
        ret = printMetadata(bd, pch);
        ejecutado = true;
      } else
        cout << " - ERROR: Faltan Parametros.\n";
    } else if (strcasecmp(pch, "recent") == 0) {
      ret = recent(bd);
      ejecutado = true;
    } else if (strcasecmp(pch, "salir") == 0) {
      salir = true;
    } else
      cout << " - Comando Incorrecto\n";
    if (ejecutado) {
      if (ret == OK)
        cout << " - OK\n\n";
      else if (ret == ERROR)
        cout << " - ERROR\n\n";
      else
        cout << " - NO IMPLEMENTADA\n\n";
    }
  } while (!salir);
  cout << "\n\n - CHAUU!!!!\n";

  bd = eliminarBase(bd);
  delete[] comando;
}
