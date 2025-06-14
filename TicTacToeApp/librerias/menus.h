#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

void maximizarConsola();
void resetApp();
int seleccionModo();

void menuPrincipal(int isAdmin);
void menuBasico();
void menuAdmin();
void gotoxy(int x, int y);
void obtenerTamConsola(int *ancho, int *alto);
void menuCentrado(char options[][30], int cantidad);
int contarPalabra(char arr[][30], int v);
int dondeEstaY();
void centrarMensajeHorizontalmente(char mensaje[]);

#endif // MENUS_H_INCLUDED
