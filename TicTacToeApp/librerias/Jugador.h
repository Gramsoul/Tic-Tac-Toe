#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

typedef struct{
    int id;
    char nombre[20];
    char apellido[20];
    char email[40];
    char contra[50];
    char figura;
    int cuentaActiva;
    int isAdmin;
}stJugador;

void mostrarJugador(stJugador data);
void mostrarArrJugadores(stJugador arr[], int v);
void passwordCorrect(stJugador *player);
void emailValido(stJugador *player);
stJugador crearJugador(int cant_id);
void deshabilitarID(stJugador data);
void mostrarJugadorAdmin(stJugador data);
void mostrarArrJugadoresAdmin(stJugador arr[], int v);


#endif // JUGADOR_H_INCLUDED
