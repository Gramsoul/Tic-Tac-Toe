#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "turnos.h"
#include "Jugador.h"
#include "menus.h"



void turnoJugador(stJugador jugador, int pos, char tablero[3][3]){
    int isCPU = 0;
///Cuan agrege ID a los player, en lugar de pos -1, poner que si el id es 00 es CPU
    if(pos == -1) {
        isCPU = 1;
        pos = pedirPosicion(isCPU, tablero, jugador);
    } else { pos = pedirPosicion(isCPU, tablero, jugador); }

    buscarPosicion(jugador, pos, tablero, isCPU);

}

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
            pos = pedirPosicion(isCPU, tablero, jugador);
        }
    }
}

int pedirPosicion(int isCpu, char tablero[3][3], stJugador jugador){
    int f = 0, pos = 0;

    if(isCpu){ pos = difUno(tablero, jugador); }
    else {
        char mensaje[] = "Seleccione una posicion desde 1 a 9.";
        centrarMensajeHorizontalmente(mensaje);
        while(!f){
            scanf("%d", &pos);
            if(pos > 0 && pos < 10){
                f = 1;
            } else {
                char selIn[] = "Seleccion incorrecta ingrese entre 1-9..";
                centrarMensajeHorizontalmente(selIn);
            }
        }

    }

    return pos;
}

int difUno(){ return rand()% 9+1; }

int difDos(char tablero[3][3], stJugador jugador){
    int pos = difUno(); //en caso de que falle, tira un random

    //FILAS
    for(int i=0; i<3; i++){
        int vacio = -1;
        int iguales = 0;

        for(int j=0; j<3; j++){
            if(tablero[i][j] == jugador.figura)
                iguales++;
            else if(tablero[i][j] == ' ')
                vacio = j;
        }

        if(iguales == 2 && vacio != -1){
            pos = (i*3) + vacio + 1; //cambia las coordenadas [i][j] a 1-9
        }
    } 

    //COLUMNAS
    for(int i=0; i<3; i++){
        int vacio = -1;
        int iguales = 0;

        for(int j=0; j<3; j++){
            if(tablero[j][i] == jugador.figura)
                iguales++;
            else if(tablero[j][i] == ' ')
                vacio = j;
        }

        if(iguales == 2 && vacio != -1)
            pos = (vacio * 3) + i + 1; //cambia las coordenadas [i][j] a 1-9
    } 

    //DIAGONAL PRINCIPAL
    int vacio = -1, iguales = 0;
    for(int i=0; i<3; i++){
        if(tablero[i][i] == jugador.figura){
            iguales++;
        }else if(tablero[i][i] == ' '){
            vacio = i;
        }
    }

    if(iguales == 2 && vacio != -1)
        pos = vacio*3 + vacio + 1;

    //DIAGONAL SECUNDARIA
    vacio = -1; iguales = 0;
    for(int i=0; i<3; i++){
        if(tablero[i][2-i] == jugador.figura){
            iguales++;
        }else if(tablero[i][2-i] == ' ')
            vacio = i;
    }

    if(iguales == 2 && vacio != -1)
        pos = (vacio * 3) + (2 - vacio) + 1;

    return pos;
}