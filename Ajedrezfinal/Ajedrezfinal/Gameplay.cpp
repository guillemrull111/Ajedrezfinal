#include <iostream>
#include "Const.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {

    int filaOrigen, colOrigen;
    int filaDestino, colDestino;
    bool turno = false;
    bool juegoAcabado = false;

    while (!juegoAcabado) {

        while (!turno) {

            std::cout << "Fila de la ficha que quieres mover: ";
            std::cin >> filaOrigen;

            std::cout << "Columna de la ficha que quieres mover: ";
            std::cin >> colOrigen;

            // Validar origen
            if (filaOrigen < 0 || filaOrigen >= FILA ||
                colOrigen < 0 || colOrigen >= COLUMNA ||
                tablero[filaOrigen][colOrigen] != 'X') {

                std::cout << "Posicion invalida.\n";
                continue;
            }

            std::cout << "Fila destino: ";
            std::cin >> filaDestino;

            std::cout << "Columna destino: ";
            std::cin >> colDestino;

            // Validar destino
            if (filaDestino < 0 || filaDestino >= FILA ||
                colDestino < 0 || colDestino >= COLUMNA ||
                tablero[filaDestino][colDestino] != '.') {

                std::cout << "No puedes mover ahi.\n";
                continue;
            }

            // Mover ficha
            tablero[filaDestino][colDestino] = 'X';
            tablero[filaOrigen][colOrigen] = '.';

            turno = true; // CAMBIO REAL
        }

        // Aquí iría el turno del otro jugador o IA
        turno = false;

        // Condición de fin (ejemplo)
        // juegoAcabado = true;
    }
}