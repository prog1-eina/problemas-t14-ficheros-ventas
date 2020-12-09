/******************************************************************************\
 * Curso de Programación 1. Tema 14 (Ficheros de texto)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 9 de diciembre de 2020
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros de texto de ventas:
 *          Fichero de especificación del módulo «venta»
\******************************************************************************/

 #pragma once

/*
 * Los registros de tipo «Venta» gestionan la información asociada a ventas como
 * las que se almacenan en los ficheros binarios especificados en el
 * enunciado.
 */
struct Venta {
    int producto;            // Código del producto vendido
    int cliente;             // Código del cliente a quien se ha vendido
    int cantidad;            // Cantidad de producto que se ha vendido
    double precioUnitario;   // Precio unitario al que se ha vendido el producto
};
