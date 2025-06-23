#ifndef TURNOS_H_INCLUDED
#define TURNOS_H_INCLUDED

#include "Jugador.h"

void turnoJugador(int pos, char tablero[3][3], int turno, int dificultad);
void buscarPosicion(int pos, char tablero[3][3], int isCPU, int turno, int dificultad);
int pedirPosicion(int isCPU, char tablero[3][3], int dificultad);
int difUno();
int difDos(char tablero[3][3], char figuraPropia, char figuraRival);
int difTes(char tablero[3][3]);

int buscarDosIguales(char tablero[3][3], char figura);


#endif // TURNOS_H_INCLUDED
