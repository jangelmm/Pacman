#pragma warning(disable: 4996)
#include "graphics.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Windows.h>

#include "include/Punto.h"
#include "include/Pared.h"
#include "include/Pallet.h"
#include "include/SuperPallet.h"
#include "include/Fantasma.h"
#include "include/Pacman.h"
#include "include/Graficar.h"
#include "include/Colisiones.h"

#pragma comment(lib, "graphics.lib")

using namespace std;

#define CELL_SIZE 13
#define ROWS 31
#define COLS 28

static const vector<string> mapa = {
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#*####.#####.##.#####.####*#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#......##....##....##......#",
    "######.##### ## #####.######",
    "     #.##### ## #####.#     ",
    "     #.##    R     ##.#     ",
    "     #.## ###--### ##.#     ",
    "######.## # TSN  # ##.######",
    "      .   #      #   .      ",
    "######.## #      # ##.######",
    "     #.## ######## ##.#     ",
    "     #.##          ##.#     ",
    "     #.## ######## ##.#     ",
    "######.## ######## ##.######",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#*..##.......P........##..*#",
    "###.##.##.########.##.##.###",
    "###.##.##.########.##.##.###",
    "#......##....##....##......#",
    "#.##########.##.##########.#",
    "#.##########.##.##########.#",
    "#..........................#",
    "############################"
};
bool sePuedeMover(int x, int y) {
    if (y < 0 || y >= mapa.size() || x < 0 || x >= mapa[0].size()) {
        return false;
    }
    return mapa[y][x] != '#';
}
void* bufferMapa;

void dibujarPacmanVida(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    string matriz[13] = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11111111111 ",
        "1111111111   ",
        "1111111      ",
        "1111         ",
        "1111111      ",
        "11111111111  ",
        " 11111111111 ",
        " 11111111111 ",
        "  111111111  ",
        "    11111    "
    };
    int pixelSize = 2;
    for (size_t i = 0; i < 13; i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            if (matriz[i][j] == '1') {
                bar(x + j * pixelSize, y + i * pixelSize, x + (j + 1) * pixelSize, y + (i + 1) * pixelSize);
            }
        }
    }
}

void dibujarHUD(int puntaje) {
    setcolor(WHITE);
    int baseY = ROWS * CELL_SIZE + 10;

    // Dibujar vidas de Pac-Man
    for (int i = 0; i < 3; i++) { // Suponiendo 3 vidas
        dibujarPacmanVida(10 + (i * 30), baseY);
    }

    char puntuacion[100];
    sprintf_s(puntuacion, "PUNTUACION: %d        HIGH SCORE: 10000", puntaje);

    char titulo[] = "Pacman";
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(10, baseY + 40, titulo);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, baseY + 70, puntuacion);
}



int main() {
    srand(time(0));
    int offsetHUD = 100;
    int width = COLS * CELL_SIZE;
    int height = ROWS * CELL_SIZE + offsetHUD + 10;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int xPos = (screenWidth - width) / 2;
    int yPos = (screenHeight - height) / 2;

    initwindow(width, height, "Pac-Man", xPos, yPos);

    vector<Pared> paredes;
    vector<Pallet> pallets;
    vector<SuperPallet> superPallets;
    vector<Fantasma> fantasmas;

    Pacman pacman(Punto(0, 0));
    int puntaje = 0;

    // Rellenar las listas de paredes, pallets, superpallets y fantasmas
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c = mapa[i][j];
            Punto pos(j, i);
            switch (c) {
            case '#': paredes.push_back(Pared(pos)); break;
            case '.': pallets.push_back(Pallet(pos)); break;
            case '*': superPallets.push_back(SuperPallet(pos)); break;
            case 'R': fantasmas.push_back(Fantasma(pos, RED)); break;
            case 'T': fantasmas.push_back(Fantasma(pos, CYAN)); break;
            case 'S': fantasmas.push_back(Fantasma(pos, MAGENTA)); break;
            case 'N': fantasmas.push_back(Fantasma(pos, LIGHTRED)); break;
            case 'P': pacman = Pacman(pos); break;
            }
        }
    }

    //bufferMapa = malloc(imagesize(0, 0, width, height));
    bufferMapa = new char[imagesize(0, 0, width, height)];
    setactivepage(0);
    cleardevice();
    for (auto& p : paredes) Graficar::dibujar(p);
    //for (auto& p : pallets) Graficar::dibujar(p);
    //for (auto& sp : superPallets) Graficar::dibujar(sp);
    getimage(0, 0, width, height, bufferMapa);

    int currentPage = 1;
    bool running = true;

    while (running) {
        setactivepage(currentPage);
        putimage(0, 0, bufferMapa, COPY_PUT); // Restaurar el mapa desde el buffer

        // Dibujar elementos dinámicos
         for (auto& p : pallets) Graficar::dibujar(p);
        for (auto& sp : superPallets) Graficar::dibujar(sp);

        for (auto& f : fantasmas) Graficar::dibujar(f);
        Graficar::dibujar(pacman);
        dibujarHUD(puntaje);

        setvisualpage(currentPage);
        currentPage = 1 - currentPage;
        delay(100);

        pacman.actualizarFrame();
        for (auto& f : fantasmas) f.mover();

        // Manejo de entrada del usuario
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 27) running = false;
            else pacman.cambiarDireccion(tecla);
        }

        pacman.mover();

        //// Manejo de colisiones con Pallets
        for (auto it = pallets.begin(); it != pallets.end(); ) {
            if (pacman.getPos() == it->getPos()) {
                puntaje += 10;

                // Borrar el pallet visualmente, dibujando un fondo vacío
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(it->getPos().getX() * CELL_SIZE, it->getPos().getY() * CELL_SIZE,
                    (it->getPos().getX() + 1) * CELL_SIZE, (it->getPos().getY() + 1) * CELL_SIZE);

                it = pallets.erase(it);  // Eliminar pallet de la lista
            }
            else {
                ++it;
            }
        }

        // Manejo de colisiones con SuperPallets
        
        for (auto it = superPallets.begin(); it != superPallets.end(); ) {
            if (pacman.getPos() == it->getPos()) {
                puntaje += 50;

                // Borrar el superPallet visualmente
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(it->getPos().getX() * CELL_SIZE, it->getPos().getY() * CELL_SIZE,
                    (it->getPos().getX() + 1) * CELL_SIZE, (it->getPos().getY() + 1) * CELL_SIZE);

                it = superPallets.erase(it);
            }
            else {
                ++it;
            }

            for (auto& f : fantasmas) {
                f.actualizarModoAzul();
                f.mover();  // Esto internamente decide si moverse rápido o no
            }

        }

        // Detectar si Pac-Man se come un fantasma
        for (size_t i = 0; i < fantasmas.size(); i++) {
            if (pacman.getPos().getX() == fantasmas[i].getPos().getX() &&
                pacman.getPos().getY() == fantasmas[i].getPos().getY() &&
                pacman.estaAtacando()) { // Si Pac-Man está en estado "Atacar"

                // Incrementar puntaje por comer un fantasma
                pacman.incrementarPuntaje(100); // Por ejemplo, 100 puntos por comer un fantasma

                // Regresar el fantasma a su celda de inicio
                fantasmas[i].regresarACeldaInicio();

                break;
            }

        }
    }
    delete[](char*)bufferMapa;
    free(bufferMapa);
    closegraph();
    return 0;
}

