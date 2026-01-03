// tablero.cpp - COPIA COMPLETO
#include <iostream>
#include "Const.h"

void InicializarTablero(char tablero[FILA][COLUMNA]) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {
            tablero[i][j] = '*';
        }
    }
}

void posicionFichas(char tablero[FILA][COLUMNA]) {
    // ARRIBA todo mayúsculas (visual fila8+7)
    for (int i = 0; i < COLUMNA; i++) {
        tablero[1][i] = 'P';  // Peones mayúsculas visual fila7 (array1)
    }
    tablero[0][0] = tablero[0][7] = 'T';  // ← CAMBIO mayúsculas
    tablero[0][1] = tablero[0][6] = 'H';
    tablero[0][2] = tablero[0][5] = 'B';
    tablero[0][3] = 'Q';
    tablero[0][4] = 'K';

    // ABAJO todo minúsculas (visual fila2+1)
    for (int i = 0; i < COLUMNA; i++) {
        tablero[6][i] = 'p';  // Peones minúsculas visual fila2 (array6)
    }
    tablero[7][0] = tablero[7][7] = 't';  // Ya correcto
    tablero[7][1] = tablero[7][6] = 'h';
    tablero[7][2] = tablero[7][5] = 'b';
    tablero[7][3] = 'q';
    tablero[7][4] = 'k';
}

void ImprimirTablero(char tablero[FILA][COLUMNA]) {
    std::cout << "  ";
    for (int j = 0; j < COLUMNA; ++j) {
        std::cout << j + 1 << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < FILA; i++) {
        std::cout << FILA - i << ' ';
        for (int j = 0; j < COLUMNA; j++) {
            std::cout << tablero[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
