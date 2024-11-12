#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "snake.h"

char tablero[ALTO][LARGO]; // Tablero con dimensiones correctas

void loadProgram() {
    system("stty raw");
    char tecla;
    tecla = getc(stdin);
    printf("%c\n", tecla);
    system("stty cooked");
}

void dibujarTablero(Serpiente* serpiente) {
    actualizarTablero(tablero, serpiente);
    for(int x = 0; x < ALTO; x++) {
        for(int y = 0; y < LARGO; y++) {
            printf("%c", tablero[x][y]);
        }
        printf("\n");
    }
}

void moverSerpiente(Serpiente* serpiente) {
    Coordenada nuevaCabeza = serpiente->cuerpo[0];
    switch (serpiente->direccion) {
        case 'w': nuevaCabeza.x--; break;
        case 's': nuevaCabeza.x++; break;
        case 'a': nuevaCabeza.y--; break;
        case 'd': nuevaCabeza.y++; break;
    }
    for (int i = serpiente->tamano - 1; i > 0; i--) {
        serpiente->cuerpo[i] = serpiente->cuerpo[i - 1];
    }
    serpiente->cuerpo[0] = nuevaCabeza;
}

void actualizarTablero(char tablero[ALTO][LARGO], Serpiente* serpiente) {
    // Inicializa el tablero con los bordes y el espacio vacío
    for(int x = 0; x < ALTO; x++) {
        for(int y = 0; y < LARGO; y++) {
            if (x == 0 || y == 0 || x == ALTO - 1 || y == LARGO - 1) {
                tablero[x][y] = '#';
            } else {
                tablero[x][y] = ' ';
            }
        }
    }
    // Coloca la serpiente en el tablero
    for (int i = 0; i < serpiente->tamano; i++) {
        int x = serpiente->cuerpo[i].x;
        int y = serpiente->cuerpo[i].y;

        // Asegurarse de que las coordenadas estén dentro de los límites
        if (x > 0 && x < ALTO - 1 && y > 0 && y < LARGO - 1) {
            tablero[x][y] = 'O';
        }
    }
}