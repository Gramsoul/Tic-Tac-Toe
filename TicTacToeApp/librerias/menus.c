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
        " 3 - Ver estadisticas",
        " 4 - Configuracion",
        " 5 - Desloguear",
        " 6 - Salir"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    scanf("%d", &select);
    system("cls");
    return select;
}

int menuLogin(stJugador data_players[], int *data_players_val_pointer) {
    int data_players_val = *data_players_val_pointer;
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
            stJugador nuevoJugador;
            guardarNuevoJugadorArr(data_players, &data_players_val, &nuevoJugador);
            guardarArr(data_players, data_players_val);
            *data_players_val_pointer = data_players_val;
            centrarMensajeHorizontalmente("Usuario registrado exitosamente!");
            Sleep(1000);
            break;
        }
        case 3:
            system("cls");
            mostrarPuntuaciones(data_players, data_players_val);
            system("pause");
            break;
        case 4:
            centrarMensajeHorizontalmente("Saliendo...");
            finalizarApp(data_players, data_players_val);
            Sleep(500);
            res = -1;
            break;
        case 0:{
            menuAdmin(data_players, data_players_val); //MENU DE ADMINISTRACION
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

void menuConfig(stJugador *User, stJugador data_players[], int *data_players_val){ //Lo mando de puntero porque se necesita para modificar en los otros menus
    system("cls");

    int isAdmin = User->isAdmin;

    if(isAdmin){
            menuConfigAdmin(User, data_players, data_players_val);
    }
    else {
            menuConfigUser(User, data_players, data_players_val);
    }
}

void menuConfigUser(stJugador *User, stJugador data_players[], int *data_players_val) {
    char menu[][30] = {
        "Menu de configuracion",
        " ",
        " 1 - Mod. nombre y apellido",
        " 2 - Mod. contrasenia",
        " 3 - Eliminar cuenta",
        " 4 - Volver"
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);

    int select = 0;
    while(select !=4) {
        menuCentrado(menu, tam_menu);
        scanf("%d", &select);
        switch(select) {
            case 1:
                modificarUsuario(User);
                break;
            case 2:
                modificarPassword(User);
                break;
            case 3:
                borrarCuenta(User);
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


void menuConfigAdmin(stJugador *Admin, stJugador data_players[], int *data_players_val) {
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

    int select = 0;
    menuCentrado(menu, tam_menu);
    while(select !=5) {
        scanf("%d", &select);
        switch(select) {
            case 1:
                modificarUsuario(Admin);
                break;
            case 2:
                modificarPassword(Admin);
                break;
            case 3:
                adminBorrarCuentaArr(data_players, data_players_val);
                break;
            case 4:
                adminDarPermisosArr(data_players, data_players_val);
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
 /*
void adminBorrarCuenta(stJugador *Admin) {
    FILE * original = fopen(DATA_JUGADORES, "rb");
    FILE * copia = fopen("temp.dat", "wb");

    if(!original || !copia) {
        perror("ERROR EN adminBorrarCuenta");
        return;
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

        // Recargar el array desde el archivo actualizado
        // Nota: Esto requeriría pasar el array y contador como parámetros
        // Por ahora, el array se recargará en la próxima ejecución
        centrarMensajeHorizontalmente("Usuario eliminado exitosamente!");
        Sleep(1000);
    } else {
        printf("Usuario con ID %d no encontrado. \n", id_eliminar);
        remove("temp.dat");
        Sleep(1000);
    }
}
*/

void adminBorrarCuentaArr(stJugador data_players[], int *data_players_val) {
    system("cls");
    centrarMensajeHorizontalmente("Lista de usuarios:");
    mostrarArrJugadoresAdmin(data_players, *data_players_val);

    centrarMensajeHorizontalmente("Ingrese el ID del usuario a eliminar: ");
    int id_eliminar;
    scanf("%d", &id_eliminar);

    int pos = buscarIDArr(data_players, *data_players_val, id_eliminar);

    if(pos != -1) {
        // Eliminar del array
        for(int i = pos; i < *data_players_val - 1; i++) {
            data_players[i] = data_players[i + 1];
        }
        (*data_players_val)--;

        // Guardar array actualizado al archivo
        guardarArr(data_players, *data_players_val);

        centrarMensajeHorizontalmente("Usuario eliminado exitosamente");
        Sleep(1000);
    } else {
        centrarMensajeHorizontalmente("Usuario no encontrado");
        Sleep(1000);
    }
}


void adminDarPermisosArr(stJugador data_players[], int *data_players_val) {
    system("cls");
    centrarMensajeHorizontalmente("Lista de usuarios:");
    mostrarArrJugadoresAdmin(data_players, *data_players_val);

    centrarMensajeHorizontalmente("Ingrese el ID del usuario al que quiere dar permisos de admin: ");
    int id_admin;
    scanf("%d", &id_admin);

    int pos = buscarIDArr(data_players, *data_players_val, id_admin);

    if (pos != -1) {
        data_players[pos].isAdmin = 1;
        guardarArr(data_players, *data_players_val);

        centrarMensajeHorizontalmente("Permisos de administrador asignados correctamente");
        Sleep(1000);
    } else {
        centrarMensajeHorizontalmente("Usuario no encontrado");
        Sleep(1000);
    }
}


void modificarUsuario(stJugador *User) {
    system("cls");
    limpiarBuffer(); // Limpiar buffer antes de fgets

    centrarMensajeHorizontalmente("Primer nombre:");
    fgets(User->nombre, sizeof(User->nombre), stdin);
    User->nombre[strcspn(User->nombre, "\n")] = 0; // Eliminar \n

    centrarMensajeHorizontalmente("Apellido:");
    fgets(User->apellido, sizeof(User->apellido), stdin);
    User->apellido[strcspn(User->apellido, "\n")] = 0; // Eliminar \n

    centrarMensajeHorizontalmente("Datos modificados exitosamente!");
    Sleep(1000);
}

void modificarPassword(stJugador *User) {
    system("cls");
    passwordCorrect(User);
}

void borrarCuenta(stJugador *User) {
    system("cls");
    centrarMensajeHorizontalmente("Desea cerrar definitivamente su cuenta?");
    char control = 'x';
    do {
        printf("Ingrese su respuesta (s/n): \n");
        scanf(" %c", &control);
        control = tolower(control);
    } while(control != 's' && control != 'n');

    if(control == 's') {
        User->cuentaActiva = 0;
        centrarMensajeHorizontalmente("Cuenta desactivada correctamente");
    } else {
        centrarMensajeHorizontalmente("Operación cancelada");
    }

    Sleep(1000);
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
        "2 - Ver Archivo",
        "3 - Forzar Jugador",
        "4 - Modificar puntaje",
        "0 - Volver",
    };
    int tam_menu = sizeof(menu)/ sizeof(menu[0]);
    menuCentrado(menu, tam_menu);

    while(!f){
        int select = 0;
        scanf("%d", &select);
        limpiarBuffer(); // Limpiar buffer después de scanf

        switch(select){
            case 0:{
                f = 1;
            break;
            }
            case 1:{
                system("cls");
                mostrarArrJugadoresAdmin(data, val);
                system("pause");
                menuAdmin(data, val);
            break;
            }
            case 2:{
                system("cls");
                cargarArchivo();
                system("pause");
                menuAdmin(data, val);
            break;
            }
            case 3:{
                stJugador aux = crearJugador(val);
                guardarJugador(aux, DATA_JUGADORES);
                centrarMensajeHorizontalmente(" ");
                centrarMensajeHorizontalmente("Guardando jugador..");
                Sleep(700);
                system("cls");
                menuAdmin(data, val);
            break;
            }
            case 4:{
                int id, pos, newpun;
                mostrarPuntuacionesAdm(data, val);
                system("pause");
                centrarMensajeHorizontalmente("ID a buscar.");
                scanf("%d", &id);
                limpiarBuffer(); // Limpiar buffer después de scanf
                pos = buscarIDArr(data, val, id);
                printf("Nueva puntuacion: \n");
                scanf("%d", &newpun);
                limpiarBuffer(); // Limpiar buffer después de scanf
                modificarPuntuacion(data, pos, newpun);
                centrarMensajeHorizontalmente(" ");
                centrarMensajeHorizontalmente("Modificando puntaje..");

                Sleep(700);
                system("cls");
                menuAdmin(data, val);
            break;
            }
            default:{
                centrarMensajeHorizontalmente(" ");
                centrarMensajeHorizontalmente("Opcion incorrecta");
                Sleep(1000);
                system("cls");
                menuAdmin(data, val);
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
