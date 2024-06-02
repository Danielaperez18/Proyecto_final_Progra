#include "main.h"
#include <iostream>

using namespace std;

void menu() {
    int opcion;
    do {
        cout << "1. Insertar Venta" << endl;
        cout << "2. Leer Ventas" << endl;
        cout << "3. Actualizar Venta" << endl;
        cout << "4. Eliminar Venta" << endl;
        cout << "5. Insertar Compra" << endl;
        cout << "6. Leer Compras" << endl;
        cout << "7. Actualizar Compra" << endl;
        cout << "8. Eliminar Compra" << endl;
        cout << "9. Validar NIT del Cliente" << endl; // Nueva opción en el menú
        cout << "10. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            insertarVenta();
            break;
        case 2:
            leerVentas();
            break;
        case 3: {
            int idVenta;
            cout << "Ingrese el ID de la Venta a actualizar: ";
            cin >> idVenta;
            actualizarVenta(idVenta);
            break;
        }
        case 4: {
            int idVenta;
            cout << "Ingrese el ID de la Venta a eliminar: ";
            cin >> idVenta;
            eliminarVenta(idVenta);
            break;
        }
        case 5:
            insertarCompra();
            break;
        case 6:
            leerCompras();
            break;
        case 7: {
            int idCompra;
            cout << "Ingrese el ID de la Compra a actualizar: ";
            cin >> idCompra;
            actualizarCompra(idCompra);
            break;
        }
        case 8: {
            int idCompra;
            cout << "Ingrese el ID de la Compra a eliminar: ";
            cin >> idCompra;
            eliminarCompra(idCompra);
            break;
        }
        case 9:
            validarNIT();
            break;
        case 10:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 10);
}

int main() {
    menu();
    return 0;
}
