#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "tablero.h"
#include "archivos.h"
#include "menus.h"
#include "controApp.h"
#include "login.h"
#include "controlDatos.h"

int seleccionModo(){
    system("cls");
    int select;

    char menu[][30] = {
        "Seleccione modo de juego",
        " ",
        " 1 - Jugador vs Jugador",
        " 2 - Jugador vs CPU",
        " 3 - Desloguear",
        " 4 - Configuracion",
        " 5 - Salir"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    scanf("%d", &select);
    system("cls");
    return select;
}

int menuLogin(stJugador data_players[], int data_players_val) {
    system("cls");
    char menu[][30] = {
        "Seleccione un menu",
        "",
        "1- Iniciar sesion",
        "2- Registrar una cuenta nueva",
        "3- Ver Ranking",
        "4- Salir"
    };
    int v_menu = sizeof(menu)/sizeof(menu[0]);
    int opcion = 0;
    int res = 0;

     do {
        system("cls");
        menuCentrado(menu, v_menu);

        scanf("%d", &opcion);
        switch(opcion) {
        case 1:
            res = menuIniciarSesion(data_players, data_players_val);
            break;
        case 2:{
            stJugador newPlayer = crearJugador(data_players_val);
            guardarJugador(newPlayer, DATA_JUGADORES);
            res = newPlayer.id;
            break;
        }
        case 3:
            mostrarPuntuaciones(data_players, data_players_val);
            break;
        case 4:
            centrarMensajeHorizontalmente("Saliendo...");
            res = -1;
            break;
        case 0:{
            menuAdmin(data_players, data_players_val);
        break;
        }
        default:
            centrarMensajeHorizontalmente("\nERROR\n");
            break;
        }
     } while(res == 0);

    return res;
}

int menuIniciarSesion(stJugador data_players[], int data_players_val) {
    char salir = 'x';
    int flag = 0;

    while(salir != 's' && flag == 0) {
       flag = login(data_players, data_players_val);
        if(flag == 0) {
            centrarMensajeHorizontalmente("Credenciales Incorrectas");
            centrarMensajeHorizontalmente("'s': Salir");
            //centrarMensajeHorizontalmente("'c': Continuar");

            scanf("%c", &salir);
        }
    }
    return flag;
}

void resetApp(char tablero[3][3]){
    char select = 0;
    centrarMensajeHorizontalmente("RESET?. ESC para volver al menu.");
    select = getch();
    if(select != 27){
        rellenarTablero(tablero);
        //MODODEJUEGO(PLAYER ACTUAL, PLAYER2 ACTUAL).
    } else {
        //seleccionModo();
    }
}

void menuConfig(stJugador *User){ //Lo mando de puntero porque se necesita para modificar en los otros menus
    system("cls");

    int isAdmin = User->isAdmin;

    if(isAdmin){
            menuConfigAdmin(User);
    }
    else {
            menuConfigUser(User);
    }
}

void menuConfigUser(stJugador *User) {
    char menu[][30] = {
        "Menu de configuracion",
        " ",
        " 1 - Mod. nombre y apellido",
        " 2 - Mod. contrasenia",
        " 3 - Eliminar cuenta",
        " 4 - Volver"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    int select = 0;
    while(select !=4) {
        scanf("%d", &select);
        switch(select) {
            case 1:
                modificarUsuario(User);
                break;
            case 2:
                modificarPassword(User);
                break;
            case 3:
                //borrarCuenta(User);
                break;
            case 4:
                //Sale directamente de config
                break;
            default:
                printf("\ERROR: Elegir una opcion valida");
                break;
        }
    }
}

void menuConfigAdmin(stJugador *Admin) {
    char menu[][30] = {
        "Menu de configuracion",
        " ",
        " 1 - Mod. nombre y apellido",
        " 2 - Mod. contrasenia",
        " 3 - Borrar usuario",
        " 4 - Permisos de admin",
        " 5 - Volver"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    int select = 0;
    while(select !=4) {
        scanf("%d", &select);
        switch(select) {
            case 1:
                modificarUsuario(Admin);
                break;
            case 2:
                modificarPassword(Admin);
                break;
            case 3:
                adminBorrarCuenta(Admin); //dentro deberia recibir el file con users
                break;
            case 4:
                // adminDarPermisos(Admin); //dentro deberia recibir el file con users
                break;
            case 5:
                //Sale directamente de config
                break;
            default:
                printf("\ERROR: Elegir una opcion valida");
                break;
        }
    }
}

void adminBorrarCuenta(stJugador *Admin) {
    FILE * original = fopen(DATA_JUGADORES, "rb");
    FILE * copia = fopen("temp.dat", "wb");

    if(!original || !copia) {
        perror("ERROR EN adminBorrarCuenta");
    }

    //Mostrar lista con todos los usuarios, luego, pedir un numero para borrar
    int id_eliminar;
    scanf("%d", &id_eliminar);

    stJugador user;
    int encontrado = 0;

    while(fread(&user, sizeof(stJugador), 1, original)) {
        if(user.id == id_eliminar) {
            printf("Usuario con ID %d eliminado.\n", id_eliminar);
            encontrado = 1;
        } else {
            fwrite(&user, sizeof(stJugador), 1, copia);
        }
    }

    fclose(original);
    fclose(copia);

    if(encontrado) {
        remove(DATA_JUGADORES);
        rename("temp.dat", DATA_JUGADORES);
    } else {
        printf("Usuario con ID %d no encontrado. \n", id_eliminar);
        remove("temp.dat");
    }
}
/*
void adminDarPermisos(stJugador *Admin) {

}
*/

void modificarUsuario(stJugador *User) {
    system("cls");
    centrarMensajeHorizontalmente("Primer nombre:\n");
    fgets(User->nombre, sizeof(User->nombre), stdin);

    centrarMensajeHorizontalmente("Apellido:\n");
    fgets(User->apellido, sizeof(User->apellido), stdin);
}

void modificarPassword(stJugador *User) {
    system("cls");
    passwordCorrect(User);
}

///Tomas: Las funciones de abajo creo que se podrian borrar
///Gonzalo: menuAdmin lo voy a dejar para nosotros. se abre en el primer menu con '0' <- CERO.
///Gonzalo: y maximizar consola, nose, por las dudas la dejo.

void menuAdmin(stJugador data[], int val){
    system("cls");
    int f = 0;

    char menu[][30] = {
        "Menu de Administrador",
        " ",
        "1 - Ver usuarios",
        "2 - Volver",
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
                mostrarArrJugadoresAdmin(data, val);
                system("pause");
                menuAdmin(data, val);
            break;
            }
            case '2':{
                f = 1;
            break;
            }
            default:{
                centrarMensajeHorizontalmente(" ");
                centrarMensajeHorizontalmente("Opcion incorrecta");
                Sleep(1000);
                system("cls");
                menuCentrado(menu, tam_menu);
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
