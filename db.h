#ifndef DB_H
#define DB_H

#include <mysql.h>

// Declaraciones para la conexi�n a la base de datos
extern MYSQL* conectar;
extern int q_estado;

void conectarDB();
void desconectarDB();

#endif
