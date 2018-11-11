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

TipoRet join(Base &b, char *nomTabla1, char *nomTabla2, char *nomTabla3);

TipoRet equalTables(Base b, char *nomTabla1, char *nomTabla2, bool &iguales);

TipoRet printTables(Base b);

TipoRet printMetadata(Base b, char *nombreTabla);

TipoRet recent(Base b);

#endif