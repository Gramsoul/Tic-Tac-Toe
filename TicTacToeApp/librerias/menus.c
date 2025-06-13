#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menus.h"
#include "controApp.h"

int seleccionModo(){
    system("cls");
    int select;
    printf("Seleccione modo de juego:\n");
    printf("01 - JvsJ\n");
    printf("02 - JvsCPU\n");
    scanf("%d", &select);
    system("cls");
    return select;
}

void resetApp(){
    char select = 0;
    printf("\nRESET? ESC para salir.\n");
    select = getch();
    if(select != 27){ inicializarApp(); }
}

void menuPrincipal(int isAdmin){
    system("cls");
    if(isAdmin){ menuAdmin(); }
    else { menuBasico(); }
}

void menuBasico(){
    int f = 0;
    printf("Seleccionar opcion: \n");
    printf("1 - Ingresar 1\n");
    printf("2 - Registrar 2\n");
    printf("3 - Salir\n");

    while(!f){
        char select = 0;
        fflush(stdin);
        select = getch();

        switch(select){
            case '1':{
                system("cls");
                printf("Menu 1..\n");
            break;
            }
            case '2':{
                system("cls");
                printf("Menu 2..\n");
            break;
            }
            case '3':{
                system("cls");
                printf("Menu 3..\n");
                f = 1;
            break;
            }
        }
    }

}

void menuAdmin(){
    int f = 0;
    printf("Configuracion: \n");
    printf("1 - Buscar Jugador 1\n");
    printf("2 - menu 2\n");
    printf("3 - Salir\n");

    while(!f){
        char select = 0;
        fflush(stdin);
        select = getch();

        switch(select){
            case '1':{
                system("cls");
                printf("Menu 1..\n");
            break;
            }
            case '2':{
                system("cls");
                printf("Menu 2..\n");
            break;
            }
            case '3':{
                system("cls");
                printf("Menu 3..\n");
                f = 1;
            break;
            }
        }
    }
}

void maximizarConsola(){
    SetConsoleTitle("Proyecto Tic-Tac-Toe");
    HWND hConsola = GetConsoleWindow();
    ShowWindow(hConsola, SW_MAXIMIZE);
}
