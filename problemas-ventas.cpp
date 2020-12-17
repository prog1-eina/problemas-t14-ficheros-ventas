/******************************************************************************\
 * Curso de Programación 1. Tema 14 (Ficheros de texto)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 16 de diciembre de 2020
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros de texto de ventas
\******************************************************************************/

#include <iostream>
#include <fstream>
#include "venta.hpp"
using namespace std;

/*
 * Cantidad máxima ESTIMADA de clientes distintos en los ficheros de ventas
 */
const unsigned int MAX_CLIENTES = 5000;

/*
 * Pre:  El flujo «f» está asociado con un fichero de texto que cumple con la
 *       sintaxis de los ficheros de ventas establecida en el enunciado y en
 *       disposición de leer desde el principio de una línea.
 * Post: Ha intentado leer la línea mencionada en la precondición y, si no se
 *       han terminado los datos del fichero en dicho intento, ha almacenado en
 *       los campos del parámetro «venta» el código del producto vendido leído 
 *       del fichero, el código del cliente a quien se ha vendido, la cantidad 
 *       de producto y el precio unitario que se ha vendido.
 */
void leerSiguienteVenta(istream& f, Venta& venta) {
    f >> venta.producto >> venta.cliente >> venta.cantidad 
      >> venta.precioUnitario;
    f.get();        // Extrae e ignora el carácter '\n' de final de línea.
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de los ficheros de ventas
 *       establecida en el enunciado.
 * Post: Ha devuelto la cantidad total a facturar al cliente cuyo código es 
 *       igual a «clienteFactura» por las ventas que le corresponden registradas 
 *       en el fichero de ventas de nombre «nombreFichero».
 */
double totalFactura(const string nombreFichero, const int clienteFactura) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero);
    if (f.is_open()) {
        // Importe inicial de la factura
        double total = 0.0;

        // Intento de lectura de la primera venta
        Venta venta;
        leerSiguienteVenta(f, venta);
        while (!f.eof()) {
            // Si la última venta leída corresponde a «cliente», se añade su
            // importe al total
            if (venta.cliente == clienteFactura) {
                total = total + venta.precioUnitario * venta.cantidad;
            }
            // Intento de lectura de la siguiente venta
            leerSiguienteVenta(f, venta);
        }
        // Cierre del fichero y devolución del total calculado
        f.close();
        return total;
    }
    else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"." << endl;
        return -1;
    }
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFicheroOriginal»
 *       accesible para su lectura y que cumple con la sintaxis de los ficheros 
 *       de ventas establecida en el enunciado y es posible crear o reescribir
 *       el fichero de nombre «nombreFicheroFinal» para su escritura.
 * Post: Ha copiado en el fichero de nombre «nombreFicheroFinal» las ventas 
 *       almacenadas en el fichero de nombre «nombreFicheroOriginal» que no son 
 *       erróneas y solo esas. Una venta es considerada errónea cuando la
 *       cantidad o el precio unitario o ambos son nulos o negativos.
 */
void eliminarErroneos(const string nombreFicheroOriginal,
                      const string nombreFicheroFinal) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream fOriginal;
    fOriginal.open(nombreFicheroOriginal);
    if (fOriginal.is_open()) {
        // Creación de un objeto «ofstream» para escribir el fichero final
        ofstream fFinal;
        fFinal.open(nombreFicheroFinal);
        if (fFinal.is_open()) {
            // Intento de lectura de la primera venta
            Venta venta;
            leerSiguienteVenta(fOriginal, venta);
            while (!fOriginal.eof()) {
                // Si la venta no es errónea, se añade al fichero final
                if (venta.cantidad > 0 && venta.precioUnitario > 0) {
                    fFinal << venta.producto << ' ' << venta.cliente << ' ' 
                           << venta.cantidad << ' ' << venta.precioUnitario
                           << endl;
                }
                leerSiguienteVenta(fOriginal, venta);
            }
            // Cierre de los ficheros
            fFinal.close();
        }
        else {
            cerr << "No se ha podido escribir en el fichero \""
                 << nombreFicheroFinal << "\"." << endl;
        }
        fOriginal.close();
    }
    else {
        cerr << "No se ha podido leer del fichero \"" << nombreFicheroOriginal
             << "\"." << endl;
    }
}


/*
 * Pre:  numClientes < MAX_CLIENTES
 * Post: Ha devuelto «true» si y solo si «cliente» está en las primeras
 *       «numClientes» componentes de «vectorClientes».
 */
bool esta(const unsigned int cliente, const unsigned int vectorClientes[], 
          const unsigned int numClientes) {
    // Esquema de búsqueda no exhaustiva sin garantía de éxito
    bool encontrado = false;
    unsigned int i = 0;
    while (!encontrado && i < numClientes) {
        encontrado = (vectorClientes[i] == cliente);
        i++;
    }
    // encontrado || i >= numClientes

    return encontrado;
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de los ficheros de ventas
 *       establecida en el enunciado.
 * Post: Ha devuelto el número de clientes diferentes cuyas ventas están
 *       registradas en el fichero de ventas de nombre «nombreFichero».
 */
unsigned int numClientesDistintos(const string nombreFichero) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero);
    if (f.is_open()) {
        // Número de clientes distintos identificados hasta el momento
        unsigned int numClientes = 0;

        /*
         * Declaración de un vector de códigos de clientes distintos
         * encontrados en el fichero. Los códigos de clientes distintos
         * encontrados en el fichero en un determinado momento estarán
         * en las «numClientes» primeras componentes del vector.
         */
        unsigned int vectorClientes[MAX_CLIENTES];

        // Intento de lectura de la primera venta
        Venta venta;
        leerSiguienteVenta(f, venta);
        while (!f.eof()) {
            // Si el cliente de la última venta leída no está en el vector,
            // se añade al vector.
            if (!esta(venta.cliente, vectorClientes, numClientes)) {
                vectorClientes[numClientes] = venta.cliente;
                numClientes++;
            }
            // Intento de lectura de la siguiente venta
            leerSiguienteVenta(f, venta);
        }
        // Cierre del fichero y devolución del número de clientes
        f.close();
        return numClientes;
    }
    else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"." << endl;
        return -1;
    }
}


/* 
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de los ficheros de ventas
 *       establecida en el enunciado y el número de ventas almacenados en el 
 *       mismo es menor o igual a la dimensión del vector «ventas».
 * Post: Ha asignado a «nVentas» el número de ventas del fichero y ha almacenado
 *       las primeras «nVentas» componentes del vector «ventas» la información
 *       de las ventas almacenadas en el fichero.
 */
void leerVentas(const string nombreFichero, 
                Venta ventas[], unsigned int& nVentas) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f;
    f.open(nombreFichero);
    if (f.is_open()) {
        nVentas = 0;

        // Intento de lectura de la primera venta
        leerSiguienteVenta(f, ventas[nVentas]);
        while (!f.eof()) {
            nVentas++;
            // Intento de lectura de la siguiente venta
            leerSiguienteVenta(f, ventas[nVentas]);
        }
        // Cierre del fichero
        f.close();
    }
    else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"" << endl;
        nVentas = -1;
    }
}

/* Pre:  ---
 * Post: Ha creado un fichero de nombre «nombreFichero» en el que ha almacenado
 *       la información de las «n» primeras componentes del vector «ventas»
 *       siguiendo la sintaxis de los ficheros de ventas establecida en el
 *       enunciado.
 */
void guardarVentas(const string nombreFichero, 
                   const Venta ventas[], const unsigned int n) {
    // Creación de un objeto «ofstream» para escribir el fichero
    ofstream f;
    f.open(nombreFichero);
    if (f.is_open()) {
        for (unsigned int i = 0; i < n; i++) {
            f << ventas[i].producto << ' ' << ventas[i].cliente << ' ' 
              << ventas[i].cantidad << ' ' << ventas[i].precioUnitario << endl;
        }
        f.close();
    }
    else {
        cerr << "No se ha podido escribir en el fichero \"" << nombreFichero
             << "\"" << endl;
    }
}

/* CÓDIGO PARA LAS PRUEBAS, QUE REALIZA LA FUNCIÓN MAIN */

const string NOMBRE_FICHERO_VENTAS = "ventas.txt";


/*
 * Programa que prueba las funciones «totalFactura» y 
 * «numClientesDistintos». Debe escribir «true» en la pantalla un total de 5
 * veces.
 */
int main() {
    cout << boolalpha;
    cout << (694.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 120552)) << endl;
    cout << (416.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 130922)) << endl;
    cout << (73.5 == totalFactura(NOMBRE_FICHERO_VENTAS, 137054)) << endl;
    cout << (0.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 123456)) << endl;
    cout << (3 == numClientesDistintos(NOMBRE_FICHERO_VENTAS)) << endl;
    return 0;
}
