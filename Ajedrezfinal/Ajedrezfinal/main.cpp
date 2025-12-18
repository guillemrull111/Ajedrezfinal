#include <iostream>
#include "Const.h"
#include "Tablero.h"
#include "Gameplay.h"


int main() {

	char tablero[FILA][COLUMNA];

	InicializarTablero(tablero);
	posicionFichas(tablero);
	ImprimirTablero(tablero);
	MovimientoFichas(tablero);

	return 0;
}