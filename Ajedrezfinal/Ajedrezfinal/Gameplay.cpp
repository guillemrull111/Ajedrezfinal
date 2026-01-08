#include <iostream>
#include <cstdlib>  
#include "Const.h"
#include "tablero.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {
    int filaOrigen, colOrigen;
    int filaDestino, colDestino;
    bool juegoAcabado = false;
    bool turno = true;  

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
                if (diferenciaFila == direccionPeon && diferenciaColumna == 0 && destino == '*') {
                    movimientoValido = true;  // Moverse una casilla
                }
                if (inicio && diferenciaFila == direccionPeon * 2 && diferenciaColumna == 0 &&
                    tablero[filaOrigen + direccionPeon][colOrigen] == '*' && destino == '*') {
                    movimientoValido = true;  // Moverse 2 casillas, solo funciona cuando esta en la posicion inicial
                }
                if (diferenciaFila == direccionPeon && (diferenciaColumna == 1 || diferenciaColumna == -1)) {
                    if (turno && (destino == 'p' || destino == 't' || destino == 'h' || destino == 'b' || destino == 'q' || destino == 'k')) {
                        movimientoValido = true;  // Matar (fichas de abajo)
                    }
                    if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K')) {
                        movimientoValido = true;  // Matar (fichas de arriba)
                    }
                }
            }

            // TORRE
            if (ficha == 'T' || ficha == 't') {
                bool rutaLibre = true;
                if (!(diferenciaFila == 0 || diferenciaColumna == 0)) {
                    rutaLibre = false;  
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
                if (turno) {  // Mayúsculas capturan minúsculas
                    if (destino == 'p' || destino == 't' || destino == 'h' || destino == 'b' || destino == 'q' || destino == 'k') {
                        puedeCapturar = true;
                    }
                }
                else {  // Minúsculas capturan mayúsculas
                    if (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K') {
                        puedeCapturar = true;
                    }
                }

                if (rutaLibre && (destino == '*' || puedeCapturar)) {
                    movimientoValido = true;
                }
            }

            // ALFIL
            if (ficha == 'B' || ficha == 'b') {
                bool caminoLibre = true;

                // Debe ser movimiento diagonal: |difFila| == |difCol|
                int valorDifFila = diferenciaFila;
                if (valorDifFila < 0) valorDifFila = - valorDifFila;
                int valorDifColumna = diferenciaColumna;
                if (valorDifColumna < 0) valorDifColumna = - valorDifColumna;

                if (valorDifFila != valorDifColumna) {
                    caminoLibre = false;
                }
                else {
                    int pasoFila = 0;
                    int pasoColumna = 0;

                    // Dirección de la diagonal
                    if (diferenciaFila > 0) pasoFila = 1;
                    if (diferenciaFila < 0) pasoFila = -1;
                    if (diferenciaColumna > 0) pasoColumna = 1;
                    if (diferenciaColumna < 0) pasoColumna = -1;

                    int filaActual = filaOrigen + pasoFila;
                    int colActual = colOrigen + pasoColumna;

                    // Mirar casillas de entre medio
                    while (filaActual != filaDestino || colActual != colDestino) {
                        if (tablero[filaActual][colActual] != '*') {
                            caminoLibre = false;
                            break;
                        }
                        filaActual += pasoFila;
                        colActual += pasoColumna;
                    }
                }

                bool puedeComer = false;
                // Mayúsculas matan a minúsculas
                if (turno && (destino == 'p' || destino == 't' || destino == 'h' ||
                    destino == 'b' || destino == 'q' || destino == 'k')) {
                    puedeComer = true;
                }
                // Minúsculas matan a mayúsculas
                if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' ||
                    destino == 'B' || destino == 'Q' || destino == 'K')) {
                    puedeComer = true;
                }

                if (caminoLibre && (destino == '*' || puedeComer)) {
                    movimientoValido = true;
                }
            }

            // CABALLO
            if (ficha == 'H' || ficha == 'h') {
                int distanciaFila = diferenciaFila;
                if (distanciaFila < 0) distanciaFila = -distanciaFila;
                int distanciaColumna = diferenciaColumna;
                if (distanciaColumna < 0) distanciaColumna = -distanciaColumna;

                bool formaCaballo = false;
                // Tiene que hacer el movimiento de L: 2+1 o 1+2
                if ((distanciaFila == 2 && distanciaColumna == 1) || (distanciaFila == 1 && distanciaColumna == 2)) {
                    formaCaballo = true;
                }

                bool puedeComer = false;
                // Mayús matan a minús
                if (turno && (destino == 'p' || destino == 't' || destino == 'h' ||
                    destino == 'b' || destino == 'q' || destino == 'k')) {
                    puedeComer = true;
                }
                // Minús matan a mayús
                if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' ||
                    destino == 'B' || destino == 'Q' || destino == 'K')) {
                    puedeComer = true;
                }

                if (formaCaballo && (destino == '*' || puedeComer)) {
                    movimientoValido = true;
                }
            }

            // REY 
            if (ficha == 'K' || ficha == 'k') {

                if ((diferenciaFila == 1 || diferenciaFila == 0 || diferenciaFila == -1) &&
                    (diferenciaColumna == 1 || diferenciaColumna == 0 || diferenciaColumna == -1) &&
                    !(diferenciaFila == 0 && diferenciaColumna == 0)) {

                    bool puedeCapturar = false;

                    if (turno) { // Mayúsculas
                        if (destino == 'p' || destino == 't' || destino == 'h' ||
                            destino == 'b' || destino == 'q' || destino == 'k') {
                            puedeCapturar = true;
                        }
                    }
                    else { // Minúsculas
                        if (destino == 'P' || destino == 'T' || destino == 'H' ||
                            destino == 'B' || destino == 'Q' || destino == 'K') {
                            puedeCapturar = true;
                        }
                    }

                    if (destino == '*' || puedeCapturar) {
                        movimientoValido = true;
                    }
                }
            }

            // REINA
            if (ficha == 'Q' || ficha == 'q') {

                bool rutaLibre = true;
                bool puedeCapturar = false;
                bool movimientoValidoReina = false;

                int pasoFila = 0;
                int pasoColumna = 0;
                int filaActual;
                int columnaActual;

                // Para mirar que el movimiento sea horizontal, vertical o en diagonal
                if (diferenciaFila == 0 || diferenciaColumna == 0) {
                    movimientoValidoReina = true;   // movimiento tipo torre
                }
                else if (diferenciaFila == diferenciaColumna || diferenciaFila == -diferenciaColumna) {
                    movimientoValidoReina = true;   // movimiento tipo alfil
                }

                if (!movimientoValidoReina) {
                    rutaLibre = false;
                }
                else {
                    // Dirección de movimiento
                    if (diferenciaFila > 0) pasoFila = 1;
                    else if (diferenciaFila < 0) pasoFila = -1;

                    if (diferenciaColumna > 0) pasoColumna = 1;
                    else if (diferenciaColumna < 0) pasoColumna = -1;

                    // Recorrer la ruta hasta la casilla destino (sin incluirla)
                    filaActual = filaOrigen + pasoFila;
                    columnaActual = colOrigen + pasoColumna;

                    while (filaActual != filaDestino || columnaActual != colDestino) {
                        if (tablero[filaActual][columnaActual] != '*') {
                            rutaLibre = false;
                            break;
                        }
                        filaActual += pasoFila;
                        columnaActual += pasoColumna;
                    }
                }

                // Mirar si puede capturar
                if (turno) { // Mayúsculas comen minúsculas
                    if (destino == 'p' || destino == 't' || destino == 'h' ||
                        destino == 'b' || destino == 'q' || destino == 'k') {
                        puedeCapturar = true;
                    }
                }
                else { // Minúsculas comen mayúsculas
                    if (destino == 'P' || destino == 'T' || destino == 'H' ||
                        destino == 'B' || destino == 'Q' || destino == 'K') {
                        puedeCapturar = true;
                    }
                }

                // Movimiento final válido
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
