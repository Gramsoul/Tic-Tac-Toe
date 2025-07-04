#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"
#include "Jugador.h"
#include "menus.h"

void cargarArchivo(){
    FILE *file = fopen(DATA_JUGADORES, "rb");
    if(file){
        stJugador aux;
        while(fread(&aux, sizeof(stJugador), 1, file) > 0){
            printf("nombre: %s %s\n", aux.nombre, aux.apellido);
            printf("email: %s\n", aux.email);
            printf("pass: %s\n", aux.contra);
            printf("ID: %d\n", aux.id);
            printf("-----------------------------------\n");
        }
        fclose(file);
    } else { printf("ERROR al cargar archivo %s", DATA_JUGADORES); }
}

void cargarArchivoArr(stJugador data[], int *i, const char name[]){
    FILE *file = fopen(name, "rb");
    if(file){
        stJugador aux;
        while(fread(&aux, sizeof(stJugador), 1, file) > 0){
                data[*i] = aux; (*i)++;
        }
        fclose(file);
    } else { printf("ERROR al cargar %s al array", DATA_JUGADORES); }
}

void guardarJugador(stJugador data, const char name[]){
    FILE *file = fopen(name, "ab");
    if(file){
        fwrite(&data, sizeof(stJugador), 1, file);
        fclose(file);
    }else{ printf("ERROR al guardar jugador\n"); }
}

void guardarArr(stJugador data[], int v){
    FILE *file = fopen(DATA_JUGADORES, "wb");
    if(file){
        for(int i=0; i<v; i++){
            fwrite(&data[i], sizeof(stJugador), 1, file);
        }
        fclose(file);
    }else{
        centrarMensajeHorizontalmente("ERROR - ARR_PLAYER SIN GUARDAR.\n");
        system("pause");
    }
}

int cantEntidades(char name[], size_t tam){
    int max = 0, size = 0;
    FILE *file = fopen(name, "rb");

    if(file){
        fseek(file, 0, SEEK_END);
        max = ftell(file);
        rewind(file);
    } else { printf("ERROR en cantEtidades\n"); }

    size = max/tam;

    return size;
}

void guardarNuevoJugadorArr(stJugador data[], int *val_data, stJugador *nuevoJugador){
    *nuevoJugador = crearJugador(*val_data);
    data[*val_data] = *nuevoJugador;
    (*val_data)++;
}
