#pragma once
#include "Const.h"
#include "Movimiento.h"

void BuscarRey(char tablero[FILA][COLUMNA], char rey, int& fila, int& col);
void ComprobarJaque(char tablero[FILA][COLUMNA], bool turno, bool& enJaque);
void ComprobarJaqueYMate(char tablero[FILA][COLUMNA], bool turno, bool& enJaque, bool& jaqueMate);