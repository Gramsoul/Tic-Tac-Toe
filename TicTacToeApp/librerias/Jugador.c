#include <stdio.h>
#include <string.h>
#include "Jugador.h"

void mostrarJugador(stJugador data){
    printf("Nombre -> %s %s\n", data.nombre, data.apellido);
    printf("Email -> %s\n", data.email);
    printf("pass -> %s\n", data.contra);
    printf("Figura -> %c\n", data.figura);
    printf("--------------------------------\n");
}

void mostrarArrJugadores(stJugador arr[], int v){
    for(int i=0; i<v; i++){ mostrarJugador(arr[i]); }
}

stJugador crearJugador(){
    stJugador player;

    fflush(stdin);
    printf("Primer nombre:\n");
    gets(player.nombre);

    fflush(stdin);
    printf("Apelldo:\n");
    gets(player.apellido);

    fflush(stdin);
    printf("Figura:\n");

    emailValido(&player);
    passwordCorrect(&player);

    return player;
}
void emailValido(stJugador *player){
    int f = 0;
    printf("Email:\n");

    while(!f){
        char email[40];
        fflush(stdin);

        gets(email);
        char *arroba = strchr(email, '@');
        char *punto = strchr(email, '.');

        if(arroba && punto && punto > arroba){
            strcpy(player->email, email);
            f = 1;
        }
        else {
            printf("Email invalido, intente nuevamente..\n");
        }

    }
}

void passwordCorrect(stJugador *player){
    int f = 0;
   while(!f){
        char aux[50], aux2[50];
        fflush(stdin);
        printf("Password:\n");
        gets(aux);
        fflush(stdin);
        printf("Repetir password:\n");
        gets(aux2);

        if(strcmp(aux, aux2) == 0){
            strcpy(player->contra, aux);
            f = 1;
        }
        else { printf("Las contraseñas no coinciden, intente nuevamente..\n"); }
    }
}
