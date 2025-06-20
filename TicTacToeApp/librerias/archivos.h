#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define DATA_JUGADORES "data/dataJugadores.dat"

#include "Jugador.h"
#include <stdio.h>

int cantEntidades(char name[], size_t tam);
void cargarArchivo(const char name[]);
void cargarArchivoArr(stJugador data[], int *i, const char name[]);
void guardarArr(stJugador data[], int v, const char name[]);
void guardarJugador(stJugador data, const char name[]);


#endif // ARCHIVOS_H_INCLUDED
