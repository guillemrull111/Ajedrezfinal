#include <iostream>
#include "Const.h"

// Función para inicializar el tablero
void InicializarTablero(char tablero[FILA][COLUMNA]) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {
            tablero[i][j] = '*';
        }
    }
}

// Función para colocar las fichas en el tablero tanto arriba como abajo
void posicionFichas(char tablero[FILA][COLUMNA]) {
    // ARRIBA mayúsculas
    for (int i = 0; i < COLUMNA; i++) {
        tablero[1][i] = 'P';  
    }
    tablero[0][0] = tablero[0][7] = 'T';  
    tablero[0][1] = tablero[0][6] = 'H';
    tablero[0][2] = tablero[0][5] = 'B';
    tablero[0][3] = 'Q';
    tablero[0][4] = 'K';

    // Abajo minúsculas
    for (int i = 0; i < COLUMNA; i++) {
        tablero[6][i] = 'p';  
    }
    tablero[7][0] = tablero[7][7] = 't';  
    tablero[7][1] = tablero[7][6] = 'h';
    tablero[7][2] = tablero[7][5] = 'b';
    tablero[7][3] = 'q';
    tablero[7][4] = 'k';
}

// Funcion para imprimir el tablero, aqui tambien ponemos para que salgan los numeros de las filas y las columnas
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
