#pragma warning(disable: 4996)

#include "graphics.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Inclusi�n de las cabeceras de tus clases
#include "include/Punto.h"
#include "include/Pared.h"
#include "include/Pallet.h"
#include "include/SuperPallet.h"
#include "include/Fantasma.h"
#include "include/Pacman.h"
#include "include/Graficar.h"

#pragma comment(lib, "graphics.lib") // Vincula la biblioteca graphics.lib

using namespace std;

#define CELL_SIZE 13
#define ROWS 31
#define COLS 28

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

/// Funci�n para dibujar el mapa est�tico en una p�gina separada
void dibujarMapaEstatico(const vector<Pared>& paredes,
    const vector<Pallet>& pallets,
    const vector<SuperPallet>& superPallets) {
    // Dibuja paredes, pallets y superpallets
    for (auto& p : paredes)
        Graficar::dibujar(p);
    for (auto& p : pallets)
        Graficar::dibujar(p);
    for (auto& sp : superPallets)
        Graficar::dibujar(sp);
}

int main() {
    srand(time(0));
    int width = COLS * CELL_SIZE;
    int height = ROWS * CELL_SIZE;
    initwindow(width, height, "Pac-Man");

    // Vectores para almacenar objetos del juego
    vector<Pared> paredes;
    vector<Pallet> pallets;
    vector<SuperPallet> superPallets;
    vector<Fantasma> fantasmas;
    Pacman pacman(Punto(0, 0)); // Se actualizar� su posici�n seg�n el mapa

    // Recorrer el mapa y crear objetos seg�n el car�cter encontrado
    for (int i = 0; i < ROWS; i++) {
        string linea = mapa[i];
        for (int j = 0; j < COLS; j++) {
            char c = linea[j];
            Punto pos(j, i);
            switch (c) {
            case '#':
                paredes.push_back(Pared(pos));
                break;
            case '.':
                pallets.push_back(Pallet(pos));
                break;
            case '*':
                superPallets.push_back(SuperPallet(pos));
                break;
            case 'R': // Fantasma Rojo
                fantasmas.push_back(Fantasma(pos, RED));
                break;
            case 'T': // Fantasma Turquesa (Azul)
                fantasmas.push_back(Fantasma(pos, CYAN));
                break;
            case 'S': // Fantasma Rosa
                fantasmas.push_back(Fantasma(pos, MAGENTA));
                break;
            case 'N': // Fantasma Naranja
                fantasmas.push_back(Fantasma(pos, LIGHTRED));
                break;
            case 'P': // Pacman
                pacman = Pacman(pos);
                break;
            default:
                break;
            }
        }
    }

    // Crear una p�gina para el mapa est�tico
    int mapaPage = 0;
    setactivepage(mapaPage);
    cleardevice();
    dibujarMapaEstatico(paredes, pallets, superPallets);

    // Guardar el mapa est�tico en la p�gina actual
    // En cada ciclo se copiar� esta p�gina al buffer visual

    // Doble b�fer: usamos dos p�ginas, una para dibujar y otra para mostrar.
    int currentPage = 1;

    bool running = true;
    int iteration = 0;
    while (running) {
        // Dibuja en la p�gina oculta
        setactivepage(currentPage);
        // Primero, copia el mapa est�tico (ya dibujado en mapaPage) al buffer actual
        // La funci�n readimagefile permite copiar una porci�n de la pantalla.
        // Guardamos el mapa est�tico en un rect�ngulo que abarca toda la ventana.
        readimagefile("",
            0, 0, width, height); // Si tu versi�n lo permite, o bien, dibuja nuevamente el mapa est�tico
        // Si readimagefile no resulta adecuado, puedes volver a dibujar el mapa est�tico
        dibujarMapaEstatico(paredes, pallets, superPallets);

        // Dibujar elementos din�micos
        for (auto& f : fantasmas)
            Graficar::dibujar(f);
        Graficar::dibujar(pacman);

        // Actualiza la p�gina visual
        setvisualpage(currentPage);

        // Alterna la p�gina para el siguiente cuadro
        currentPage = 1 - currentPage;

        delay(100);
        iteration++;
        pacman.actualizarFrame();

        // Mover fantasmas de forma aleatoria
        for (auto& f : fantasmas)
            f.mover();

        // Procesar entrada para mover a Pacman (W, A, S, D; ESC para salir)
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 27) { // ESC
                running = false;
            }
            else {
                pacman.mover(tecla);
            }
        }
    }

    closegraph();
    return 0;
}
