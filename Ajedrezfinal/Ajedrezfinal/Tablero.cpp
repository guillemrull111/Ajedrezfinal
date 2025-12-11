#include <iostream>
#include "Const.h"

void InicializarTablero(char tablero[FILA][COLUMNA]) {
	int numero = 0;
	for (int i = 0; i < COLUMNA; i++)
	{
		std::cout << numero << ' ';
		numero++;
		
	}
	std::cout << std::endl;
	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			tablero[i][j] = '*';
		}

	}
}

void posicionFichas(char tablero[FILA][COLUMNA]) {
	for (int i = 0; i < FILA; i++)
	{
		tablero[1][i] = 'p';
		tablero[6][i] = 'P';
	}
	tablero[0][0] = tablero[0][7] = 't';
	tablero[0][1] = tablero[0][6] = 'h';
	tablero[0][2] = tablero[0][5] = 'b';
	tablero[0][3] = 'q';
	tablero[0][4] = 'k';


	tablero[7][0] = tablero[7][7] = 'T';
	tablero[7][1] = tablero[7][6] = 'H';
	tablero[7][2] = tablero[7][5] = 'B';
	tablero[7][3] = 'Q';
	tablero[7][4] = 'K';
}

void ImprimirTablero(char tablero[FILA][COLUMNA]) {
	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++) {
			std::cout << tablero[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

