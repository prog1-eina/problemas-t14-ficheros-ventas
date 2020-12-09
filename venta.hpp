/******************************************************************************\
 * Curso de Programación 1. Tema 15 (Ficheros binarios)
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 17 de diciembre de 2019
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas de ficheros binarios:
 *          Fichero de especificación del módulo «venta»
\******************************************************************************/

 #pragma once

/*
 * Los registros de tipo «Venta» gestionan la información asociada a ventas como
 * las que se almacenan en los ficheros binarios especificados en el
 * enunciado.
 */
struct Venta {
    unsigned int producto;           // Código del producto vendido
    unsigned int cliente;            // Código del cliente a quien se ha vendido
    unsigned int cantidad;           // Cantidad de producto que se ha vendido
    double precioUnitario;   // Precio unitario al que se ha vendido el producto
};
