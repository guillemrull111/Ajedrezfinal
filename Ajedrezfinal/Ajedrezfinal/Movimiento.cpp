#include "Movimiento.h"


void MovimientoPeon(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal
    int direccionPeon = (turno == false) ? -1 : 1; // Dirección de avance del peón según el turno
    bool inicio = (filaOrigen == (turno ? 1 : 6));// Indica si el peón está en su fila inicial para permitir mover 2 casillas

    if (diferenciaFila == direccionPeon && diferenciaColumna == 0 && destino == '*') {
        movimientoValido = true;  // 1 casilla
    }
    if (inicio && diferenciaFila == direccionPeon * 2 && diferenciaColumna == 0 &&
        tablero[filaOrigen + direccionPeon][colOrigen] == '*' && destino == '*') {
        movimientoValido = true;  // 2 casillas inicio
    }
    // se mueve 1 posición hacia adelante y otra de lado
    if (diferenciaFila == direccionPeon && (diferenciaColumna == 1 || diferenciaColumna == -1)) {
        //Turno Mayus
        if (turno && (destino == 'p' || destino == 't' || destino == 'h' || destino == 'b' || destino == 'q' || destino == 'k')) {
            movimientoValido = true;  // Captura abajo
        }
        //Turno Minus
        if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K')) {
            movimientoValido = true;  // Captura arriba
        }
    }
}

void MovimientoTorre(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    bool rutaLibre = true; // Indica si no hay piezas entre origen y destino
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal

    // La torre solo se puede mover en línea recta si es la misma fila o la misma columna
    if (!(diferenciaFila == 0 || diferenciaColumna == 0)) {
        rutaLibre = false; // movimiento no válido
    }
    else {
        int pasoFila = 0, pasoColumna = 0;
        if (diferenciaFila > 0) pasoFila = 1; // Se mueve una casilla hacia arriba
        if (diferenciaFila < 0) pasoFila = -1; // Se mueve una casilla hacia abajo
        if (diferenciaColumna > 0) pasoColumna = 1; // Se mueve una casilla hacia la derecha
        if (diferenciaColumna < 0) pasoColumna = -1; // Se mueve una casilla hacia la izquierda

        // Empezamos a comprobar desde la casilla siguiente al origen
        int filaActual = filaOrigen + pasoFila;
        int columnaActual = colOrigen + pasoColumna;

        // Recorremos todas las casillas entre el origen y el destino
        while (filaActual != filaDestino || columnaActual != colDestino) {
            // Si encontramos cualquier pieza en medio, la ruta no está libre
            if (tablero[filaActual][columnaActual] != '*') {
                rutaLibre = false;
                break;
            }
            // Avanzamos a la siguiente casilla en la dirección calculada
            filaActual += pasoFila;
            columnaActual += pasoColumna;
        }
    }

    bool puedeCapturar = false;// Indica si la torre puede capturar en la casilla destino

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
    // El movimiento es válido si la posición destino esta vacía o es una ficha rival
    if (rutaLibre && (destino == '*' || puedeCapturar)) {
        movimientoValido = true;
    }

}

void MovimientoAlfil(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    bool caminoLibre = true; // Indica si no hay piezas entre origen y destino
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal

    // Debe ser movimiento diagonal
    int valorDifFila = diferenciaFila; // La diferencia de la fila y la columna deben ser iguales 
    if (valorDifFila < 0) valorDifFila = -valorDifFila;
    int valorDifColumna = diferenciaColumna;
    if (valorDifColumna < 0) valorDifColumna = -valorDifColumna;

    if (valorDifFila != valorDifColumna) { // Si los valores no son iguales no es una diagonal
        caminoLibre = false;
    }
    else {
        int pasoFila = 0;
        int pasoColumna = 0;

        // Dirección de la diagonal en filas: -1 sube o 1 baja
        if (diferenciaFila > 0) pasoFila = 1;
        if (diferenciaFila < 0) pasoFila = -1;
        // Dirección de la diagonal en columnas: -1 izquierda o 1 derecha
        if (diferenciaColumna > 0) pasoColumna = 1;
        if (diferenciaColumna < 0) pasoColumna = -1;

        // Empezar a comprobar desde la casilla siguiente al origen
        int filaActual = filaOrigen + pasoFila;
        int colActual = colOrigen + pasoColumna;

        // Recorremos todas las casillas entre el origen y el destino
        while (filaActual != filaDestino || colActual != colDestino) {
            if (tablero[filaActual][colActual] != '*') {
                caminoLibre = false;
                break;
            }
            // Avanzar a la siguiente casilla en la diagonal
            filaActual += pasoFila;
            colActual += pasoColumna;
        }
    }

    bool puedeComer = false; // Indica si el alfil puede capturar en la casilla destino
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
    
    //  El movimiento es válido si el camino está libre o la casilla destino esta libre o hay una pieza rival
    if (caminoLibre && (destino == '*' || puedeComer)) {
        movimientoValido = true;
    }
}

void MovimientoCaballo(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal
    
    //Distancia entre origen y destino
    int distanciaFila = diferenciaFila;
    if (distanciaFila < 0) distanciaFila = -distanciaFila;
    int distanciaColumna = diferenciaColumna;
    if (distanciaColumna < 0) distanciaColumna = -distanciaColumna;

    bool formaCaballo = false; // Indica si el movimiento tiene forma de L
    // Tiene que hacer el movimiento de L: 2+1 o 1+2
    if ((distanciaFila == 2 && distanciaColumna == 1) || (distanciaFila == 1 && distanciaColumna == 2)) {
        formaCaballo = true;
    }

    bool puedeComer = false; // Indica si el caballo puede capturar la pieza destino
    // Mayúsculas matan a minúsculas
    if (turno && (destino == 'p' || destino == 't' || destino == 'h' ||destino == 'b' || destino == 'q' || destino == 'k')) {
        puedeComer = true;
    }
    // Minúsculas matan a mayúsculas
    if (!turno && (destino == 'P' || destino == 'T' || destino == 'H' || destino == 'B' || destino == 'Q' || destino == 'K')) {
        puedeComer = true;
    }

    // El movimiento es válido si se mueve en forma de L y el destino esta vacio o hay una pieza rival
    if (formaCaballo && (destino == '*' || puedeComer)) {
        movimientoValido = true;
    }
}

void MovimientoRey(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal

    // El rey solo puede moverse 1 casilla en cualquier dirección
    if ((diferenciaFila == 1 || diferenciaFila == 0 || diferenciaFila == -1) &&
        (diferenciaColumna == 1 || diferenciaColumna == 0 || diferenciaColumna == -1) &&
        !(diferenciaFila == 0 && diferenciaColumna == 0)) {

        bool puedeCapturar = false; // Indica si el rey puede capturar la pieza que hay en el destino

        if (turno) { // Mayusculas matan a las minusculas
            if (destino == 'p' || destino == 't' || destino == 'h' ||
                destino == 'b' || destino == 'q' || destino == 'k') {
                puedeCapturar = true;
            }
        }
        else { // Minusculas matan a las mayusculas
            if (destino == 'P' || destino == 'T' || destino == 'H' ||
                destino == 'B' || destino == 'Q' || destino == 'K') {
                puedeCapturar = true;
            }
        }
        // El movimiento es válido si la casilla destino está vacía o hay una pieza rival que el rey puede capturar
        if (destino == '*' || puedeCapturar) {
            movimientoValido = true;
        }
    }
}
void MovimientoReina(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido) {
    char destino = tablero[filaDestino][colDestino]; // Contenido de la casilla destino
    int diferenciaFila = filaDestino - filaOrigen; // Desplazamiento vertical
    int diferenciaColumna = colDestino - colOrigen; // Desplazamiento horizontal
    bool rutaLibre = true; // Indica si no hay piezas entre origen y destino
    bool puedeMatar = false; // Indica si la reina puede capturar en destino
    bool movimientoValidoReina = false; // Indica si el patrón de movimiento es de reina

    int pasoFila = 0;
    int pasoColumna = 0;
    int filaActual; // Fila mientras recorremos el camino
    int columnaActual; // Columna mientras recorremos el camino

    // Miramos que el movimiento sea horizontal, vertical o en diagonal
    if (diferenciaFila == 0 || diferenciaColumna == 0) {
        movimientoValidoReina = true;   // movimiento tipo torre
    }
    else if (diferenciaFila == diferenciaColumna || diferenciaFila == -diferenciaColumna) {
        movimientoValidoReina = true;   // movimiento tipo alfil
    }
    // Si no es ni recto ni diagonal, el movimiento no es válido para la reina
    if (!movimientoValidoReina) {
        rutaLibre = false;
    }
    else {
        // Calcular la dirección de movimiento en filas
        if (diferenciaFila > 0) pasoFila = 1;
        else if (diferenciaFila < 0) pasoFila = -1;

        // Calcular la dirección de movimiento en columnas
        if (diferenciaColumna > 0) pasoColumna = 1;
        else if (diferenciaColumna < 0) pasoColumna = -1;

        // Empezar a recorrer la ruta desde la casilla siguiente al origen
        filaActual = filaOrigen + pasoFila;
        columnaActual = colOrigen + pasoColumna;

        // Recorrer todas las casillas intermedias hasta llegar al destino(sin incluir destino)
        while (filaActual != filaDestino || columnaActual != colDestino) {
            // Si hay cualquier pieza en medio, la ruta no está libre
            if (tablero[filaActual][columnaActual] != '*') {
                rutaLibre = false;
                break;
            }
            // Avanzar una casilla más en la dirección calculada
            filaActual += pasoFila;
            columnaActual += pasoColumna;
        }
    }

    // Comprobar si puede matar
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

    // Movimiento final válido si el camino está libre y el destino está vacío o contiene una pieza rival que se puede capturar
    if (rutaLibre && (destino == '*' || puedeMatar)) {
        movimientoValido = true;
    }
}


