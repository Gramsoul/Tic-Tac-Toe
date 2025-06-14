#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menus.h"
#include "controApp.h"

int seleccionModo(){
    system("cls");
    int select;

    char menu[][30] = {
        "Seleccione modo de juego",
        " ",
        " 1 - Jugador vs Jugador",
        " 2 - Jugador vs CPU",
        " 3 - Salir"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    scanf("%d", &select);
    system("cls");
    return select;
}

void resetApp(){
    char select = 0;
    printf("\nRESET? ESC para volver al menu.\n");
    select = getch();
    if(select != 27){ menuBasico(); }
}

void menuPrincipal(int isAdmin){
    system("cls");
    if(isAdmin){ menuAdmin(); }
    else { menuBasico(); }

    //Modificar para que esta fn muestre login/register
    //y dependiendo si es admin o no, llamar a las otras fn.
}

void menuBasico(){
    int f = 0;
    char menu[][30] = {
        "Seleccionar opcion:",
        " ",
        "  1 - Ingresar 1",
        "  2 - menu 2",
        "  3 - Salir",
    };

    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

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

    char menu[][30] = {
        "Menu de Administrador",
        " ",
        "1 - Config 1",
        "2 - Config 2",
        "3 - Config 3",
        "4 - Salir",
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

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
            case '4':{
                system("cls");
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

void obtenerTamConsola(int *ancho, int *alto){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *alto = csbi.srWindow.Bottom - csbi.srWindow.Top +1;
}

void menuCentrado(char options[][30], int cantidad){
    int altoConsola, anchoConsola;
    obtenerTamConsola(&anchoConsola, &altoConsola);

    int palabraMax = contarPalabra(options, cantidad);

    int filaInicio = (altoConsola/ 2) - (cantidad/ 2);
    for(int i=0; i< cantidad; i++){
        int columna = (anchoConsola - palabraMax)/ 2;
        gotoxy(columna, filaInicio + i);
        printf("%s\n", options[i]);
    }
}

void gotoxy(int x, int y){
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int contarPalabra(char arr[][30], int v){
    int palMax = 0;
    palMax = strlen(arr[0]);

    for(int i=0; i<v; i++){
        if(palMax < strlen(arr[i])) {
            palMax = strlen(arr[i]); }
    }

    return palMax;
}
