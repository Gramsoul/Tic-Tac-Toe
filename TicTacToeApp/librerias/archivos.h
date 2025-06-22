#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define DATA_JUGADORES "data/dataJugadores.dat"

#include "Jugador.h"
#include <stdio.h>

int cantEntidades(char name[], size_t tam);
void cargarArchivo();
void cargarArchivoArr(stJugador data[], int *i, const char name[]);
void guardarArr(stJugador data[], int v);
void guardarJugador(stJugador data, const char name[]);
void guardarNuevoJugadorArr(stJugador data[], int *val_data, stJugador *nuevoJugador);


#endif // ARCHIVOS_H_INCLUDED
