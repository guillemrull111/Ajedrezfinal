#include <iostream>
#include "Const.h"
#include "tablero.h"


void MovimientoFichas(char tablero[FILA][COLUMNA]) {

	int filaOrigen, colOrigen;
	int filaDestino, colDestino;
	bool juegoAcabado = false;
	bool turno = false;

	while (!juegoAcabado) {
		while (turno == false) {

			std::cout << "Fila de la ficha a mover: ";
			std::cin >> filaOrigen;
			std::cout << "Columna de la ficha a mover: ";
			std::cin >> colOrigen;

			if (tablero[filaOrigen][colOrigen] == 'p') {

				std::cout << "Fila destino: ";
				std::cin >> filaDestino;
				std::cout << "Columna destino: ";
				std::cin >> colDestino;

				
				tablero[filaOrigen][colOrigen] = '*';
				tablero[filaDestino][colDestino] = 'p';

			}
			else {
				std::cout << "No hay ficha en esa posicion.\n";
			}
			system("cls");
			ImprimirTablero(tablero);
		}
		turno = true;

		while (turno == true)
		{
			std::cout << "Fila de la ficha a mover: ";
			std::cin >> filaOrigen;
			std::cout << "Columna de la ficha a mover: ";
			std::cin >> colOrigen;

			if (tablero[filaOrigen][colOrigen] == 'p') {

				std::cout << "Fila destino: ";
				std::cin >> filaDestino;
				std::cout << "Columna destino: ";
				std::cin >> colDestino;

		
				tablero[filaOrigen][colOrigen] = '*';
				tablero[filaDestino][colDestino] = 'p';

			}
			else {
				std::cout << "No hay ficha en esa posicion.\n";
			}
			system("cls");
			ImprimirTablero(tablero);
		}
		turno = false;
	}
}	
