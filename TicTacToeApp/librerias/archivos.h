#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#define DATAJ "dataJugadores.dat"

#include "Jugador.h"

int cantEntidades(FILE *file, size_t tam);
void cargarArchivo(const char name[]);
void cargarArchivoArr(stJugador data[], int *i, const char name[]);
void guardarArr(stJugador data[], int v, const char name[]);
void guardarJugador(stJugador data, const char name[]);


#endif // ARCHIVOS_H_INCLUDED
