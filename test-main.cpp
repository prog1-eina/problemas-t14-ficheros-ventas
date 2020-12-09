/********************************************************************************\
 * Curso de Programación 1. Tema 15 (Ficheros binarios)
 * Autores: Miguel Ángel Latre
 * Última revisión: 17 de diciembre de 2019
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros binarios
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\********************************************************************************/
#include <iostream>
#include "venta.h"
#include "problemas-ventas.h"
using namespace std;

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
