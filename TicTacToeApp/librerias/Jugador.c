#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "Jugador.h"
#include "controlDatos.h"
#include "login.h"
#include "menus.h"

void mostrarJugador(stJugador data){
    printf("Nombre -> %s %s\n", data.nombre, data.apellido);
    printf("Email -> %s\n", data.email);
    printf("--------------------------------\n");
}

void mostrarJugadorAdmin(stJugador data){
    printf("Nombre -> %s %s\n", data.nombre, data.apellido);
    printf("Email -> %s\n", data.email);
    printf("pass -> %s\n", data.contra);
    printf("ID -> %d\n", data.id);
    printf("Cuenta activa -> %d\n", data.cuentaActiva);
    printf("Admin -> %d\n", data.isAdmin);
    printf("--------------------------------\n");
}

void mostrarPuntuaciones(stJugador arr[], int val){
    for(int i=0; i<val; i++){
        printf("%s %s\n", arr[i].nombre, arr[i].apellido);
        printf("Puntuacion total -> %d\n", arr[i].puntuacion);
        printf("--------------------------");
    }
}

void mostrarArrJugadores(stJugador arr[], int v){
    for(int i=0; i<v; i++){
        if(arr[i].cuentaActiva) { mostrarJugador(arr[i]); }
    }
}
void mostrarArrJugadoresAdmin(stJugador arr[], int v){
    for(int i=0; i<v; i++){
        if(arr[i].cuentaActiva) { mostrarJugadorAdmin(arr[i]); }
    }
}

stJugador crearJugador(int cant_id){
    system("cls");
    stJugador player;

    limpiarBuffer();
    centrarMensajeHorizontalmente("Primer nombre: ");
    gets(player.nombre);

    centrarMensajeHorizontalmente("Apellido: ");
    gets(player.apellido);

    centrarMensajeHorizontalmente("Email: ");
    emailValido(&player);

    passwordCorrect(&player);
    player.id = cant_id+1;
    player.puntuacion = 0;
    player.cuentaActiva = 1;

    return player;
}

void emailValido(stJugador *player){
    int flag = 0;

    while(!flag){
        char email[40];
        fflush(stdin);

        fgets(email, sizeof(email), stdin);
        toUpperString(email);
        char *arroba = strchr(email, '@');
        char *punto = strchr(email, '.');

        if(arroba && punto && punto > arroba){
            strcpy(player->email, email);
            flag = 1;
        }
        else {
            centrarMensajeHorizontalmente("Email:");
        }

    }
}
void toUpperString(char *str){
    for(int i=0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
}
void passwordCorrect(stJugador *player){
    int f = 0;
   while(!f){
        char aux[50], aux2[50];
        fflush(stdin);
        printf("Password:\n");
        ocultarPassw(aux, sizeof(aux));
        fflush(stdin);
        printf("Repetir password:\n");
        ocultarPassw(aux2, sizeof(aux2));

        if(strcmp(aux, aux2) == 0){
            strcpy(player->contra, aux);
            f = 1;
        }
        else { printf("Las contrasenias no coinciden, intente nuevamente..\n"); }
    }
}

void deshabilitarID(stJugador *data){ data->cuentaActiva = 0; }

stJugador buscarPlayerLogged(stJugador data_players[], int data_players_val, int id_logged) {
    stJugador aux;

    for(int i=0; i<data_players_val; i++) {
        if(data_players[i].id == id_logged) {
            aux = data_players[i];
        }
    }

    return aux;
}




