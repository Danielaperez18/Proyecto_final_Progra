#include "ventas.h"
#include "db.h"
#include <iostream>
#include <string>

using namespace std;

void insertarVenta() {
    conectarDB();
    if (conectar) {
        int nofactura;
        string serie, fechafactura, idCliente, idEmpleado, fechaingreso;
        cout << "Ingrese No. de Factura: ";
        cin >> nofactura;
        cout << "Ingrese Serie: ";
        cin >> serie;
        cout << "Ingrese Fecha de Factura (YYYY-MM-DD): ";
        cin >> fechafactura;
        cout << "Ingrese ID del Cliente: ";
        cin >> idCliente;
        cout << "Ingrese ID del Empleado: ";
        cin >> idEmpleado;
        cout << "Ingrese Fecha de Ingreso (YYYY-MM-DD): ";
        cin >> fechaingreso;

        string insert = "INSERT INTO ventas(nofactura, serie, fechafactura, idCliente, idEmpleado, fechaingreso) VALUES(" + to_string(nofactura) + ",'" + serie + "','" + fechafactura + "'," + idCliente + "," + idEmpleado + ",'" + fechaingreso + "')";
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "Ingreso Exitoso de Venta..." << endl;
        }
        else {
            cout << "Error al Ingresar Venta: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

void leerVentas() {
    conectarDB();
    if (conectar) {
        string consulta = "SELECT idVenta, nofactura, serie, fechafactura, idCliente, idEmpleado FROM ventas";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            MYSQL_RES* resultado = mysql_store_result(conectar);
            if (resultado) {
                int num_filas = mysql_num_rows(resultado);
                if (num_filas > 0) {
                    cout << "ID\tNo. Factura\tSerie\tFecha Factura\tID Cliente\tID Empleado" << endl;
                    while (MYSQL_ROW fila = mysql_fetch_row(resultado)) {
                        cout << fila[0] << "\t" << fila[1] << "\t\t" << fila[2] << "\t" << fila[3] << "\t" << fila[4] << "\t" << fila[5] << endl;
                    }
                }
                else {
                    cout << "No se encontraron ventas." << endl;
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

void actualizarVenta(int idVenta) {
    conectarDB();
    if (conectar) {
        int nofactura;
        string serie, fechafactura, idCliente, idEmpleado, fechaingreso;
        cout << "Ingrese el nuevo No. de Factura: ";
        cin >> nofactura;
        cout << "Ingrese la nueva Serie: ";
        cin >> serie;
        cout << "Ingrese la nueva Fecha de Factura (YYYY-MM-DD): ";
        cin >> fechafactura;
        cout << "Ingrese el nuevo ID del Cliente: ";
        cin >> idCliente;
        cout << "Ingrese el nuevo ID del Empleado: ";
        cin >> idEmpleado;
        cout << "Ingrese la nueva Fecha de Ingreso (YYYY-MM-DD): ";
        cin >> fechaingreso;

        string update = "UPDATE ventas SET nofactura=" + to_string(nofactura) + ", serie='" + serie + "', fechafactura='" + fechafactura + "', idCliente=" + idCliente + ", idEmpleado=" + idEmpleado + ", fechaingreso='" + fechaingreso + "' WHERE idVenta=" + to_string(idVenta);
        const char* u = update.c_str();
        q_estado = mysql_query(conectar, u);
        if (!q_estado) {
            cout << "Actualizacion Exitosa de Venta..." << endl;
        }
        else {
            cout << "Error al Actualizar Venta: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

bool esNITValido(const string& nit) {
    if (nit.length() != 8)
        return false;

    for (char c : nit) {
        if (!isdigit(c))
            return false;
    }

    if (nit == "CF" || nit == "cf")
        return true;

    return true;
}

void validarNIT() {
    conectarDB();
    if (conectar) {
        string nit;
        bool formatoCorrecto = false;
        do {
            cout << "Ingrese el NIT del cliente: ";
            cin >> nit;

            if (!esNITValido(nit)) {
                cout << "El formato del NIT es incorrecto. Intentelo de nuevo." << endl;
            }
            else {
                formatoCorrecto = true;
            }
        } while (!formatoCorrecto);

        string query = "SELECT nombres FROM Clientes WHERE NIT = '" + nit + "'";
        if (mysql_query(conectar, query.c_str())) {
            cerr << "Error al ejecutar la consulta: " << mysql_error(conectar) << endl;
            desconectarDB();
            return;
        }

        MYSQL_RES* result = mysql_store_result(conectar);
        if (result == NULL) {
            cerr << "Error al obtener el resultado de la consulta: " << mysql_error(conectar) << endl;
            desconectarDB();
            return;
        }

        if (mysql_num_rows(result) == 0) {
            cout << "El cliente con NIT '" << nit << "' no existe en la base de datos." << endl;

            char respuesta;
            cout << "¿Desea agregar este cliente? (s/n): ";
            cin >> respuesta;

            if (respuesta == 's' || respuesta == 'S') {
                string nombres, apellidos, correo, fechaIngreso;
                int genero;
                int telefono;
                bool datosCorrectos = false;
                do {
                    cout << "Ingrese los nombres del cliente: ";
                    cin.ignore();
                    getline(cin, nombres);
                    cout << "Ingrese los apellidos del cliente: ";
                    getline(cin, apellidos);
                    cout << "Ingrese el genero (0 para Hombre, 1 para Mujer): ";
                    cin >> genero;
                    cout << "Ingrese el teléfono: ";
                    cin >> telefono;
                    cout << "Ingrese el correo electrónico: ";
                    cin >> correo;
                    cout << "Ingrese la fecha de ingreso (YYYY-MM-DD): ";
                    cin >> fechaIngreso;

                    if ((genero != 0 && genero != 1) || telefono < 0 || correo.empty() || fechaIngreso.empty()) {
                        cout << "Algunos de los datos son incorrectos. Intentelo de nuevo." << endl;
                    }
                    else {
                        datosCorrectos = true;
                    }
                } while (!datosCorrectos);

                string insertQuery = "INSERT INTO Clientes (NIT, nombres, apellidos, genero, telefono, correo_electronico, fechaingreso) VALUES ('" + nit + "', '" + nombres + "', '" + apellidos + "', " + to_string(genero) + ", " + to_string(telefono) + ", '" + correo + "', '" + fechaIngreso + "')";
                if (mysql_query(conectar, insertQuery.c_str())) {
                    cerr << "Error al insertar el cliente: " << mysql_error(conectar) << endl;
                    mysql_free_result(result);
                    desconectarDB();
                    return;
                }
                cout << "Cliente agregado correctamente." << endl;
            }
            else {
                cout << "No se agregará el cliente." << endl;
            }

            mysql_free_result(result);
            desconectarDB();
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        cout << "Nombre completo del cliente: " << row[0] << endl;

        mysql_free_result(result);
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}

void eliminarVenta(int idVenta) {
    conectarDB();
    if (conectar) {
        string eliminarDetalles = "DELETE FROM ventas_detalle WHERE idVenta=" + to_string(idVenta);
        const char* ed = eliminarDetalles.c_str();
        q_estado = mysql_query(conectar, ed);
        if (q_estado) {
            cout << "Error al eliminar detalles de venta: " << mysql_error(conectar) << endl;
            desconectarDB();
            return;
        }

        string eliminarVenta = "DELETE FROM ventas WHERE idVenta=" + to_string(idVenta);
        const char* ev = eliminarVenta.c_str();
        q_estado = mysql_query(conectar, ev);
        if (!q_estado) {
            cout << "Venta y detalles eliminados correctamente." << endl;
        }
        else {
            cout << "Error al eliminar venta: " << mysql_error(conectar) << endl;
        }
    }
    else {
        cout << "Conexion Fallida" << endl;
    }
    desconectarDB();
}
