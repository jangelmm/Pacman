#pragma warning(disable: 4996)

#include "graphics.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Inclusión de las cabeceras de tus clases
#include "include/Punto.h"
#include "include/Pared.h"
#include "include/Pallet.h"
#include "include/SuperPallet.h"
#include "include/Fantasma.h"
#include "include/Pacman.h"
#include "include/Graficar.h"
#include "include/Colisiones.h"

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

/// Función para dibujar el mapa estático en una página separada
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
    Pacman pacman(Punto(0, 0)); // Se actualizará su posición según el mapa

    // Recorrer el mapa y crear objetos según el carácter encontrado
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

    // Crear una página para el mapa estático
    int mapaPage = 0;
    setactivepage(mapaPage);
    cleardevice();
    dibujarMapaEstatico(paredes, pallets, superPallets);

    // Guardar el mapa estático en la página actual
    // En cada ciclo se copiará esta página al buffer visual

    // Doble búfer: usamos dos páginas, una para dibujar y otra para mostrar.
    int currentPage = 1;

    bool running = true;
    int iteration = 0;
    
    while (running) {
        // 1. Procesar entrada para mover a Pacman (W, A, S, D; ESC para salir)
        if (kbhit()) {
            int tecla = getch();
            if (tecla == 27) { // ESC
                running = false;
            }
            else {
                pacman.mover(tecla);
            }
        }

        // 2. Actualizar el frame de Pacman (para la animación) y mover a los fantasmas
        pacman.actualizarFrame();
        for (auto& f : fantasmas)
            f.mover();

        // 3. Procesar colisiones entre Pacman y Pallets/SuperPallets
        // Colisión con Pallets
        for (auto it = pallets.begin(); it != pallets.end(); ) {
            if (it->getPos().getX() == pacman.getPos().getX() &&
                it->getPos().getY() == pacman.getPos().getY()) {
                it = pallets.erase(it);
                // Aquí podrías incrementar el puntaje o reproducir sonido.
            }
            else {
                ++it;
            }
        }
        // Colisión con SuperPallets
        for (auto it = superPallets.begin(); it != superPallets.end(); ) {
            if (it->getPos().getX() == pacman.getPos().getX() &&
                it->getPos().getY() == pacman.getPos().getY()) {
                it = superPallets.erase(it);
                // Aquí podrías poner a los fantasmas en modo vulnerable y actualizar el puntaje.
            }
            else {
                ++it;
            }
        }

        // 4. Dibujar la escena (mapa estático y objetos dinámicos)
        cleardevice();
        setactivepage(currentPage);
        // Se dibuja el mapa estático (paredes, pallets y superPallets)
        dibujarMapaEstatico(paredes, pallets, superPallets);
        // Se dibujan los elementos dinámicos
        for (auto& f : fantasmas)
            Graficar::dibujar(f);
        Graficar::dibujar(pacman);
        setvisualpage(currentPage);
        currentPage = 1 - currentPage;

        delay(100);
        iteration++;
    }

    closegraph();
    return 0;
}
