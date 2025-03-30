#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

class Pacman {
private:
    Punto pos;
    int color;
    int frame; // Para animación
public:
    Pacman(Punto pos) : pos(pos), color(YELLOW), frame(0) {}
    Punto getPos() const { return pos; }
    int getColor() const { return color; }

    // Retorna la matriz según el estado de animación
    vector<string> getMatrix() const {
        vector<string> matriz;
        if (frame % 10 == 0 || frame % 10 == 1 || frame % 10 == 2 || frame % 10 == 9) {
            // Figura 1: boca cerrada
            matriz = {
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
        }
        else if (frame % 10 == 3 || frame % 10 == 4 || frame % 10 == 5) {
            // Figura 2: boca semiabierta
            matriz = {
                "    11111    ",
                "  111111111  ",
                " 11111111111 ",
                " 11111111111 ",
                "1111111111   ",
                "1111111      ",
                "1111         ",
                "1111111      ",
                "11111111111 ",
                " 11111111111 ",
                " 11111111111 ",
                "  111111111  ",
                "    11111    "
            };
        }
        else {
            // Figura 3: boca abierta
            matriz = {
                "    1111111  ",
                "  111111111  ",
                " 111111111   ",
                " 11111111    ",
                "1111111      ",
                "11111        ",
                "1111         ",
                "11111        ",
                "1111111      ",
                " 11111111    ",
                " 111111111   ",
                "  111111111  ",
                "    1111111  "
            };
        }
        return matriz;
    }

    void actualizarFrame() { frame++; }

    // Movimiento según tecla (W, A, S, D)
    void mover(char tecla) {
        int newX = pos.getX();
        int newY = pos.getY();
        switch (tecla) {
        case 'w':
        case 'W': newY -= 1; break;
        case 's':
        case 'S': newY += 1; break;
        case 'a':
        case 'A': newX -= 1; break;
        case 'd':
        case 'D': newX += 1; break;
        default: break;
        }
        pos.setX(newX);
        pos.setY(newY);
    }
};
