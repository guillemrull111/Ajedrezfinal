#include <iostream>
#include "Const.h"
#include "tablero.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {

    int filaOrigen, colOrigen;
    int filaDestino, colDestino;
    bool juegoAcabado = false;
    bool turno = false; // false = blancas ('p'), true = negras ('P')

    while (!juegoAcabado) {

        char fichaTurno = (turno == false) ? 'p' : 'P';

        std::cout << "\nTurno de las fichas: " << fichaTurno << "\n";

        std::cout << "Fila de la ficha a mover (1-8): ";
        std::cin >> filaOrigen;
        std::cout << "Columna de la ficha a mover (1-8): ";
        std::cin >> colOrigen;

        // Validar rango
        if (filaOrigen < 1 || filaOrigen > 8 || colOrigen < 1 || colOrigen > 8) {
            std::cout << "Posicion fuera del tablero\n";
            continue;
        }

        // Convertir a memoria
        filaOrigen = 8 - filaOrigen;
        colOrigen = colOrigen - 1;

        if (tablero[filaOrigen][colOrigen] == fichaTurno) {

            std::cout << "Fila destino (1-8): ";
            std::cin >> filaDestino;
            std::cout << "Columna destino (1-8): ";
            std::cin >> colDestino;

            // Validar destino
            if (filaDestino < 1 || filaDestino > 8 || colDestino < 1 || colDestino > 8) {
                std::cout << "Destino fuera del tablero\n";
                continue;
            }

            // Convertir destino
            filaDestino = 8 - filaDestino;
            colDestino = colDestino - 1;

            // Mover ficha
            tablero[filaOrigen][colOrigen] = '*';
            tablero[filaDestino][colDestino] = fichaTurno;

            // Cambiar turno
            turno = !turno;

        }
        else {
            std::cout << "No es tu ficha o no hay ficha en esa posicion.\n";
        }

        system("cls");
        ImprimirTablero(tablero);
    }
}
