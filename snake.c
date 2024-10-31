#include <stdlib.h>
#include <stdio.h>
#include "snake.h"

//https://prod.liveshare.vsengsaas.visualstudio.com/join?BCFAE49092E0EA5F3C928A08181FB51BC4D1

char tablero[LARGO][ALTO];

void loadProgram() {
    system("stty raw");
    char tecla;
    tecla = getc(stdin);
    printf("%c\n", tecla);
}

void dibujarTablero(snake serpiente) {
    for(int x = 0; x < ALTO; x++) {
        for(int y = 0; y < LARGO; y++) {
            if (x == 0 || y == 0 || x == ALTO - 1 || y == LARGO - 1) {
                tablero[x][y] = '#';
            } else {
                tablero[x][y] = ' ';
            }
            if (x == serpiente.x && y == serpiente.y) {
                tablero[x][y] = 'O';
            }
            printf("%c", tablero[x][y]);
        }
        printf("\n");
    }
}
