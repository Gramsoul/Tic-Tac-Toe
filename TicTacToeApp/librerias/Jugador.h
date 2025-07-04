#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

typedef struct{
    int id;
    char nombre[20];
    char apellido[20];
    char email[40];
    char contra[50];
    int puntuacion;
    int cuentaActiva;
    int isAdmin;

    int partidasJugadas;
    int partidasGanadas;
    int partidasEmpatadas;
}stJugador;

void mostrarJugador(stJugador data);
void mostrarArrJugadores(stJugador arr[], int v);
void passwordCorrect(stJugador *player);
void emailValido(stJugador *player);
stJugador crearJugador(int cant_id);
void deshabilitarID(stJugador *data);
void mostrarJugadorAdmin(stJugador data);
void mostrarArrJugadoresAdmin(stJugador arr[], int v);
stJugador buscarPlayerLogged(stJugador data_players[], int data_players_val, int id_logged);
void mostrarPuntuaciones(stJugador arr[], int val);
void toUpperString(char *str);
void modificarPuntuacion(stJugador data[], int id,int nuevaPuntuacion);
void mostrarPuntuacionesAdm(stJugador arr[], int val);
void mostrarEstadisticas(stJugador User);
int buscarIDArr(stJugador data[], int data_val, int id);


#endif // JUGADOR_H_INCLUDED
