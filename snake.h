#ifndef SNAKE_H
#define SNAKE_H

#define LARGO 40
#define ALTO 24
#define foods 50

typedef struct {
    int x;
    int y;
    int size;
} snake;

void loadProgram();
void dibujarTablero(snake serpiente);

#endif