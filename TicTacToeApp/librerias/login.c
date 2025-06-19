#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "login.h"
#include "Jugador.h"
#include "archivos.h"

int login(stJugador data[], int data_v){
    int flag = 0;

    stJugador aux = dataLogin();

    int login = buscarJugadorLogin(data, data_v, aux);
    if(login == 0){
            printf("LOGEADO...\n");
            flag = 1;
    }

    return flag;
}



int buscarJugadorLogin(stJugador data[], int vData, stJugador aux){ // existe -> 0
    int res = -1, flag = 0, i = 0;
    while(i<vData && !flag){
            if(strcmp(aux.email, data[i].email) == 0){
                res = validarPassword(data[i], aux.contra);
                flag = 1;
            }
            i++;
        }
    return res;
}

int validarPassword(stJugador data, char pass[]){
    return strcmp(data.contra, pass);
}

stJugador dataLogin(){
    stJugador aux;
    fflush(stdin);
    emailValido(&aux);
    fflush(stdin);
    printf("Password: \n");
    ocultarPassw(aux.contra, sizeof(aux.contra));

    return aux;
}

void ocultarPassw(char *pass, int tmax){
    int i = 0;
    char c;
    while ((c = getch()) != '\r' && i < tmax - 1){   //Si lo introducido es diferente que "enter" y menor a 40 caracteres
        if(c == '\b'){  //si borras vuelve hacia atras una posicion y "simula" un borrado con \b \b
            i--;
            printf("\b \b");
        } else {    // si no borraste implanta en caracter en el string y printea un *..
            pass[i] = c;
            i++;
            printf("*");
        }
    }
    pass[i] = '\0'; //agrega el simbolo de finalizacion del string
    printf("\n");
}
