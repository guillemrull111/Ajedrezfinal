#pragma once
#include "Const.h"

void MovimientoPeon(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);
void MovimientoTorre(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);
void MovimientoAlfil(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);
void MovimientoCaballo(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);
void MovimientoRey(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);
void MovimientoReina(char tablero[FILA][COLUMNA], int filaOrigen, int colOrigen, int filaDestino, int colDestino, bool turno, bool& movimientoValido);