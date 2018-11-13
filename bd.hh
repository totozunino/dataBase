#ifndef BD_HH
#define BD_HH

#include "define.hh"

typedef struct _strBase *Base;

Base crearBase();
// Crea la base de datos vacia

Base eliminarBase(Base &bd);
// Elimina a base de datos

TipoRet createTable(Base bd, char *nombreTabla);
// Crea la tabla

TipoRet dropTable(Base bd, char *nombreTabla);
// Elimina una tabla

TipoRet addCol(Base bd, char *nombreTabla, char *nombreCol);
// Añade una columna

TipoRet dropCol(Base bd, char *nombreTabla, char *nombreCol);
// Elimina una columna

TipoRet insertInto(Base bd, char *nombreTabla, char *valores);
// Inserta valores a una tabla

TipoRet printDataTable(Base bd, char *nombreTabla);
// Immprime los datos de una tabla

TipoRet deleteFrom(Base bd, char *nombreTabla, char *condicion);
// Elimina las tuplas que cumplan la condicion

TipoRet update(Base bd, char *nombreTabla, char *condicion, char *nombreCol, char *valor);
// Modifica una tupla

TipoRet selectWhere(Base bd, char *nombreTabla2, char *condicion, char *nombreTabla);
// Crea una tabla con los datos de la tabla2 que cumplen la condicion

TipoRet select(Base bd, char *nombreTabla2, char *nombreCols, char *nombreTabla1);
// Crea una tabla con las columnas especificadas y sus datos

TipoRet join(Base bd, char *nombreTabla1, char *nombreTabla2, char *nombreTabla3);
// Crea una tabla la cual es el resultado de hacer el join entre otras 2 tablas

TipoRet equalTables(Base bd, char *nombreTabla1, char *nombreTabla2, bool &iguales);
// Se fija si dos tablas son iguales

TipoRet printTables(Base bd);
// Imprime en pantalla todas las tablas

TipoRet printMetadata(Base bd, char *nombreTabla);
// Imprime en pantalla todas las columnas de una tabla

TipoRet recent(Base bd);
// Imprime el nombre de las tablas recientemente modificadas

#endif
