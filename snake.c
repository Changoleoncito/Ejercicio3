#include <stdlib.h>
#include <stdio.h>
#include "snake.h"

//https://prod.liveshare.vsengsaas.visualstudio.com/join?BCFAE49092E0EA5F3C928A08181FB51BC4D1

//aligned_alloc


char tablero[LARGO][ALTO];

void loadProgram() {
    system("stty raw");
    char tecla;
    while(1) {
        tecla = getc(stdin);
        printf("%c\n", tecla);
    }
    
}
void dibujarTablero() {
    
    for(int y = 0; y < ALTO; y++) {
        for(int x = 0; x < LARGO; x++) {
            if (x == 0 || y == 0 || x == ALTO - 1 || y == LARGO - 1) {
                //tablero[y * ALTO + x] = '#';
            } else {
                //tablero[y * ALTO + x] = ' ';
            }
        }
    }
}
void posSnake();