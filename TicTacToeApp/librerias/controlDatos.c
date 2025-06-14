#include "Jugador.h"
#include "controlDatos.h"
#include "archivos.h"


void cargaDataBase(stJugador data_players_arr[], int *data_players_val){
    cargarArchivoArr(data_players_arr, data_players_val, DATA_JUGADORES);
}

void finalizarApp(stJugador arr[], int val_arr){
    guardarArr(arr, val_arr, DATA_JUGADORES);
}

