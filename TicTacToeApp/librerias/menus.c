#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menus.h"
#include "controApp.h"
#include "login.h"

int seleccionModo(){
    system("cls");
    int select;

    char menu[][30] = {
        "Seleccione modo de juego",
        " ",
        " 1 - Jugador vs Jugador",
        " 2 - Jugador vs CPU",
        " 3 - Desloguear",
        " 4 - Salir"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    scanf("%d", &select);
    system("cls");
    return select;
}

<<<<<<< HEAD
void menuLogin(/* params */) {
    system("cls");
    char menu[][30] = {
        "Seleccione un menu",
        "",
        "1- Iniciar sesion",
        "2- Registrar una cuenta nueva",
        "3- Salir"
    };
    int v_menu = sizeof(menu)/sizeof(menu[0]);
    menuCentrado(menu, v_menu);

    int opcion = 0;
     do {
        scanf("%d", &opcion);

        switch(opcion) {
        case 1:
            menuIniciarSesion(/* params */);
            break;
        case 2:
            menuRegistrarCuenta(/* params */);
            break;
        case 3:
            centrarMensajeHorizontalmente("Saliendo...");
            break;
        default:
            centrarMensajeHorizontalmente("\nERROR\n");
            break;
        }
     } while(opcion != 3)

    /*
    do {
        flag_valido = login(/* params );
        if(flag_valido == 0) {
            printf("\Credenciales Incorrectas");
        } else {
            flag_resultado = 1;
        }
    } while(flag_valido == 0);
    */
}

int menuIniciarSesion(/* params */) {
    int salir = 0;
    int flag = 0;

    while(salir == 0 && flag == 0) {
        flag = login(/* params */);
        if(flag == 0) {
            centrarMensajeHorizontalmente("Credenciales Incorrectas");
            centrarMensajeHorizontalmente("ESC: Salir");
            scanf("%d", &salir);
            if(salir != 27) {
                salir = 0;
            }
        }
    }

}

void resetApp(){
=======
void resetApp(char tablero[3][3]){
>>>>>>> d8c5c6b3bea66d32c892c5a86c737ee847dc759a
    char select = 0;
    printf("\nRESET? ESC para volver al menu.\n");
    select = getch();
    if(select != 27){
        rellenarTablero(tablero);
        //MODODEJUEGO(PLAYER ACTUAL, PLAYER2 ACTUAL).
    } else {
        //seleccionModo();
    }
}

void menuPrincipal(int isAdmin){
    system("cls");
    if(isAdmin){
            menuAdmin();
    }
    else {
            menuBasico();
    }

    //Modificar para que esta fn muestre login/register
    //y dependiendo si es admin o no, llamar a las otras fn.
}

void menuBasico(){
    system("cls");
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
    system("cls");
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

int dondeEstaY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.dwCursorPosition.Y;
}

void centrarMensajeHorizontalmente(char mensaje[]){
    int anchoConsola, altoconsola;
    obtenerTamConsola(&anchoConsola, &altoconsola);

    int x = (anchoConsola - strlen(mensaje))/ 2;

    gotoxy(x, dondeEstaY());
    printf("%s\n", mensaje);
}
