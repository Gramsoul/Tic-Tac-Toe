#ifndef CONTROAPP_H_INCLUDED
#define CONTROAPP_H_INCLUDED
#include "Jugador.h"

void controlApp(char tablero[3][3], stJugador data_players[], int *data_players_val, int *id_logged, int *control);
void inicializarApp();
void accionesPorTurno(stJugador *player, char tablero[3][3], int *vic, int isCPU, int turno, int dificultad);
void modoDeJuego(stJugador *player1, stJugador *player2, char tablero[3][3], int isCPU, int dificultad);
char figuraActual(int turno);
int seleccionarDificultad();
#endif // CONTROAPP_H_INCLUDED
