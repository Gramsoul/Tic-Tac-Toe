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
    printf("puntuacion -> %d\n", data.puntuacion);
    printf("ID -> %d\n", data.id);
    printf("Cuenta activa -> %d\n", data.cuentaActiva);
    printf("Admin -> %d\n", data.isAdmin);
    printf("--------------------------------\n");
}

void mostrarPuntuaciones(stJugador arr[], int val){
    for(int i=0; i<val; i++){
        printf("%s %s\n", arr[i].nombre, arr[i].apellido);
        printf("Puntuacion total -> %d\n", arr[i].puntuacion);
        printf("--------------------------\n");
    }
}
void mostrarPuntuacionesAdm(stJugador arr[], int val){
    for(int i=0; i<val; i++){
        printf("%s %s\n", arr[i].nombre, arr[i].apellido);
        printf("Puntuacion total -> %d\n", arr[i].puntuacion);
        printf("ID -> %d\n", arr[i].id);
        printf("--------------------------\n");
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

    do {
        centrarMensajeHorizontalmente("Primer nombre: ");
        fgets(player.nombre, sizeof(player.nombre), stdin);
        player.nombre[strcspn(player.nombre, "\n")] = 0;   /// quitar '\n'

        if (strlen(player.nombre) == 0) {
            printf("El nombre no puede estar vacío. Intente nuevamente.\n");
        }
    } while (strlen(player.nombre) == 0);

    do {
        centrarMensajeHorizontalmente("Apellido: ");
        fgets(player.apellido, sizeof(player.apellido), stdin);
        player.apellido[strcspn(player.apellido, "\n")] = 0;

        if (strlen(player.apellido) == 0) {
            printf("El apellido no puede estar vacío. Intente nuevamente.\n");
        }
    } while (strlen(player.apellido) == 0);

    emailValido(&player);
    passwordCorrect(&player);

    player.id = cant_id+1;
    player.puntuacion = 0;
    player.cuentaActiva = 1;
    player.isAdmin = 0;
    player.partidasJugadas = 0;
    player.partidasGanadas = 0;
    player.partidasEmpatadas = 0;

    return player;
}

void emailValido(stJugador *player) {
    int flag = 0;

    while (!flag) {
        char email[40];
        centrarMensajeHorizontalmente("Email:");

        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = 0;  // elimina el \n al final
        toUpperString(email);

        char *arroba = strchr(email, '@');
        char *punto = strchr(email, '.');

        if (arroba && punto && punto > arroba) {
            strcpy(player->email, email);
            flag = 1;
        } else {
            centrarMensajeHorizontalmente("Email inválido, intente nuevamente...");
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
        if(data_players[i].id == id_logged && data_players[i].cuentaActiva == 1) {
            aux = data_players[i];
        }
    }

    return aux;
}

void modificarPuntuacion(stJugador data[], int pos, int nuevaPuntuacion){
    data[pos].puntuacion = nuevaPuntuacion;
}

int buscarIDArr(stJugador data[], int data_val, int id){
    int pos;
    for(int i=0; i<data_val; i++){
        if(data[i].id == id){
            pos = i;
        }else{
        printf("\nID NO ENCONTRADO\n");
        }
    }
    return pos;
}

void mostrarEstadisticas(stJugador User) {
    system("cls");
    centrarMensajeHorizontalmente("Estadisticas");

    printf("Nombre: %s\n", User.nombre);
    printf("Partidas jugadas: %d\n", User.partidasJugadas);
    printf("Puntuacion: %d\n", User.puntuacion);

    int perdidas = User.partidasJugadas - User.partidasGanadas - User.partidasEmpatadas;
    float porcentajeGanadas = 0, porcentajeEmpatadas = 0, porcentajePerdidas = 0;

    if (User.partidasJugadas > 0) {
        porcentajeGanadas = (User.partidasGanadas * 100.0f) / User.partidasJugadas;
        porcentajeEmpatadas = (User.partidasEmpatadas * 100.0f) / User.partidasJugadas;
        porcentajePerdidas = (perdidas * 100.0f) / User.partidasJugadas;
    }

    printf("Ganadas   : %d\t(%.2f%%)\n", User.partidasGanadas, porcentajeGanadas);
    printf("Empatadas : %d\t(%.2f%%)\n", User.partidasEmpatadas, porcentajeEmpatadas);
    printf("Perdidas  : %d\t(%.2f%%)\n", perdidas, porcentajePerdidas);

    printf("\nPresione una tecla para volver...");
    getch();
}

