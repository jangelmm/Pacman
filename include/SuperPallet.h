#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

class SuperPallet {
private:
    Punto pos;
    int color;
    vector<string> matriz;
    vector<string> matrizVacia; // Matriz vacía para hacerla desaparecer
    bool comida; // Indica si la superpallet ya fue comida
public:
    SuperPallet(Punto pos) : pos(pos), color(WHITE), comida(false) {
        matriz = {
            "             ",
            "             ",
            "             ",
            "    11111    ",
            "    11111    ",
            "    11111    ",
            "    11111    ",
            "    11111    ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             "
        };
        // Matriz vacía (cuando la superpallet es comida)
        matrizVacia = {
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             ",
            "             "
        };
    }
    Punto getPos() const { return pos; }
    int getColor() const { return color; }

    // Devuelve la matriz según si la superpallet fue comida o no
    vector<string> getMatrix() const {
        return comida ? matrizVacia : matriz;
    }

    // Método para "comer" la superpallet y cambiar su estado
    void comer() {
        comida = true;
    }
};
