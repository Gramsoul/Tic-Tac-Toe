#ifndef TURNOS_H_INCLUDED
#define TURNOS_H_INCLUDED

#include "Jugador.h"

void turnoJugador(stJugador jugador, int pos, char tablero[3][3]);
void buscarPosicion(stJugador jugador,int pos, char tablero[3][3], int isCPU);
int pedirPosicion(int isCPU, char tablero[3][3], stJugador jugador);
int difUno();
int difDos(char tablero[3][3], char figuraPropia, char figuraRival);
int difTes(char tablero[3][3]);

int buscarDosIguales(char tablero[3][3], char figura);


#endif // TURNOS_H_INCLUDED
