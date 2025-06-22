#include <windows.h>
#include "Jugador.h"
#include "controlDatos.h"
#include "archivos.h"
#include "menus.h"


void cargaDataBase(stJugador data_players_arr[], int *data_players_val){
    cargarArchivoArr(data_players_arr, data_players_val, DATA_JUGADORES);
}

void finalizarApp(stJugador arr[], int val_arr){
    guardarArr(arr, val_arr);
    centrarMensajeHorizontalmente("Guardando archivos..");
    Sleep(800);
    system("cls");
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}  // Limpia el stdin
}
