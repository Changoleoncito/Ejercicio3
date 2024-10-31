#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Asegúrate de incluir esta biblioteca
#include <termios.h>  // Para configurar el terminal en modo sin bloqueo (compatible con Linux/Mac)
#include <unistd.h> // for usleep
#include <sys/select.h> // for kbhit equivalent

#define COLS 25
#define ROWS 25
#define MAX_FOOD 10
#define SNAKE_MAX_LEN 100

char board[COLS * ROWS];
int snakeX[SNAKE_MAX_LEN], snakeY[SNAKE_MAX_LEN];
int snakeLength = 1;
int foodX[MAX_FOOD], foodY[MAX_FOOD];
int foodCount = MAX_FOOD;
int score = 0;
int gameOver = 0;

void fill_board() {
    int x, y;
    for (y = 0; y < ROWS; y++) {
        for (x = 0; x < COLS; x++) {
            if (x == 0 || y == 0 || x == COLS - 1 || y == ROWS - 1) {
                board[y * COLS + x] = '#';
            } else {
                board[y * COLS + x] = ' ';
            }
        }
    }
}

void draw_snake() {
    for (int i = 0; i < snakeLength; i++) {
        board[snakeY[i] * COLS + snakeX[i]] = (i == 0) ? '@' : '*';
    }
}

void draw_food() {
    for (int i = 0; i < foodCount; i++) {
        if (foodX[i] != -1 && foodY[i] != -1) {
            board[foodY[i] * COLS + foodX[i]] = '+';
        }
    }
}

void place_food() {
    for (int i = 0; i < foodCount; i++) {
        if (foodX[i] == -1 && foodY[i] == -1) {
            int newX, newY;
            do {
                newX = 1 + rand() % (COLS - 2);
                newY = 1 + rand() % (ROWS - 2);
            } while (board[newY * COLS + newX] != ' '); // Ensure food does not appear on the snake
            foodX[i] = newX;
            foodY[i] = newY;
        }
    }
}

void clear_screen() {
    printf("\033[H\033[J"); // Clear screen using ANSI escape codes
}

void print_board() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            putchar(board[y * COLS + x]);
        }
        putchar('\n');
    }
}

void set_nonblocking_mode(int enable) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (enable) {
        tty.c_lflag &= ~(ICANON | ECHO); // desactivar modo canónico y eco
        tty.c_cc[VMIN] = 0;
        tty.c_cc[VTIME] = 0;
    } else {
        tty.c_lflag |= (ICANON | ECHO); // activar modo canónico y eco
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void read_keyboard() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv)) {
        int ch = getchar();
        switch (ch) {
            case 'w': snakeY[0]--; break;
            case 's': snakeY[0]++; break;
            case 'a': snakeX[0]--; break;
            case 'd': snakeX[0]++; break;
        }
    }
}

void update_snake_position() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
}

void check_food() {
    for (int i = 0; i < foodCount; i++) {
        if (snakeX[0] == foodX[i] && snakeY[0] == foodY[i]) {
            score += 100;
            snakeLength++;
            if (snakeLength > SNAKE_MAX_LEN) {
                snakeLength = SNAKE_MAX_LEN;
            }
            foodX[i] = -1; // Mark food as eaten
            foodY[i] = -1;
        }
    }
    place_food(); // Ensure new food is placed after eating
}

void check_game_over() {
    if (snakeX[0] == 0 || snakeX[0] == COLS - 1 || snakeY[0] == 0 || snakeY[0] == ROWS - 1) {
        gameOver = 1;
    }
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
        }
    }
}

int main() {
    srand(time(0));
    snakeX[0] = COLS / 2;
    snakeY[0] = ROWS / 2;
    for (int i = 1; i < SNAKE_MAX_LEN; i++) {
        snakeX[i] = -1;
        snakeY[i] = -1;
    }
    for (int i = 0; i < foodCount; i++) {
        foodX[i] = -1;
        foodY[i] = -1;
    }
    place_food();

    set_nonblocking_mode(1); // Habilitar modo no bloqueante

    while (!gameOver) {
        fill_board();
        draw_food();
        draw_snake();
        clear_screen();
        printf("Score: %d\n", score);
        print_board();
        read_keyboard();
        update_snake_position();
        check_food();
        check_game_over();
        usleep(200000); // Small delay
    }

    set_nonblocking_mode(0); // Restaurar el modo normal
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
