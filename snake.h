#ifndef SNAKE_H
#define SNAKE_H

#define LARGO 40
#define ALTO 24
#define FOODS 50

typedef struct {
    int x;
    int y;
} Coordenada;

typedef struct {
    Coordenada cuerpo[100]; // Suponiendo un tamaño máximo de 100 segmentos
    int tamano;
    char direccion; // 'w', 's', 'a', 'd'
} Serpiente;

void loadProgram();
void dibujarTablero(Serpiente* serpiente);
void moverSerpiente(Serpiente* serpiente);
void actualizarTablero(char tablero[LARGO][ALTO], Serpiente* serpiente);

#endif
