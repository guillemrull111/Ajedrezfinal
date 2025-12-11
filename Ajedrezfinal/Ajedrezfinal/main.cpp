#include <iostream>
#include "Const.h"
#include "Tablero.h"

int main() {

	char tablero[FILA][COLUMNA];

	InicializarTablero(tablero);
	posicionFichas(tablero);
	ImprimirTablero(tablero);

	return 0;
}