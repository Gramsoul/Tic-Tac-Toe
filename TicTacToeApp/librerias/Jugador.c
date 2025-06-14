#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Jugador.h"
#include "controlDatos.h"
#include "login.h"

void mostrarJugador(stJugador data){
    printf("Nombre -> %s %s\n", data.nombre, data.apellido);
    printf("Email -> %s\n", data.email);
    printf("Figura -> %c\n", data.figura);
    printf("--------------------------------\n");
}

void mostrarJugadorAdmin(stJugador data){
    printf("Nombre -> %s %s\n", data.nombre, data.apellido);
    printf("Email -> %s\n", data.email);
    printf("pass -> %s\n", data.contra);
    printf("Figura -> %c\n", data.figura);
    printf("ID -> %d\n", data.id);
    printf("Cuenta activa -> %d\n", data.cuentaActiva);
    printf("Admin -> %d\n", data.isAdmin);
    printf("--------------------------------\n");
}

void mostrarArrJugadores(stJugador arr[], int v){
    for(int i=0; i<v; i++){
        if(arr[i].cuentaActiva) { mostrarJugador(arr[i]); }
    }
}

stJugador crearJugador(int cant_id){
    stJugador player;

    fflush(stdin);
    printf("Primer nombre:\n");
    gets(player.nombre);

    fflush(stdin);
    printf("Apelldo:\n");
    gets(player.apellido);

    fflush(stdin);
    printf("Figura:\n");
    player.figura = getch();

    emailValido(&player);
    passwordCorrect(&player);
    player.id = cant_id+1;
    player.cuentaActiva = 1;

    return player;
}

void emailValido(stJugador *player){
    int flag = 0;

    while(!flag){
        char email[40];
        fflush(stdin);

        gets(email);
        char *arroba = strchr(email, '@');
        char *punto = strchr(email, '.');

        if(arroba && punto && punto > arroba){
            strcpy(player->email, email);
            flag = 1;
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
        ocultarPassw(aux, sizeof(aux));
        fflush(stdin);
        printf("Repetir password:\n");
        ocultarPassw(aux2, sizeof(aux2));

        if(strcmp(aux, aux2) == 0){
            strcpy(player->contra, aux);
            f = 1;
        }
        else { printf("Las contraseñas no coinciden, intente nuevamente..\n"); }
    }
}

void deshabilitarID(stJugador data){ data.cuentaActiva = 0; }
