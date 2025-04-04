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
#include "include/Vacio.h"       // Incluir la nueva clase Vacio
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

// Dibuja un icono de vida (mini Pac-Man semiabierto)
void dibujarPacmanVida(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    // Matriz de Pac-Man semiabierto (13x13)
    string matriz[13] = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11111111111 ",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        " 11111111111 ",
        " 11111111111 ",
        "  111111111  ",
        "    11111    "
    };
    int pixelSize = 2;
    for (size_t i = 0; i < 13; i++) {
        for (size_t j = 0; j < matriz[i].size(); j++) {
            if (matriz[i][j] == '1') {
                bar(x + j * pixelSize, y + i * pixelSize,
                    x + (j + 1) * pixelSize, y + (i + 1) * pixelSize);
            }
        }
    }
}

void dibujarHUD(int vidas, int puntaje) {
    setcolor(WHITE);
    int baseY = ROWS * CELL_SIZE + 10;
    int pacmanX = 10, pacmanY = baseY;
    for (int i = 0; i < vidas; i++) {
        dibujarPacmanVida(pacmanX + (i * 30), pacmanY);
    }
    char buffer[100];
    sprintf(buffer, "PUNTUACION: %d        HIGH SCORE: 10000", puntaje);
    char titulo[] = "Pacman";
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(10, baseY + 40, titulo);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(10, baseY + 70, buffer);
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
    int offsetHUD = 100;
    int width = COLS * CELL_SIZE;
    int height = ROWS * CELL_SIZE + offsetHUD + 10;

    // Centrar la ventana en pantalla
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int xPos = (screenWidth - width) / 2;
    int yPos = (screenHeight - height) / 2;
    initwindow(width, height, "Pac-Man", xPos, yPos);

    // Inicialización de objetos del juego
    vector<Pared> paredes;
    vector<Pallet> pallets;
    vector<SuperPallet> superPallets;
    vector<Fantasma> fantasmas;
    vector<Vacio> vacios;  // Vector para guardar las zonas vacías (pellets y superpellets comidos)
    Pacman pacman(Punto(0, 0));

    // Crear objetos a partir del mapa lógico
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

    // Capturar el mapa estático en un buffer para doble buffer
    void* bufferMapa = malloc(imagesize(0, 0, width, height));
    setactivepage(0);
    cleardevice();
    dibujarMapaEstatico(paredes, pallets, superPallets);
    getimage(0, 0, width, height, bufferMapa);

    int currentPage = 1;
    bool running = true;
    Punto posInicial = pacman.getPos();

    while (running) {
        // Procesar entrada: cambiar dirección (sin detener el avance)
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 27) {
                running = false;
            }
            else {
                pacman.mover(tecla);
            }
        }

        // Avanzar continuamente en la dirección actual
        pacman.avanzar();

        // Manejar túnel teletransportador (horizontal)
        int x = pacman.getPos().getX();
        int y = pacman.getPos().getY();
        if (x < 0) {
            pacman = Pacman(Punto(COLS - 1, y));
        }
        else if (x >= COLS) {
            pacman = Pacman(Punto(0, y));
        }

        // Colisiones con Pellets:
        // Si Pac-Man está en la misma celda que un Pallet, se elimina el Pallet,
        // se suma el puntaje y se añade un objeto Vacio en esa celda para repintar en negro.
        for (auto it = pallets.begin(); it != pallets.end(); ) {
            if (pacman.getPos().getX() == it->getPos().getX() &&
                pacman.getPos().getY() == it->getPos().getY()) {
                Vacio vacio(it->getPos());
                vacios.push_back(vacio);
                it = pallets.erase(it);
                pacman.sumarPuntaje(10);
            }
            else {
                ++it;
            }
        }

        // Colisiones con SuperPallets:
        // Se aplica la misma lógica que con los Pallets:
        // al comer el SuperPallet, se añade un objeto Vacio para repintar la zona en negro,
        // se activa el modo de ataque y se cambia el color de los fantasmas.
        for (auto it = superPallets.begin(); it != superPallets.end(); ) {
            if (pacman.getPos().getX() == it->getPos().getX() &&
                pacman.getPos().getY() == it->getPos().getY()) {
                Vacio vacio(it->getPos());
                vacios.push_back(vacio);
                it = superPallets.erase(it);
                pacman.activarModoAtacar();
                for (auto& fantasma : fantasmas) {
                    fantasma.activarModoAzul();
                }
            }
            else {
                ++it;
            }
        }

        // Colisiones con Fantasmas
        for (auto& fantasma : fantasmas) {
            if (pacman.getPos().getX() == fantasma.getPos().getX() &&
                pacman.getPos().getY() == fantasma.getPos().getY()) {
                if (pacman.getModoAtacar()) {
                    fantasma.resetear();
                    pacman.sumarPuntaje(200);
                }
                else {
                    pacman.perderVida(posInicial);
                }
            }
        }

        // Dibujo con doble buffer:
        setactivepage(currentPage);
        putimage(0, 0, bufferMapa, COPY_PUT); // Restaurar el mapa estático

        // Dibujar objetos vacíos (zonas repintadas en negro)
        for (auto& vacio : vacios) {
            Graficar::dibujar(vacio);
        }
        // Dibujar elementos dinámicos
        for (auto& fantasma : fantasmas) {
            Graficar::dibujar(fantasma);
        }
        Graficar::dibujar(pacman);
        dibujarHUD(pacman.getVidas(), pacman.getPuntaje());
        setvisualpage(currentPage);
        currentPage = 1 - currentPage;

        delay(100);
        pacman.actualizarFrame();
        for (auto& fantasma : fantasmas) {
            fantasma.mover();
        }
    }

    free(bufferMapa);
    closegraph();
    return 0;
}
