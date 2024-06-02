#include "db.h"
#include <iostream>

using namespace std;

MYSQL* conectar;
int q_estado;

void conectarDB() {
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "Guatemala502", "super", 3306, NULL, 0);
    if (!conectar) {
        cout << "Conexion Fallida: " << mysql_error(conectar) << endl;
    }
}

void desconectarDB() {
    if (conectar) {
        mysql_close(conectar);
    }
}

