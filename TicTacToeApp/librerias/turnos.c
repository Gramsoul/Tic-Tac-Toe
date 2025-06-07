#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "turnos.h"
#include "Jugador.h"



void turnoJugador(stJugador jugador, int pos, char tablero[3][3]){
    int isCPU = 0;
///Cuan agrege ID a los player, en lugar de pos -1, poner que si el id es 00 es CPU
    if(pos == -1) {
        isCPU = 1;
        pos = pedirPosicion(isCPU);
    } else { pos = pedirPosicion(isCPU); }

    buscarPosicion(jugador, pos, tablero, isCPU);

}
/*
void buscarPosicion(stJugador jugador, int pos, char tablero[3][3], int isCPU){  ///Antigua funcion de posicion
    int i = 0, j = 0, f = 0;

    while(!f){
        int count = 1;
        for(i=0; i<3 && !f; i++){
            for(j=0; j<3 && !f; j++){
                if(pos == count){
                    if(tablero[i][j] == ' '){
                        tablero[i][j] = jugador.figura;
                        f = 1;
                    }
                    else {
                        pos = pedirPosicion(isCPU);
                    }
                } else{ count++; }
            }
        }
    }
}
*/

void buscarPosicion(stJugador jugador, int pos, char tablero[3][3], int isCPU){
    int f = 0;

    while(!f){
        int fila    = (pos - 1) /3;
        int columna = (pos - 1) %3;

        if(tablero[fila][columna] == ' '){
            tablero[fila][columna] = jugador.figura;
            f = 1;
        }
        else {
            pos = pedirPosicion(isCPU);
        }
    }
}

int pedirPosicion(int isCpu){
    int f = 0, pos = 0;

    if(isCpu){ pos = rand()%9+1; }
    else {
        printf("\nSeleccione posicion 1-9..\n");
        while(!f){
            scanf("%d", &pos);
            if(pos > 0 && pos < 10){
                f = 1;
            } else { printf("\nSeleccion incorrecta ingrese entre 1-9..\n"); }
        }

    }

    return pos;
}
