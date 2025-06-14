#include "Jugador.h"
#include "controlDatos.h"
#include "archivos.h"


void cargaDataBase(char data_players_arr[], int *data_players_val){

    ///MOVER LOS ARR y VAL A LA APP DE CONTROL O LA FUNCION MAS "GLOBAL". LUEGO HACER QUE SE RECIVA POR PARAMETRO

    cargarArchivoArr(data_players_arr, &data_players_val, DATA_JUGADORES);
    //mostrarArrJugadores(data_players_arr, data_players_val);

}

void finalizarApp(stJugador arr[], int val_arr){
    guardarArr(arr, val_arr, DATA_JUGADORES);
}

