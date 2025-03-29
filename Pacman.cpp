#include "graphics.h"
#pragma comment(lib, "graphics.lib") // Enlaza graphics.lib automáticamente

#define CELL_SIZE 13  // Tamaño de cada celda en píxeles
#define ROWS 31
#define COLS 28

const char* mapa[ROWS] = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "     #.##### ## #####.#     ",
    "     #.##          ##.#     ",
    "     #.## ###  ### ##.#     ",
    "######.## #      # ##.######",
    "      .   #      #   .      ",
    "######.## #      # ##.######",
    "     #.## ######## ##.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#...##................##...#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################"
};

void dibujarMapa() {
    for (int fila = 0; fila < ROWS; fila++) {
        for (int col = 0; col < COLS; col++) {
            int x = col * CELL_SIZE;
            int y = fila * CELL_SIZE;

            if (mapa[fila][col] == '#') {
                setfillstyle(SOLID_FILL, BLUE);
                bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
            }
            else if (mapa[fila][col] == '.') {
                setcolor(WHITE);
                circle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, 2);
                floodfill(x + CELL_SIZE / 2, y + CELL_SIZE / 2, WHITE);
            }
        }
    }
}

int main() {
    int width = COLS * CELL_SIZE;
    int height = ROWS * CELL_SIZE;

    initwindow(width, height, "Pac-Man");
    dibujarMapa();
    system("pause");
    closegraph();
    return 0;
}