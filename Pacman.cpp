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

// Mapa del juego
const char* mapa[ROWS] = {
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

// Definición de la función para dibujar una vida con forma de Pac-Man semiabierto
void dibujarPacmanVida(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);

    // Matriz de Pac-Man semiabierto
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

    int pixelSize = 2; // Tamaño del píxel para formar la figura

    for (size_t i = 0; i < 13; i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            if (matriz[i][j] == '1') {
                bar(x + j * pixelSize, y + i * pixelSize, x + (j + 1) * pixelSize, y + (i + 1) * pixelSize);
            }
        }
    }
}

void dibujarHUD(int vidas) {
    setcolor(WHITE);

    int baseY = ROWS * CELL_SIZE + 10;

    // Dibujar iconos de vidas
    int pacmanX = 10;
    int pacmanY = baseY;
    for (int i = 0; i < vidas; i++) {
        dibujarPacmanVida(pacmanX + (i * 30), pacmanY);
    }

    // Mostrar texto debajo de las vidas
    char puntuacion[] = "PUNTUACION: 00        HIGH SCORE: 10000"; // OJO: Modificar aqui para actualizar puntuacion
    char titulo[] = "Pacman";

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(10, baseY + 40, titulo);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, baseY + 70, puntuacion);
}


// Dibuja el mapa estático en una página
void dibujarMapaEstatico(const vector<Pared>& paredes,
    const vector<Pallet>& pallets,
    const vector<SuperPallet>& superPallets) {
    for (auto& p : paredes) Graficar::dibujar(p);
    for (auto& p : pallets) Graficar::dibujar(p);
    for (auto& sp : superPallets) Graficar::dibujar(sp);
}

int main() {
    srand(time(0));
    
    int offsetHUD = 100; // Espacio para el HUD en la parte inferior
    int width = COLS * CELL_SIZE;
    int height = ROWS * CELL_SIZE + offsetHUD + 10; // Se aumentó la altura total

    // Obtener resolución de la pantalla
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calcular coordenadas para centrar la ventana
    int xPos = (screenWidth - width) / 2;
    int yPos = (screenHeight - height) / 2;

    // Inicializar la ventana en el centro de la pantalla
    initwindow(width, height, "Pac-Man", xPos, yPos);

    // Vectores de elementos del juego
    vector<Pared> paredes;
    vector<Pallet> pallets;
    vector<SuperPallet> superPallets;
    vector<Fantasma> fantasmas;
    Pacman pacman(Punto(0, 0));

    // Crear objetos en base al mapa
    for (int i = 0; i < ROWS; i++) {
        string linea = mapa[i];
        for (int j = 0; j < COLS; j++) {
            char c = linea[j];
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

    // Capturar el mapa en un buffer
    void* bufferMapa = malloc(imagesize(0, 0, width, height));
    setactivepage(0);
    cleardevice();
    dibujarMapaEstatico(paredes, pallets, superPallets);
    getimage(0, 0, width, height, bufferMapa);

    int currentPage = 1;
    bool running = true;
    int vidas = 4; // Número de vidas inicial

    while (running) {
        setactivepage(currentPage);
        putimage(0, 0, bufferMapa, COPY_PUT); // Restaurar el mapa desde el buffer

        // Dibujar elementos dinámicos
        for (auto& f : fantasmas) Graficar::dibujar(f);
        Graficar::dibujar(pacman);

        // Dibujar la información en pantalla
        dibujarHUD(vidas);

        setvisualpage(currentPage);
        currentPage = 1 - currentPage;

        delay(100);
        pacman.actualizarFrame();
        for (auto& f : fantasmas) f.mover();

        // Manejo de entrada del usuario
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 27) running = false;
            else pacman.mover(tecla);
        }

        // Detectar si Pac-Man se come un SuperPallet
        for (size_t i = 0; i < superPallets.size(); i++) {
            if (pacman.getPos().getX() == superPallets[i].getPos().getX() &&
                pacman.getPos().getY() == superPallets[i].getPos().getY()) {

                // Borrar SuperPallet
                superPallets.erase(superPallets.begin() + i);

                // Activar modo azul en todos los fantasmas
                for (auto& fantasma : fantasmas) {
                    fantasma.activarModoAzul();
                }
            }
        }
    }

    free(bufferMapa);
    closegraph();
    return 0;
}
