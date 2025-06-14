#include <time.h>
#include <stdio.h>
#include <windows.h>
#include "tablero.h"
#include "controApp.h"
#include "Jugador.h"
#include "victory.h"
#include "menus.h"
#include "turnos.h"
#include "login.h"
#include "controlDatos.h"


void inicializarApp(){
    stJugador data_players_arr[100];
    int data_players_val = 0;
    int isAdmin = 1;///ESTA FUNCION LUEGO DEBE RECIBIR ISDAMIN POR PARAMETRO.

    maximizarConsola();
    //menuPrincipal(isAdmin);
    //cargaDataBase(data_players_arr, &data_players_val);

    char tablero[3][3];
    rellenarTablero(tablero);
    controlApp(tablero);
    //login(data_players, vData_players);

}

void controlApp(char tablero[3][3]){

    int select = 0;

    ///JUGADORES DE TESTEO
    stJugador CPU = {0, "CPU", "PC", "email@gmail.com", "1234", 'X', 1, 0};
    stJugador Player1 = {1, "Gonzalo", "Gallego", "email@gmail.com", "0122", 'G', 1, 1};
    stJugador Player2 = {2, "Romina", "Gimenez", "email@gmail.com", "1234", 'R', 1, 0};
    ///

    while(select != 3){
        select = seleccionModo();
        switch(select){
            case 1: {
                mostrarTablero(tablero);
                modoDeJuego(Player1, Player2, tablero, 0);
                resetApp();
            break;}
            case 2: {
                mostrarTablero(tablero);
                modoDeJuego(Player1, Player2, tablero, -1);
                resetApp();
            break;}
            case 3: {
                menuPrincipal(0);
            break;}
        }
    }

}


void modoDeJuego(stJugador player1, stJugador player2, char tablero[3][3], int isCPU){
    int tTotal = 0, vic = 0, turno = 1;

    while(tTotal < 9 && !vic){
        if(turno){ accionesPorTurno(player1, tablero, &vic, 0); }
        else{ accionesPorTurno(player2, tablero, &vic, isCPU); }
        tTotal++;
        turno = 1 - turno;
    }
    if(!vic) { printf("EMPATE!\n"); }
}

void accionesPorTurno(stJugador player, char tablero[3][3], int *vic, int isCPU){
    turnoJugador(player, isCPU, tablero);
    mostrarTablero(tablero);
    *vic = checkVictory(tablero, player.figura);
    victoria(*vic, player.nombre);
}
