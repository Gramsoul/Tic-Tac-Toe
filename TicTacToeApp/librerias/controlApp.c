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
#include "archivos.h"

void inicializarApp(){
    srand(time(NULL));
    stJugador data_players_arr[100];
    int data_players_val = 0;
    char tablero[3][3];
    cargaDataBase(data_players_arr, &data_players_val);

    //maximizarConsola(); hay resoluciones en donde anda mal.

    int control = 1;
    do {
        control = 1; // ??? <- Se defaultea a 1 cada vez que se reinicia el ciclo
        int id_logged = menuLogin(data_players_arr, &data_players_val);

        if(id_logged != -1) { // id_logged -1 -> opcion 3 = salir
            rellenarTablero(tablero);
            controlApp(tablero, data_players_arr, &data_players_val, &id_logged, &control);
            // control = 0 -> salir de la cuenta
        }
    } while(control == 0) ;

    //finalizarApp(data_players_arr, data_players_val);
    // TESTEO
    //int a = 99, b = 1;
    //rellenarTablero(tablero);
    //controlApp(tablero, data_players_arr, data_players_val, &a, &b);
}

void controlApp(char tablero[3][3], stJugador data_players[], int *data_players_val, int *id_logged, int *control){

    int select = 0;
    int pos; // Variable para buscar posición en array

    ///JUGADORES DE TESTEO
    stJugador CPU = {
        0,
        "CPU",
        "TEST",
        "test@email.com",
        "0122",
        0,
        1,
        1
    };

    // Buscar el jugador logueado en el array
    stJugador Player1 = buscarPlayerLogged(data_players, *data_players_val, *id_logged);
    /*stJugador Player2 = {
        98,
        "Romina",
        "Gimenez",
        "email@email.com",
        "1234",
        0,
        1,
        1
    }; */
    ///

    /*  res recibe el id del jugador, hay que usar una
        funcion que busque el jugador en el array por el id
        y ese jugador es el que se utiliza para modoDeJego() */
    while(select != 5){
        select = seleccionModo();
        switch(select){
            case 1:
                system("cls");
                printf("\nIniciar sesion Player 2: \n");
                int id_logged_player2 = menuIniciarSesion(data_players, *data_players_val);
                stJugador Player2 = buscarPlayerLogged(data_players, *data_players_val, id_logged_player2);
                //No se guardan las stats de Player2, hay que modificar funcion de control datos
                mostrarTablero(tablero);
                modoDeJuego(&Player1, &Player2, tablero, 0, 0);
                rellenarTablero(tablero);
                resetApp(tablero);
                break;
            case 2:{
                int dif = -1;
                dif = seleccionarDificultad();
                mostrarTablero(tablero);
                modoDeJuego(&Player1, &CPU, tablero, -1, dif);
                rellenarTablero(tablero);
                resetApp(tablero);
                break;
            }
            case 3:
                mostrarEstadisticas(Player1);
                break;
            case 4:
                menuConfig(&Player1, data_players, data_players_val);
                // Actualizar el jugador en el array después de la configuración
                pos = buscarIDArr(data_players, *data_players_val, *id_logged);
                if(pos != -1) {
                    data_players[pos] = Player1;
                    guardarArr(data_players, *data_players_val);
                }
                break;
            case 5:
                centrarMensajeHorizontalmente("Saliendo...");
                *control = 0;
                break;
            case 6:
                select = 5;
                *id_logged = -1;
                break;
            default:
                printf("\nERROR: Elegir una opcion valida");
                break;
        }
    }

}

int seleccionarDificultad(){
    char menu[][30] = {
        "1 - Facil",
        "2 - Dificil"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);
    int opcion;
    scanf("%d", &opcion);

    return opcion;
}

void modoDeJuego(stJugador *player1, stJugador *player2, char tablero[3][3], int isCPU, int dificultad){
    int tTotal = 0, vic = 0, turno = 1;
    player1->partidasJugadas++;
    player2->partidasJugadas++;

    while(tTotal < 9 && !vic){
        if(turno){ accionesPorTurno(player1, tablero, &vic, 0, turno, 0); }
        else{ accionesPorTurno(player2, tablero, &vic, isCPU, turno, dificultad); }
        tTotal++;
        turno = 1 - turno;
    }
    if(!vic) {
            centrarMensajeHorizontalmente("Empate!.");
            player1->partidasEmpatadas++;
            player1->puntuacion++;
            player2->partidasEmpatadas++;
            player2->puntuacion++;
        //SE AGREGO LA PUNTUACION DE EMPATE.
    }
}

void accionesPorTurno(stJugador *player, char tablero[3][3], int *vic, int isCPU, int turno, int dificultad){
    char figura = figuraActual(turno);
    turnoJugador(isCPU, tablero, turno, dificultad);
    mostrarTablero(tablero);
    *vic = checkVictory(tablero, figura);
    victoria(*vic, player);
}

char figuraActual(int turno){ return (turno == 1)? 'X': 'O'; }

