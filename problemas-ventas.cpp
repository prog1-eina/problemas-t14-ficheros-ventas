/******************************************************************************\
 * Curso de Programación 1. Tema 15 (Ficheros binarios)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 17 de diciembre de 2019
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros binarios
\******************************************************************************/

#include <iostream>
#include <fstream>
#include "venta.h"
using namespace std;

/*
 * Cantidad máxima ESTIMADA de clientes distintos en los ficheros de ventas
 */
const int MAX_CLIENTES = 5000;

/*
 * Pre:  Existe un fichero binario de ventas con el nombre «nombreFichero»
 *       accesible para su lectura.
 * Post: Ha devuelto la cantidad total a facturar al cliente cuyo código es 
 *       igual a «clienteFactura» por las ventas que le corresponden registradas 
 *       en el fichero de ventas de nombre «nombreFichero».
 */
double totalFactura(const char nombreFichero[], const int clienteFactura) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero, ios::binary);
    if (f.is_open()) {
        // Importe inicial de la factura
        double total = 0.0;

        // Intento de lectura de la primera venta
        Venta venta;
        f.read(reinterpret_cast<char*>(&venta), sizeof(venta));
        while (!f.eof()) {
            // Si la última venta leída corresponde a «cliente», se añade su
            // importe al total
            if (venta.cliente == clienteFactura) {
                total = total + venta.precioUnitario * venta.cantidad;
            }
            // Intento de lectura de la siguiente venta
            f.read(reinterpret_cast<char*>(&venta), sizeof(venta));
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
 * Pre:  Existe un fichero binario de ventas con el nombre
 *       «nombreFicheroOriginal» accesible para su lectura y es posible crear
 *       o reescribir el fichero de nombre «nombreFicheroFinal» para su
 *       escritura.
 * Post: Ha copiado en el fichero de nombre «nombreFicheroFinal» las
 *       ventas almacenadas en el fichero de nombre «nombreFicheroOriginal»
 *       que no son erróneas y solo esas. Una venta es considerada errónea
 *       cuando la cantidad o el precio unitario o ambos son negativos.
 */
void eliminarErroneos(const char nombreFicheroOriginal[],
                      const char nombreFicheroFinal[]) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream fOriginal;
    fOriginal.open(nombreFicheroOriginal, ios::binary);
    if (fOriginal.is_open()) {
        // Creación de un objeto «ofstream» para escribir el fichero final
        ofstream fFinal;
        fFinal.open(nombreFicheroFinal, ios::binary);
        if (fFinal.is_open()) {
            // Intento de lectura de la primera venta
            Venta venta;
            fOriginal.read(reinterpret_cast<char*>(&venta), sizeof(venta));
            while (!fOriginal.eof()) {
                // Si la venta no es errónea, se añade al fichero final
                if (venta.cantidad >= 0 && venta.precioUnitario >= 0) {
                    fFinal.write(reinterpret_cast<const char*>(&venta),
                                 sizeof(venta));
                }
				fOriginal.read(reinterpret_cast<char*>(&venta), sizeof(venta));
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
 * Pre:  0 <= numClientes y numClientes < MAX_CLIENTES
 * Post: Ha devuelto «true» si y solo si «cliente» está en las primeras
 *       «numClientes» componentes de «vectorClientes».
 */
bool esta(const int cliente, const int vectorClientes[], const int numClientes) {
    // Esquema de búsqueda no exhaustiva sin garantía de éxito
    bool encontrado = false;
    int i = 0;
    while (!encontrado && i < numClientes) {
        encontrado = (vectorClientes[i] == cliente);
        i++;
    }
    // encontrado || i >= numClientes

    return encontrado;
}


/*
 * Pre:  Existe un fichero binario de ventas con el nombre
 *       «nombreFichero» accesible para su lectura.
 * Post: Ha devuelto el número de clientes diferentes cuyas ventas están
 *       registradas en el fichero de ventas de nombre «nombreFichero».
 */
int numClientesDistintos(const char nombreFichero[]) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero, ios::binary);
    if (f.is_open()) {
        // Número de clientes distintos identificados hasta el momento
        int numClientes = 0;

        /*
         * Declaración de un vector de códigos de clientes distintos
         * encontrados en el fichero. Los códigos de clientes distintos
         * encontrados en el fichero en un determinado momento estarán
         * en las «numClientes» primeras componentes del vector.
         */
        int vectorClientes[MAX_CLIENTES];

        // Intento de lectura de la primera venta
        Venta venta;
        f.read(reinterpret_cast<char*>(&venta), sizeof(venta));
        while (!f.eof()) {
            // Si el cliente de la última venta leída no está en el vector,
            // se añade al vector.
            if (!esta(venta.cliente, vectorClientes, numClientes)) {
                vectorClientes[numClientes] = venta.cliente;
                numClientes++;
            }
            // Intento de lectura de la siguiente venta
            f.read(reinterpret_cast<char*>(&venta), sizeof(venta));
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


/* Pre:  Existe un fichero binario de ventas de nombre «nombreFichero» accesible
 *       para su lectura y el número de ventas almacenados en el mismo es menor
 *       o igual a la dimensión del vector «ventas».
 * Post: Ha asignado a «nVentas» el número de ventas del fichero y ha almacenado
 *       las primeras «nVentas» componentes del vector «ventas» la información
 *       de las ventas almacenadas en el fichero.
 */
void leerVentas(const char nombreFichero[], Venta ventas[], int& nVentas) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f;
    f.open(nombreFichero, ios::binary);
    if (f.is_open()) {
        nVentas = 0;

        // Intento de lectura de la primera venta
        f.read(reinterpret_cast<char*>(&ventas[nVentas]), sizeof(Venta));
        while (!f.eof()) {
            nVentas++;
            // Intento de lectura de la siguiente venta
            f.read(reinterpret_cast<char*>(&ventas[nVentas]), sizeof(Venta));
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

/* Pre:  n ≥ 0
 * Post: Ha creado un fichero de nombre «nombreFichero» en el que ha almacenado
 *       la información codificada en binario de las «n» primeras componentes
 *       del vector «ventas».
 */
void guardarVentas(const char nombreFichero[], const Venta t[], const int n) {
    // Creación de un objeto «ofstream» para escribir el fichero
    ofstream f;
    f.open(nombreFichero, ios::binary);
    if (f.is_open()) {
        f.write(reinterpret_cast<const char*>(t), n * sizeof(Venta));
        f.close();
    }
    else {
        cerr << "No se ha podido escribir en el fichero \"" << nombreFichero
             << "\"" << endl;
    }
}

/* CÓDIGO PARA LAS PRUEBAS, QUE REALIZA LA FUNCIÓN MAIN */

const char NOMBRE_FICHERO_VENTAS[] = "ventas.dat";
const int NUM_VENTAS_EJEMPLO = 4;
const Venta VENTAS_EJEMPLO[NUM_VENTAS_EJEMPLO] = {
    {117, 120552, 120, 3.15},
    {122, 130922, 65, 6.40},
    {105, 120552, 100, 3.16},
    {154, 137054, 75, 0.98}
};


/*
 * Programa de pruebas que crea un fichero binario de ventas (a partir de los
 * datos del vector «VENTAS_EJEMPLO») y prueba las funciones «totalFactura» y 
 * «numClientesDistintos». Debe escribir «true» en la pantalla un total de 5
 * veces.
 */
int main() {
    guardarVentas(NOMBRE_FICHERO_VENTAS, VENTAS_EJEMPLO, NUM_VENTAS_EJEMPLO);
    cout << boolalpha;
    cout << (694.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 120552)) << endl;
    cout << (416.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 130922)) << endl;
    cout << (73.5 == totalFactura(NOMBRE_FICHERO_VENTAS, 137054)) << endl;
    cout << (0.0 == totalFactura(NOMBRE_FICHERO_VENTAS, 123456)) << endl;
    cout << (3 == numClientesDistintos(NOMBRE_FICHERO_VENTAS)) << endl;
    return 0;
}
