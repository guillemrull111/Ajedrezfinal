#include <iostream>
#include <cstdlib>  
#include "Const.h"
#include "tablero.h"
#include "Movimiento.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {
    int filaOrigen, colOrigen;
    int filaDestino, colDestino;
    bool juegoAcabado = false;
    bool turno = true;  

    while (!juegoAcabado) {
        std::cout << "\n(0 0 para salir)\n";
        std::cout << "\nTurno: " << (turno ? "MAYUSCULAS (arriba)" : "minusculas (abajo)") << "\n";

        std::cout << "Fila origen (1-8): ";
        std::cin >> filaOrigen;
        std::cout << "Columna origen (1-8): ";
        std::cin >> colOrigen;

        if (filaOrigen == 0 && colOrigen == 0) {
            std::cout << "¡Juego terminado!\n";
            juegoAcabado = true;
            continue;
        }

        if (filaOrigen < 1 || filaOrigen > 8 || colOrigen < 1 || colOrigen > 8) {
            std::cout << "Fuera del tablero\n";
            system("cls");
            ImprimirTablero(tablero);
            continue;
        }

        filaOrigen = 8 - filaOrigen;
        colOrigen = colOrigen - 1;

        char ficha = tablero[filaOrigen][colOrigen];

        // Turno arriba mayusculas y abajo minusculas
        bool esMiFicha = false;
        if (turno) {  
            if (ficha == 'P' || ficha == 'T' || ficha == 'H' || ficha == 'B' || ficha == 'Q' || ficha == 'K') {
                esMiFicha = true;
            }
        }
        else {  
            if (ficha == 'p' || ficha == 't' || ficha == 'h' || ficha == 'b' || ficha == 'q' || ficha == 'k') {
                esMiFicha = true;
            }
        }

        if (esMiFicha) {
            std::cout << "Fila destino (1-8): ";
            std::cin >> filaDestino;
            std::cout << "Columna destino (1-8): ";
            std::cin >> colDestino;

            if (filaDestino < 1 || filaDestino > 8 || colDestino < 1 || colDestino > 8) {
                std::cout << "Destino fuera del tablero\n";
                system("cls");
                ImprimirTablero(tablero);
                continue;
            }

            filaDestino = 8 - filaDestino;
            colDestino = colDestino - 1;

            char destino = tablero[filaDestino][colDestino];
            int diferenciaFila = filaDestino - filaOrigen;
            int diferenciaColumna = colDestino - colOrigen;
            int direccionPeon = (turno == false) ? -1 : 1;
            bool inicio = (filaOrigen == (turno ? 1 : 6));

            bool movimientoValido = false;

            // PEÓN
            if (ficha == 'P' || ficha == 'p') {
                MovimientoPeon(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);
            }

            // TORRE
            if (ficha == 'T' || ficha == 't') {
                MovimientoTorre(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);
            }

            // ALFIL
            if (ficha == 'B' || ficha == 'b') {
                MovimientoAlfil(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);
            }

            // CABALLO
            if (ficha == 'H' || ficha == 'h') {
                MovimientoCaballo(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);
            }

            // REY 
            if (ficha == 'K' || ficha == 'k') {
                MovimientoRey(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);

            }

            // REINA
            if (ficha == 'Q' || ficha == 'q') {
                MovimientoReina(tablero, filaOrigen, colOrigen, filaDestino, colDestino, turno, movimientoValido);

            }

            if (movimientoValido) {
                tablero[filaDestino][colDestino] = ficha;
                tablero[filaOrigen][colOrigen] = '*';
                turno = !turno;
                std::cout << "¡Movimiento correcto!\n";
            }
            else {
                std::cout << "Movimiento inválido\n";
            }
        }
        else {
            std::cout << "No es tu ficha o posición vacía\n";
        }

        system("cls");
        ImprimirTablero(tablero);
    }
}