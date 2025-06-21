#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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
    srand(time(NULL));
    stJugador data_players_arr[100];
    int data_players_val = 0;
    char tablero[3][3];
    cargaDataBase(data_players_arr, &data_players_val);

    //maximizarConsola();
    int control = 1;
    do {
        control = 1;
        int id_logged = menuLogin(data_players_arr, data_players_val);

        if(id_logged != -1) { // id_logged -1 -> opcion 3 = salir
            rellenarTablero(tablero);
            controlApp(tablero, data_players_arr, data_players_val, &id_logged, &control);
            // control = 0 -> salir de la cuenta
        }
    } while(control == 0) ;

    finalizarApp(data_players_arr, data_players_val);
}

void controlApp(char tablero[3][3], stJugador data_players[], int data_players_val, int *id_logged, int *control){

    int select = 0;

    ///JUGADORES DE TESTEO
    stJugador CPU = {
        0,
        "CPU",
        "TEST",
        "test@email.com",
        "0122",
        'X',
        0,
        1,
        1
    };
    stJugador Player1 = {
        99,
        "Gonzalo",
        "Gallego",
        "email@email.com",
        "1234",
        'G',
        0,
        1,
        1
    };
    stJugador Player2 = {
        98,
        "Romina",
        "Gimenez",
        "email@email.com",
        "1234",
        'R',
        0,
        1,
        1
    };
    data_players[97] = Player1;
    data_players[98] = Player2;
    data_players[99] = CPU;
    ///

    Player1 = buscarPlayerLogged(data_players, data_players_val, *id_logged);

    /*  res recibe el id del jugador, hay que usar una
        funcion que busque el jugador en el array por el id
        y ese jugador es el que se utiliza para modoDeJego() */
    while(select != 3){
        select = seleccionModo();
        switch(select){
            case 1:
                mostrarTablero(tablero);
                modoDeJuego(Player1, Player2, tablero, 0);
                resetApp(tablero);
                break;
            case 2:
                mostrarTablero(tablero);
                modoDeJuego(Player1, CPU, tablero, -1);
                resetApp(tablero);
                break;
            case 3:
                //menuPrincipal(0); No creo que sea necesaria esta pantalla
                // 3 -> Salir. Volver a llamar inicializar app? O hacer un ciclo mientras op != 4
                centrarMensajeHorizontalmente("Saliendo...");
                *control = 0;
                break;
            case 4:
                menuConfig(&Player1);
                break;
            case 5:
                select = 3;
                *id_logged = -1;
                break;
            default:
                printf("\nERROR: Elegir una opcion valida");
                break;
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
    if(!vic) { centrarMensajeHorizontalmente("Victoria!."); }
}

void accionesPorTurno(stJugador player, char tablero[3][3], int *vic, int isCPU){
    turnoJugador(player, isCPU, tablero);
    mostrarTablero(tablero);
    *vic = checkVictory(tablero, player.figura);
    victoria(*vic, player.nombre);
}
