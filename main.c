#include <stdio.h>
#include <unistd.h>
#include "snake.h"

int main() {
    // 
    Serpiente serpiente = {{{12, 20}}, 1, 'd'};

    while (1) {
        dibujarTablero(&serpiente);
        usleep(300000); // Ajustamos velocidad
        moverSerpiente(&serpiente);
        system("clear"); // Limpiar la pantalla
    }

    return 0;
}

