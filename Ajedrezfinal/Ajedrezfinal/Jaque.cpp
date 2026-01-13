#include "Jaque.h"

void BuscarRey(char tablero[FILA][COLUMNA], char rey, int& fila, int& col) { //Fila y columna por referencia con '&'
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) { //Recorre todas las casillas
            if (tablero[i][j] == rey) {  //cuando encuentra el rey guarda su posición
                fila = i;
                col = j;
                return; //Sale de la función, ya que ya se ha encontrado el rey
            }
        }
    }
}

void ComprobarJaque(char tablero[FILA][COLUMNA], bool turno, bool& enJaque) {

    enJaque = false; // por defecto, no hay jaque
    int filaRey, colRey;
    bool movimientoValido;

    // Determinar qué rey buscamos
    char rey = turno ? 'K' : 'k';

    // Buscar la posición del rey
    BuscarRey(tablero, rey, filaRey, colRey);

    // Recorrer todas las fichas del tablero
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {

            char ficha = tablero[i][j];
            movimientoValido = false;

            // Si turno de blancas, comprobamos fichas negras
            if (turno &&
                (ficha == 'p' || ficha == 't' || ficha == 'b' ||
                    ficha == 'h' || ficha == 'q' || ficha == 'k')) {

                if (ficha == 'p')
                    MovimientoPeon(tablero, i, j, filaRey, colRey, false, movimientoValido);
                else if (ficha == 't')
                    MovimientoTorre(tablero, i, j, filaRey, colRey, false, movimientoValido);
                else if (ficha == 'b')
                    MovimientoAlfil(tablero, i, j, filaRey, colRey, false, movimientoValido);
                else if (ficha == 'h')
                    MovimientoCaballo(tablero, i, j, filaRey, colRey, false, movimientoValido);
                else if (ficha == 'q')
                    MovimientoReina(tablero, i, j, filaRey, colRey, false, movimientoValido);
                else if (ficha == 'k')
                    MovimientoRey(tablero, i, j, filaRey, colRey, false, movimientoValido);

                if (movimientoValido) {
                    enJaque = true;
                    return; // jaque detectado
                }
            }

            // Si turno de negras, comprobamos fichas blancas
            if (!turno &&
                (ficha == 'P' || ficha == 'T' || ficha == 'B' ||
                    ficha == 'H' || ficha == 'Q' || ficha == 'K')) {

                if (ficha == 'P')
                    MovimientoPeon(tablero, i, j, filaRey, colRey, true, movimientoValido);
                else if (ficha == 'T')
                    MovimientoTorre(tablero, i, j, filaRey, colRey, true, movimientoValido);
                else if (ficha == 'B')
                    MovimientoAlfil(tablero, i, j, filaRey, colRey, true, movimientoValido);
                else if (ficha == 'H')
                    MovimientoCaballo(tablero, i, j, filaRey, colRey, true, movimientoValido);
                else if (ficha == 'Q')
                    MovimientoReina(tablero, i, j, filaRey, colRey, true, movimientoValido);
                else if (ficha == 'K')
                    MovimientoRey(tablero, i, j, filaRey, colRey, true, movimientoValido);

                if (movimientoValido) {
                    enJaque = true;
                    return; // jaque detectado
                }
            }
        }
    }
}

void ComprobarJaqueYMate(char tablero[FILA][COLUMNA], bool turno, bool& enJaque, bool& jaqueMate) {

    enJaque = false;
    jaqueMate = false;
    bool movimientoValido;

    // 1 Comprobar jaque en la posición actual usando la función independiente
    ComprobarJaque(tablero, turno, enJaque);

    if (!enJaque)
        return; // si no hay jaque → no puede haber jaque mate

    // 2 Simular todos los movimientos posibles del jugador en jaque
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {

            char ficha = tablero[i][j];

            // Solo piezas del jugador en jaque
            if ((turno &&
                (ficha == 'P' || ficha == 'T' || ficha == 'B' ||
                    ficha == 'H' || ficha == 'Q' || ficha == 'K')) ||

                (!turno &&
                    (ficha == 'p' || ficha == 't' || ficha == 'b' ||
                        ficha == 'h' || ficha == 'q' || ficha == 'k'))) {

                // Recorrer todas las casillas como posibles destinos
                for (int filaDestino = 0; filaDestino < FILA; filaDestino++) {
                    for (int colDestino = 0; colDestino < COLUMNA; colDestino++) {

                        movimientoValido = false;

                        // Comprobar si la pieza puede moverse a (filaDestino, colDestino)
                        if (ficha == 'P' || ficha == 'p')
                            MovimientoPeon(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);
                        else if (ficha == 'T' || ficha == 't')
                            MovimientoTorre(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);
                        else if (ficha == 'B' || ficha == 'b')
                            MovimientoAlfil(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);
                        else if (ficha == 'H' || ficha == 'h')
                            MovimientoCaballo(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);
                        else if (ficha == 'Q' || ficha == 'q')
                            MovimientoReina(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);
                        else if (ficha == 'K' || ficha == 'k')
                            MovimientoRey(tablero, i, j, filaDestino, colDestino, turno, movimientoValido);

                        if (!movimientoValido)
                            continue; // si no es un movimiento válido, ignorar

                        // 3 Simular el movimiento en el tablero
                        char origen = tablero[i][j];
                        char destino = tablero[filaDestino][colDestino];
                        tablero[filaDestino][colDestino] = origen;
                        tablero[i][j] = '*';

                        // 4 Comprobar si el rey sigue en jaque
                        bool sigueEnJaque;
                        ComprobarJaque(tablero, turno, sigueEnJaque);

                        // 5 Deshacer movimiento
                        tablero[i][j] = origen;
                        tablero[filaDestino][colDestino] = destino;

                        if (!sigueEnJaque)
                            return; // el rey puede salvarse → no es jaque mate
                    }
                }
            }
        }
    }

    // 6 Si llegamos aquí → no hay movimiento que salve al rey → JAQUE MATE
    jaqueMate = true;
}