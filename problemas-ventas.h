/********************************************************************************\
 * Curso de Programación 1. Tema 15 (Ficheros binarios)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 12 de diciembre de 2018
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros binarios
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\********************************************************************************/

#include "venta.h"

/*
 * Pre:  Existe un fichero binario de ventas con el nombre «nombreFichero»
 *       accesible para su lectura.
 * Post: Ha devuelto la cantidad total a facturar al cliente cuyo código es igual
 *       a «clienteFactura» por las ventas que le corresponden registradas en
 *       el fichero de ventas de nombre «nombreFichero».
 */
double totalFactura(const char nombreFichero[], const int clienteFactura);


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
                      const char nombreFicheroFinal[]);


/*
 * Pre:  Existe un fichero binario de ventas con el nombre
 *       «nombreFichero» accesible para su lectura.
 * Post: Ha devuelto el número de clientes diferentes cuyas ventas están
 *       registradas en el fichero de ventas de nombre «nombreFichero».
 */
int numClientesDistintos(const char nombreFichero[]);


/* Pre:  Existe un fichero binario de ventas de nombre «nombreFichero» accesible
 *       para su lectura y el número de ventas almacenados en el mismo es menor o
 *       igual a la dimensión del vector «ventas».
 * Post: Ha asignado a «nVentas» el número de ventas del fichero y ha almacenado
 *       las primeras «nVentas» componentes del vector «ventas» la información de
 *       las ventas almacenadas en el fichero.
 */
void leerVentas(const char nombreFichero[], Venta ventas[], int& nVentas);


/* Pre:  n ≥ 0
 * Post: Ha creado un fichero de nombre «nombreFichero» en el que ha almacenado la
 *       información codificada en binario de las «n» primeras componentes del
 *       vector «ventas».
 */
void guardarVentas(const char nombreFichero[], const Venta t[], const int n);
