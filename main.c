#include <stdio.h>
#include "snake.h"

int main() {
    snake serpiente;
    serpiente.x = 12;
    serpiente.y = 20;
    dibujarTablero(serpiente);
    return 0;
}