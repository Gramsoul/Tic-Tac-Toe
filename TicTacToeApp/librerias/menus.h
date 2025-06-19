#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "Jugador.h"

void maximizarConsola();
void resetApp();
void gotoxy(int x, int y);
void obtenerTamConsola(int *ancho, int *alto);
void menuPrincipal(int isAdmin);
void menuBasico();
void menuAdmin();
void menuCentrado(char options[][30], int cantidad);
void centrarMensajeHorizontalmente(char mensaje[]);
void resetApp(char tablero[3][3]);
int menuLogin(stJugador data_players[], int data_players_val);
int menuIniciarSesion(stJugador data_players[], int data_players_val);
int seleccionModo();
int contarPalabra(char arr[][30], int v);
int dondeEstaY();

#endif // MENUS_H_INCLUDED
