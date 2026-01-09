#include "Movimiento.h"


void MovimientoPeon(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
    int direccionPeon = (turno == false) ? -1 : 1;
    bool inicio = (filaOrigen == (turno ? 1 : 6));

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

void MovimientoTorre(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    bool rutaLibre = true;
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
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

void MovimientoAlfil(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    bool caminoLibre = true;
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
    // Debe ser movimiento diagonal: |difFila| == |difCol|
    int valorDifFila = diferenciaFila;
    if (valorDifFila < 0) valorDifFila = -valorDifFila;
    int valorDifColumna = diferenciaColumna;
    if (valorDifColumna < 0) valorDifColumna = -valorDifColumna;

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

void MovimientoCaballo(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
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
    // Mayúsculas matan a minús
    if (turno && (destino == 'p' || destino == 't' || destino == 'h' ||
        destino == 'b' || destino == 'q' || destino == 'k')) {
        puedeComer = true;
    }
    // Minúsculas matan a mayús
    if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' ||
        destino == 'B' || destino == 'Q' || destino == 'K')) {
        puedeComer = true;
    }

    if (formaCaballo && (destino == '*' || puedeComer)) {
        movimientoValido = true;
    }
}

void MovimientoRey(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
    if ((diferenciaFila == 1 || diferenciaFila == 0 || diferenciaFila == -1) &&
        (diferenciaColumna == 1 || diferenciaColumna == 0 || diferenciaColumna == -1) &&
        !(diferenciaFila == 0 && diferenciaColumna == 0)) {

        bool puedeCapturar = false;

        if (turno) { // Para matar a las minusculas
            if (destino == 'p' || destino == 't' || destino == 'h' ||
                destino == 'b' || destino == 'q' || destino == 'k') {
                puedeCapturar = true;
            }
        }
        else { // Para matar a las mayusculas
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

void MovimientoReina(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino];
    int diferenciaFila = filaDestino - filaOrigen;
    int diferenciaColumna = colDestino - colOrigen;
    bool rutaLibre = true;
    bool puedeMatar = false;
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

    // Mirar si puede matar
    if (turno) { // Mayúsculas matan minúsculas
        if (destino == 'p' || destino == 't' || destino == 'h' ||
            destino == 'b' || destino == 'q' || destino == 'k') {
            puedeMatar = true;
        }
    }
    else { // Minúsculas matan mayúsculas
        if (destino == 'P' || destino == 'T' || destino == 'H' ||
            destino == 'B' || destino == 'Q' || destino == 'K') {
            puedeMatar = true;
        }
    }

    // Movimiento final válido
    if (rutaLibre && (destino == '*' || puedeMatar)) {
        movimientoValido = true;
    }
}

