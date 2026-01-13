#include <iostream>
#include <cstdlib>  
#include "Const.h"
#include "tablero.h"
#include "Movimiento.h"
#include "Jaque.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {
    int filaOrigen, colOrigen; // Coordenadas de origen donde esta la pieza que se quiere mover
    int filaDestino, colDestino; // Coordenadas de destino donde se quiere mover la pieza
    bool juegoAcabado = false; // Controla si la partida ha terminado
    bool turno = true;  // true: mayúsculas , false: minúsculas 

    while (!juegoAcabado) {  // Bucle principal del juego
        std::cout << "\n(0 0 para salir)\n";
        std::cout << "\nTurno: " << (turno ? "MAYUSCULAS (arriba)" : "minusculas (abajo)") << "\n";

        std::cout << "Fila origen (1-8): ";
        std::cin >> filaOrigen;
        std::cout << "Columna origen (1-8): ";
        std::cin >> colOrigen;

        // Opción para terminar la partida
        if (filaOrigen == 0 && colOrigen == 0) {
            std::cout << "¡Juego terminado!\n";
            juegoAcabado = true;
            break; // Salimos del bucle
        }

        // Comprobación de que el origen está dentro del tablero
        if (filaOrigen < 1 || filaOrigen > 8 || colOrigen < 1 || colOrigen > 8) {
            std::cout << "Fuera del tablero\n";
            system("cls");
            ImprimirTablero(tablero);
            continue; // Pide otra vez coordenadas
        }

        // Conversión de coordenadas
        filaOrigen = 8 - filaOrigen;
        colOrigen = colOrigen - 1;

        char ficha = tablero[filaOrigen][colOrigen]; // Ficha en la casilla de origen

        // Comprobamos si la ficha elegida es del jugador al que le toca tirar
        bool esMiFicha = false;
        if (turno) {  // Turno mayúsculas
            if (ficha == 'P' || ficha == 'T' || ficha == 'H' || ficha == 'B' || ficha == 'Q' || ficha == 'K') {
                esMiFicha = true;
            }
        }
        else {   // Turno minúsculas
            if (ficha == 'p' || ficha == 't' || ficha == 'h' || ficha == 'b' || ficha == 'q' || ficha == 'k') {
                esMiFicha = true;
            }
        }

        if (esMiFicha) { // Solo continuamos si la ficha es del jugador
            std::cout << "Fila destino (1-8): ";
            std::cin >> filaDestino;
            std::cout << "Columna destino (1-8): ";
            std::cin >> colDestino;

            // Comprobar que el destino está dentro del tablero
            if (filaDestino < 1 || filaDestino > 8 || colDestino < 1 || colDestino > 8) {
                std::cout << "Destino fuera del tablero\n";
                system("cls");
                ImprimirTablero(tablero);
                continue; // Pide otra vez coordenadas
            }

            // Conversión de coordenadas
            filaDestino = 8 - filaDestino;
            colDestino = colDestino - 1;

            // Indica si el movimiento es valido
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

            if (movimientoValido) { // Si el movimiento es valido
                tablero[filaDestino][colDestino] = ficha; // Movemos la ficha al destino
                tablero[filaOrigen][colOrigen] = '*'; // Vaciamps la casilla de origen

                // Conversión de peón a reina
                if (ficha == 'P' && filaDestino == 7) // Peón blanco llega al final
                    tablero[filaDestino][colDestino] = 'Q'; // Se convierte en reina blanca
                else if (ficha == 'p' && filaDestino == 0) // Peón negro llega al final
                    tablero[filaDestino][colDestino] = 'q'; // Se convierte en reina negra

                bool enJaque, jaqueMate;
                // Comprobar si el movimiento deja al rival en jaque/jaque mate
                ComprobarJaqueYMate(tablero, !turno, enJaque, jaqueMate);
                if (enJaque) {
                    std::cout << "¡Jaque al rey! Estás obligado a mover el rey.\n";
                    system("pause");
                }
                if (jaqueMate) {
                    std::cout << "¡¡Jaque mate!!\n";
                    juegoAcabado = true; // Termina la partida
                }

                turno = !turno;  // Cambiar turno al otro jugador
                std::cout << "Movimiento correcto\n";
            }
            else {
                std::cout << "Movimiento inválido\n";  // Movimiento no válido
            }

        }
        else {
            std::cout << "No es tu ficha o posición vacía\n";  // Intento de mover ficha vacía o del rival
        }

        system("cls"); //Limpia la pantalla
        ImprimirTablero(tablero); //Muestra el tablero actualizado
    }
}