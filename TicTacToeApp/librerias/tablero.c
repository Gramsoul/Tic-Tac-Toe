#include "tablero.h"
#include "menus.h"
#include <stdlib.h>
#include <stdio.h>


void mostrarTablero(char tablero[3][3]) {
    system("cls");

    int anchoConsola, altoConsola;
    obtenerTamConsola(&anchoConsola, &altoConsola);

    int anchoTablero = (3 * 7) + (2 * 1);  // 7 por celda, 2 separadores "|"
    int altoTablero = (3 * 3) + 2;         // 3 filas con 3 líneas cada una, +2 separadores

    int columnaInicio = (anchoConsola - anchoTablero) / 2;
    int filaInicio = (altoConsola - altoTablero) / 2;

    int filaConsola = filaInicio;


    for (int fila = 0; fila < 3; fila++) {
        for (int linea = 0; linea < 3; linea++) {
            gotoxy(columnaInicio, filaConsola++);
            for (int columna = 0; columna < 3; columna++) {
                if (linea == 1) {
                    printf("   %c   ", tablero[fila][columna]);
                } else {
                    printf("       ");
                }
                if (columna < 2) printf("|");
            }
            printf("\n");
        }
        if (fila < 2) {
            gotoxy(columnaInicio, filaConsola++);
            printf("-------+-------+-------\n");
        }
    }
}
void rellenarTablero(char tablero[3][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = 32;
            }
        }
}
