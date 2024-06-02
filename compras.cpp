#include "compras.h"
#include "db.h"
#include <iostream>
#include <string>

using namespace std;

void insertarCompra() {
    conectarDB();
    if (conectar) {
        int no_orden_compra, idProveedore;
        string fecha_orden, fechaingreso;
        cout << "Ingrese No. de Orden de Compra: ";
        cin >> no_orden_compra;
        cout << "Ingrese ID del Proveedor: ";
        cin >> idProveedore;
        cout << "Ingrese Fecha de Orden (YYYY-MM-DD): ";
        cin >> fecha_orden;
        cout << "Ingrese Fecha de Ingreso (YYYY-MM-DD HH:MM:SS): ";
        cin >> fechaingreso;

        string insert = "INSERT INTO compras(no_orden_compra, idProveedore, fecha_orden, fechaingreso) VALUES(" + to_string(no_orden_compra) + "," + to_string(idProveedore) + ",'" + fecha_orden + "','" + fechaingreso + "')";
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Ingreso Exitoso de Compra..." << endl;
        }
        else {
            cout << "Error al Ingresar Compra: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

void leerCompras() {
    conectarDB();
    if (conectar) {
        string consulta = "SELECT idCompra, no_orden_compra, idProveedore, fecha_orden, fechaingreso FROM compras";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            MYSQL_RES* resultado = mysql_store_result(conectar);
            if (resultado) {
                int num_filas = mysql_num_rows(resultado);
                if (num_filas > 0) {
                    cout << "ID\tNo. Orden\tID Proveedor\tFecha Orden\tFecha Ingreso" << endl;
                    while (MYSQL_ROW fila = mysql_fetch_row(resultado)) {
                        cout << fila[0] << "\t" << fila[1] << "\t" << fila[2] << "\t" << fila[3] << "\t" << fila[4] << endl;
                    }
                }
                else {
                    cout << "No se encontraron compras." << endl;
                }
                mysql_free_result(resultado);
            }
        }
        else {
            cout << "Error al realizar la consulta: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

void actualizarCompra(int idCompra) {
    conectarDB();
    if (conectar) {
        int no_orden_compra, idProveedore;
        string fecha_orden, fechaingreso;
        cout << "Ingrese el nuevo No. de Orden de Compra: ";
        cin >> no_orden_compra;
        cout << "Ingrese el nuevo ID del Proveedor: ";
        cin >> idProveedore;
        cout << "Ingrese la nueva Fecha de Orden (YYYY-MM-DD): ";
        cin >> fecha_orden;
        cout << "Ingrese la nueva Fecha de Ingreso (YYYY-MM-DD HH:MM:SS): ";
        cin >> fechaingreso;

        string update = "UPDATE compras SET no_orden_compra=" + to_string(no_orden_compra) + ", idProveedore=" + to_string(idProveedore) + ", fecha_orden='" + fecha_orden + "', fechaingreso='" + fechaingreso + "' WHERE idCompra=" + to_string(idCompra);
        const char* u = update.c_str();
        q_estado = mysql_query(conectar, u);
        if (!q_estado) {
            cout << "Actualizacion Exitosa de Compra..." << endl;
        }
        else {
            cout << "Error al Actualizar Compra: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

void eliminarCompra(int idCompra) {
    conectarDB();
    if (conectar) {
        string eliminarCompra = "DELETE FROM compras WHERE idCompra=" + to_string(idCompra);
        const char* ec = eliminarCompra.c_str();
        q_estado = mysql_query(conectar, ec);
        if (!q_estado) {
            cout << "Compra eliminada correctamente." << endl;
        }
        else {
            cout << "Error al eliminar compra: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}
