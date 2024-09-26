/******************************************************************************\
 * Curso de Programación 1. Tema 14 (Ficheros de texto)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 27 de noviembre de 2023
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros de texto de ventas
 * Nota: El programa completo está contenido en este fichero, por lo que puede 
 *       compilarse y ejecutarse con la extensión Code Runner de Visual Studio 
 *       Code.
 *       También puede compilarse desde la terminal través de la orden
 *           g++ -Wall -Wextra problemas-ventas.cpp -o problemas-ventas
 *       y ejecutarse en Windows a través de la orden
 *           .\problemas-ventas.exe
 *       o en Linux y macOS
 *           ./problemas-ventas
\******************************************************************************/

#include <iostream>
#include <fstream>
#include "venta.hpp"
using namespace std;

/*
 * Cantidad máxima ESTIMADA de clientes distintos en los ficheros de ventas
 */
const unsigned MAX_CLIENTES = 5000;

/*
 * Pre:  El flujo «f» está asociado con un fichero de texto que cumple con la
 *       sintaxis de los ficheros de ventas establecida en el enunciado y en
 *       disposición de leer desde el principio de una línea.
 * Post: Intenta leer la línea mencionada en la precondición y, si no se terminan los
 *       datos del fichero en dicho intento, almacena en los campos del parámetro
 *       «venta» el código del producto vendido leído del fichero, el código del 
 *       cliente a quien se ha vendido, la cantidad de producto y el precio unitario
 *       que se ha vendido. Devuelve «true» si los datos del fichero no se han
 *       terminado y, por lo tanto, se han podido leer los datos mencionados.
 *       Devuelve «false» en caso contrario.
 */
bool leerSiguienteVenta(istream &f, Venta &venta) {
    f >> venta.producto >> venta.cliente >> venta.cantidad 
      >> venta.precioUnitario;
    f.ignore();        // Extrae e ignora el carácter '\n' de final de línea.
    return !f.eof();
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de la regla <fichero-ventas>
 *       establecida en el enunciado.
 * Post: Devuelve la cantidad total a facturar al cliente cuyo código es igual a 
 *       «clienteFactura» por las ventas que le corresponden registradas en 
 *       el fichero de ventas de nombre «nombreFichero». Si el fichero
 *		 «nombreFichero» no se puede abrir, devuelve -1.
 */
double totalFactura(const string nombreFichero, const unsigned clienteFactura) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero);
    if (f.is_open()) {
        // Importe inicial de la factura
        double total = 0.0;

        Venta venta;
        while (leerSiguienteVenta(f, venta)) {
            // Si la última venta leída corresponde a «cliente», se añade su
            // importe al total
            if (venta.cliente == clienteFactura) {
                total = total + venta.precioUnitario * venta.cantidad;
            }
        }
        // Cierre del fichero y devolución del total calculado
        f.close();
        return total;
    } else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"." << endl;
        return -1;
    }
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFicheroOriginal»
 *       accesible para su lectura y que cumple con la sintaxis de la regla
 *       <fichero-ventas> y es posible crear o reescribir el 
 *       fichero de nombre «nombreFicheroFinal» para su escritura.
 * Post: Copia en el fichero de nombre «nombreFicheroFinal» las ventas almacenadas en 
 *       el fichero de nombre «nombreFicheroOriginal» que no son erróneas y solo 
 *       esas. Una venta es considerada errónea cuando la cantidad o el precio
 *       unitario son NO son positivos.
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
            Venta venta;
            while (leerSiguienteVenta(fOriginal, venta)) {
                // Si la venta no es errónea, se añade al fichero final
                if (venta.cantidad > 0 && venta.precioUnitario > 0) {
                    fFinal << venta.producto << ' ' << venta.cliente << ' ' 
                           << venta.cantidad << ' ' << venta.precioUnitario
                           << endl;
                }
            }
            // Cierre de los ficheros
            fFinal.close();
        } else {
            cerr << "No se ha podido escribir en el fichero \""
                 << nombreFicheroFinal << "\"." << endl;
        }
        fOriginal.close();
    } else {
        cerr << "No se ha podido leer del fichero \"" << nombreFicheroOriginal
             << "\"." << endl;
    }
}


/*
 * Pre:  numClientes <= MAX_CLIENTES
 * Post: Devuelve «true» si y solo si «cliente» está en las primeras
 *       «numClientes» componentes de «vectorClientes».
 */
bool esta(const unsigned cliente, const unsigned vectorClientes[], 
          const unsigned numClientes) {
    // Esquema de búsqueda no exhaustiva sin garantía de éxito
    bool encontrado = false;
    unsigned i = 0;
    while (!encontrado && i < numClientes) {
        encontrado = (vectorClientes[i] == cliente);
        i++;
    }
    // encontrado || i >= numClientes

    return encontrado;
}


/*
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de la regla <fichero-ventas>.
 * Post: Devuelve el número de clientes diferentes cuyas ventas están
 *       registradas en el fichero de ventas de nombre «nombreFichero». Si el fichero
 *		 no se puede abrir, devuelve -1.
 */
int numClientesDistintos(const string nombreFichero) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f(nombreFichero);
    if (f.is_open()) {
        // Número de clientes distintos identificados hasta el momento
        unsigned numClientes = 0;

        /*
         * Declaración de un vector de códigos de clientes distintos
         * encontrados en el fichero. Los códigos de clientes distintos
         * encontrados en el fichero en un determinado momento estarán
         * en las «numClientes» primeras componentes del vector.
         */
        unsigned vectorClientes[MAX_CLIENTES];

        Venta venta;
        while (leerSiguienteVenta(f, venta)) {
            // Si el cliente de la última venta leída no está en el vector,
            // se añade al vector.
            if (numClientes < MAX_CLIENTES 
                    && !esta(venta.cliente, vectorClientes, numClientes)) {
                vectorClientes[numClientes] = venta.cliente;
                numClientes++;
            }
        }
        // Cierre del fichero y devolución del número de clientes
        f.close();
        return numClientes;
    } else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"." << endl;
        return -1;
    }
}


/* 
 * Pre:  Existe un fichero de ventas con el nombre «nombreFichero» accesible 
 *       para su lectura y que cumple con la sintaxis de la regla <fichero-ventas> y
 *       el número de ventas almacenados en el mismo es 
 *       menor o igual a la dimensión del vector «ventas».
 * Post: Si el fichero «nombreFichero» se ha podido abrir, asigna a «nVentas» el
 *		 número de ventas del fichero, almacena las primeras «nVentas» componentes del
 *       vector «ventas» la información de las ventas almacenadas en el fichero y
 *       asigna a «lecturaOk» el valor «true». En caso contrario, asigna a 
 *       «lecturaOk» el valor «false».
 */
void leerVentas(const string nombreFichero, 
                Venta ventas[], unsigned &nVentas, bool &lecturaOk) {
    // Creación de un objeto «ifstream» para leer el fichero
    ifstream f;
    f.open(nombreFichero);
    if (f.is_open()) {
        nVentas = 0;

        while (leerSiguienteVenta(f, ventas[nVentas])) {
            nVentas++;
        }
        // Cierre del fichero
        f.close();
        lecturaOk = true;
    } else {
        cerr << "No se ha podido leer del fichero \"" << nombreFichero
             << "\"." << endl;
        lecturaOk = false;
    }
}


/* Pre:  ---
 * Post: Creado un fichero de nombre «nombreFichero» en el que ha almacenado la
 *       información de las «n» primeras componentes del vector «ventas» siguiendo la 
 *       sintaxis de los ficheros de ventas establecida en el enunciado. Si el
 *       fichero se ha podido crear sin problemas, ha asignado a «escrituraOk» el
 *       valor «true». En caso contrario, ha asignado a «escrituraOk» el valor
 *       «false».
 */
void guardarVentas(const string nombreFichero, 
                   const Venta ventas[], const unsigned n, bool &escrituraOk) {
    // Creación de un objeto «ofstream» para escribir el fichero
    ofstream f;
    f.open(nombreFichero);
    if (f.is_open()) {
        for (unsigned i = 0; i < n; i++) {
            f << ventas[i].producto << ' ' << ventas[i].cliente << ' ' 
              << ventas[i].cantidad << ' ' << ventas[i].precioUnitario << endl;
        }
        f.close();
        escrituraOk = true;
    } else {
        cerr << "No se ha podido escribir en el fichero \"" << nombreFichero
             << "\"." << endl;
        escrituraOk = false;
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
