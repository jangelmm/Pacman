#pragma once
#include <vector>
#include <string>
#include "Punto.h"
#include "Colisiones.h"

using namespace std;

class Fantasma {
private:
    Punto pos;
    int color;
    vector<string> matriz;
public:
    Fantasma(Punto pos, int color) : pos(pos), color(color) {
        matriz = {
            "    11111    ",
            "  111111111  ",
            " 11111111111 ",
            " 11111111111 ",
            " 11111111111 ",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "111 11111 111",
            " 1   1 1   1"
        };
    }
    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    vector<string> getMatrix() const { return matriz; }

    // Movimiento aleatorio (simplificado)
    void mover() {
        int dir = rand() % 4;
        int newX = pos.getX();
        int newY = pos.getY();
        switch (dir) {
        case 0: newX += 1; break;
        case 1: newX -= 1; break;
        case 2: newY += 1; break;
        case 3: newY -= 1; break;
        }
        // Solo mueve si el destino no es pared
        if (sePuedeMover(newX, newY))
        {
            pos.setX(newX);
            pos.setY(newY);
        }
    }
};
