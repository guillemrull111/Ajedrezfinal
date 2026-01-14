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

void ComprobarJaque(char tablero[FILA][COLUMNA], bool turno, bool& enJaque) { // Comprueba si el jugador está en jaque

    enJaque = false; // por defecto, no hay jaque
    int filaRey, colRey;  // Posición del rey del jugador actual
    bool movimientoValido; // Indica si una pieza rival puede atacar al rey

    //'K' si es turno de blancas , 'k' si es turno de negras
    char rey = turno ? 'K' : 'k';

    // Buscar la posición del rey
    BuscarRey(tablero, rey, filaRey, colRey);

    // Recorrer todas las fichas del tablero
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {

            char ficha = tablero[i][j]; // Ficha actual
            movimientoValido = false; // Ponemos en false para evitar errores

            // Si és turno de blancas comprobamos si las fichas negras pueden atacar a nuestro rey
            if (turno &&
                (ficha == 'p' || ficha == 't' || ficha == 'b' ||
                    ficha == 'h' || ficha == 'q' || ficha == 'k')) {

                // Probamos el movimiento de todas las piezas
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

                // Si alguna pieza tiene un movimiento válido hacia la posición del rey hay jaque
                if (movimientoValido) {
                    enJaque = true;
                    return; // Una vez ya hemos encontrado el jaque no hace falta seguir comprobando
                }
            }

            // Si és turno de negras comprobamos si las fichas blancas pueden atacar a nuestro rey
            if (!turno &&
                (ficha == 'P' || ficha == 'T' || ficha == 'B' ||
                    ficha == 'H' || ficha == 'Q' || ficha == 'K')) {

                // Probamos el movimiento de todas las piezas
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

                // Si alguna pieza tiene un movimiento válido hacia la posición del rey hay jaque
                if (movimientoValido) {
                    enJaque = true;
                    return; // Una vez ya hemos encontrado el jaque no hace falta seguir comprobando
                }
            }
        }
    }
}

void ComprobarJaqueYMate(char tablero[FILA][COLUMNA], bool turno, bool& enJaque, bool& jaqueMate) { // Comprueba si el jugador está en jaque mate

    enJaque = false; // Por defecto no hay jaque
    jaqueMate = false; // Por defecto no hay jaque mate
    bool movimientoValido; 

    // Comprueba si el jugador está en jaque
    ComprobarJaque(tablero, turno, enJaque);

    if (!enJaque)
        return; // si no hay jaque no hay jaque mate

    // Simula los movimientos que puede hacer el jugador en jaque
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {

            char ficha = tablero[i][j];

            // Solo piezas del jugador que esta en jaque
            if ((turno &&
                (ficha == 'P' || ficha == 'T' || ficha == 'B' ||
                    ficha == 'H' || ficha == 'Q' || ficha == 'K')) ||

                (!turno &&
                    (ficha == 'p' || ficha == 't' || ficha == 'b' ||
                        ficha == 'h' || ficha == 'q' || ficha == 'k'))) {

                // Recorremos todas las casillas como posibles destinos
                for (int filaDestino = 0; filaDestino < FILA; filaDestino++) {
                    for (int colDestino = 0; colDestino < COLUMNA; colDestino++) {

                        movimientoValido = false; // Se resetea para cada movimiento

                        // Comprobamos si la pieza puede moverse a (filaDestino, colDestino)
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

                        // Si no es un movimiento válido lo ignoramos
                        if (!movimientoValido)
                            continue; // Pasa a comprobar la siguiente posición

                        // Simula los movimientos que puede hacer el jugador en jaque en el tablero
                        char origen = tablero[i][j];
                        char destino = tablero[filaDestino][colDestino];
                        tablero[filaDestino][colDestino] = origen;
                        tablero[i][j] = '*';

                        // Comprobamos si el rey sigue en jaque
                        bool sigueEnJaque;
                        ComprobarJaque(tablero, turno, sigueEnJaque);

                        // Volvemos a poner las piezas donde estaban
                        tablero[i][j] = origen;
                        tablero[filaDestino][colDestino] = destino;

                        if (!sigueEnJaque)
                            return; // Si el rey ya no esta en jaque no és jaque mate
                    }
                }
            }
        }
    }

    // Si sigue en jaque, no hay ningún movimiento que pueda dejar al rey fura de jaque, por lo que es jaque mate
    jaqueMate = true;
}