#include <iostream>
#include "Const.h"

void MovimientoFichas(char tablero[FILA][COLUMNA]) {

	int FilafichaUsuario;
	int ColumnafichaUsuario;

	
	std::cout << "Escoje la fils de la ficha que quieres mover: ";
	std::cin >> FilafichaUsuario;

	std::cout << "Escoje la columna de la ficha que quieres mover: ";
	std::cin >> ColumnafichaUsuario;


	std::cout << "\nDonde lo quieres mover: ";
	std::cin >> posicionMover;
	if (tablero[FilafichaUsuario][ColumnafichaUsuario])
	{

	}
}