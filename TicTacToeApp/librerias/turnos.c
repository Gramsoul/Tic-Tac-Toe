#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "turnos.h"
#include "Jugador.h"
#include "menus.h"
#include "controApp.h"



void turnoJugador(int pos, char tablero[3][3], int turno, int dificultad){
    int isCPU = 0;

    if(pos == -1) {
        isCPU = 1;
        pos = pedirPosicion(isCPU, tablero, dificultad);
    } else { pos = pedirPosicion(isCPU, tablero, 0); }

    buscarPosicion(pos, tablero, isCPU, turno, dificultad);

}


void buscarPosicion(int pos, char tablero[3][3], int isCPU, int turno, int dificultad){
    int f = 0;
    char figura = figuraActual(turno);

    while(!f){
        int fila    = (pos - 1) /3;
        int columna = (pos - 1) %3;

        if(tablero[fila][columna] == ' '){
            tablero[fila][columna] = figura;
            f = 1;
        }
        else {
            pos = pedirPosicion(isCPU, tablero, dificultad);
        }
    }
}

int pedirPosicion(int isCpu, char tablero[3][3], int dificultad){
    int f = 0, pos = 0;

    if(isCpu){
            if(dificultad == 2){ pos = difDos(tablero, 'O', 'X'); }
            else { pos = difUno(); }
    }
    else { centrarMensajeHorizontalmente("Seleccione una posicion desde 1 a 9.");
        while(!f){
            scanf("%d", &pos);
            if(pos > 0 && pos < 10){
                f = 1;
            } else { centrarMensajeHorizontalmente("Seleccion incorrecta ingrese entre 1-9.."); }
        }

    }

    return pos;
}

int difUno(){ return rand()% 9+1; }

int difDos(char tablero[3][3], char figuraPropia, char figuraRival){

    int pos = buscarDosIguales(tablero, figuraPropia);
    if(pos == -1){ pos = buscarDosIguales(tablero, figuraRival); }
    if(pos == -1){
        if(tablero[1][1] == ' '){ pos = 5; } //en caso de que falle, tira un random
        else{ pos = difUno(); }
    }

    return pos;
}

int buscarDosIguales(char tablero[3][3], char figura){
    int pos = -1;
    int vacio, iguales;

    //FILAS
    for(int i=0; i<3 && pos == -1; i++){
        vacio = -1;
        iguales = 0;

        for(int j=0; j<3; j++){
            if(tablero[i][j] == figura)
                iguales++;
            else if(tablero[i][j] == ' ')
                vacio = j;
        }

        if(iguales == 2 && vacio != -1){
            pos = (i*3) + vacio + 1; //cambia las coordenadas [i][j] a 1-9
        }
    }

    //COLUMNAS
    for(int i=0; i<3 && pos == -1; i++){
        vacio = -1;
        iguales = 0;
        for(int j=0; j<3; j++){
            if(tablero[j][i] == figura)
                iguales++;
            else if(tablero[j][i] == ' ')
                vacio = j;
        }

        if(iguales == 2 && vacio != -1)
            pos = (vacio * 3) + i + 1; //cambia las coordenadas [i][j] a 1-9
    }

    //DIAGONAL PRINCIPAL
    if(pos == -1){
        vacio = -1;
        iguales = 0;
        for(int i=0; i<3; i++){
            if(tablero[i][i] == figura){
                iguales++;
            }else if(tablero[i][i] == ' '){
                vacio = i;
            }
        }

        if(iguales == 2 && vacio != -1)
            pos = vacio*3 + vacio + 1; //cambia las coordenadas [i][j] a 1-9
    }

    //DIAGONAL SECUNDARIA
    if(pos == -1){
        vacio = -1; iguales = 0;
        for(int i=0; i<3; i++){
            if(tablero[i][2-i] == figura){
                iguales++;
            }else if(tablero[i][2-i] == ' ')
                vacio = i;
        }

        if(iguales == 2 && vacio != -1)
            pos = (vacio * 3) + (2 - vacio) + 1; //cambia las coordenadas [i][j] a 1-9
    }

    return pos;
}
