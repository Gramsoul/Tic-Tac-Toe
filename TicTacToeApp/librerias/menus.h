#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "Jugador.h"

void menuCentrado(char options[][30], int cantidad);
void centrarMensajeHorizontalmente(char mensaje[]);
void maximizarConsola();
void gotoxy(int x, int y);
void obtenerTamConsola(int *ancho, int *alto);
int contarPalabra(char arr[][30], int v);
int seleccionModo();
int dondeEstaY();
void resetApp(char tablero[3][3]);

int menuLogin(stJugador data_players[], int data_players_val);
int menuIniciarSesion(stJugador data_players[], int data_players_val);
void menuConfig(stJugador *User);
void menuConfigUser(stJugador *User);
void menuConfigAdmin(stJugador *Admin);
void adminBorrarCuenta(stJugador *Admin);
void modificarUsuario(stJugador *User);
void modificarPassword(stJugador *User);
void menuAdmin(stJugador data[], int val);



#endif // MENUS_H_INCLUDED
