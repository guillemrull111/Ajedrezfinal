#include <iostream>
#include <cstdlib>  
#include "Const.h"
#include "tablero.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {
    int filaOrigen, colOrigen;
    int filaDestino, colDestino;
    bool juegoAcabado = false;
    bool turno = true;  // true = mayúsculas arriba

    while (!juegoAcabado) {
        std::cout << "\n(0 0 para salir)\n";
        std::cout << "\nTurno: " << (turno ? "MAYÚSCULAS (arriba)" : "minúsculas (abajo)") << "\n";

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

        // CHEQUEO SIMPLE: turno arriba busca P/T/H/B/Q/K, abajo p/t/h/b/q/k
        bool esMiFicha = false;
        if (turno) {  // MAYÚSCULAS
            if (ficha == 'P' || ficha == 'T' || ficha == 'H' || ficha == 'B' || ficha == 'Q' || ficha == 'K') {
                esMiFicha = true;
            }
        }
        else {  // minúsculas
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
                if (diferenciaFila == direccionPeon && diferenciaColumna == 0 && destino == '*') {
                    movimientoValido = true;  // 1 casilla
                }
                if (inicio && diferenciaFila == direccionPeon * 2 && diferenciaColumna == 0 &&
                    tablero[filaOrigen + direccionPeon][colOrigen] == '*' && destino == '*') {
                    movimientoValido = true;  // 2 casillas inicio
                }
                if (diferenciaFila == direccionPeon && (diferenciaColumna == 1 || diferenciaColumna == -1)) {
                    if (turno && (destino == 'p' || destino == 't' || destino == 'h' || destino == 'b' || destino == 'q' || destino == 'k')) {
                        movimientoValido = true;  // Captura abajo
                    }
                    if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K')) {
                        movimientoValido = true;  // Captura arriba
                    }
                }
            }

            // TORRE
            if (ficha == 'T' || ficha == 't') {
                bool rutaLibre = true;
                if (!(diferenciaFila == 0 || diferenciaColumna == 0)) {
                    rutaLibre = false;  // Solo H/V
                }
                else {
                    int pasoFila = 0, pasoColumna = 0;
                    if (diferenciaFila > 0) pasoFila = 1;
                    if (diferenciaFila < 0) pasoFila = -1;
                    if (diferenciaColumna > 0) pasoColumna = 1;
                    if (diferenciaColumna < 0) pasoColumna = -1;

                    int filaActual = filaOrigen + pasoFila;
                    int columnaActual = colOrigen + pasoColumna;
                    while (filaActual != filaDestino || columnaActual != colDestino) {
                        if (tablero[filaActual][columnaActual] != '*') {
                            rutaLibre = false;
                            break;
                        }
                        filaActual += pasoFila;
                        columnaActual += pasoColumna;
                    }
                }

                bool puedeCapturar = false;
                if (turno) {  // Mayús capturan minús
                    if (destino == 'p' || destino == 't' || destino == 'h' || destino == 'b' || destino == 'q' || destino == 'k') {
                        puedeCapturar = true;
                    }
                }
                else {  // minús capturan mayús
                    if (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K') {
                        puedeCapturar = true;
                    }
                }

                if (rutaLibre && (destino == '*' || puedeCapturar)) {
                    movimientoValido = true;
                }
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
