#include <iostream>
#include <cstdlib>  
#include "Const.h"
#include "tablero.h"
#include "Movimiento.h"

// Buscar el rey en el tablero
void BuscarRey(char tablero[FILA][COLUMNA], char rey, int& fila, int& col) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {
            if (tablero[i][j] == rey) {
                fila = i;
                col = j;
                return;
            }
        }
    }
}

// Comprobar si el jugador actual amenaza al rey rival
bool HayJaque(char tablero[FILA][COLUMNA], bool turnoQueAtaca) {

    int filaRey, colRey;
    char reyObjetivo;

    // Asignar el rey enemigo según el turno
    if (turnoQueAtaca) {
        reyObjetivo = 'k';
    }
    else {
        reyObjetivo = 'K';
    }

    BuscarRey(tablero, reyObjetivo, filaRey, colRey);

    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {

            char ficha = tablero[i][j];
            bool movimientoValido = false;

            // Comprobar si la ficha pertenece al jugador que ataca
            if (turnoQueAtaca) {
                if (!(ficha == 'P' || ficha == 'T' || ficha == 'H' ||
                    ficha == 'B' || ficha == 'Q' || ficha == 'K'))
                    continue;
            }
            else {
                if (!(ficha == 'p' || ficha == 't' || ficha == 'h' ||
                    ficha == 'b' || ficha == 'q' || ficha == 'k'))
                    continue;
            }

            // Simular ataque al rey usando las funciones de movimiento
            if (ficha == 'P' || ficha == 'p') {
                MovimientoPeon(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }
            else if (ficha == 'T' || ficha == 't') {
                MovimientoTorre(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }
            else if (ficha == 'B' || ficha == 'b') {
                MovimientoAlfil(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }
            else if (ficha == 'H' || ficha == 'h') {
                MovimientoCaballo(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }
            else if (ficha == 'Q' || ficha == 'q') {
                MovimientoReina(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }
            else if (ficha == 'K' || ficha == 'k') {
                MovimientoRey(tablero, i, j, filaRey, colRey, turnoQueAtaca, movimientoValido);
            }

            if (movimientoValido) {
                return true;
            }
        }
    }

    return false;
}



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

                if (ficha == 'P' && filaDestino == 7)
                    tablero[filaDestino][colDestino] = 'Q';
                else if (ficha == 'p' && filaDestino == 0)
                    tablero[filaDestino][colDestino] = 'q';

                if (HayJaque(tablero, turno)) {
                    std::cout << "Jaque al rey! Estas obligado a mover el rey, sino lo mataran y perderas.\n";
                    system("pause");
                }

                turno = !turno;
                std::cout << "Movimiento correcto\n";
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