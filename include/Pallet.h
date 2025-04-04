#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

#define CREMA COLOR(255, 248, 220)  // Código RGB para crema cálido (#FFF8DC)

class Pallet {
private:
    Punto pos;
    int color;
    vector<string> matriz;
public:
    Pallet(Punto pos) : pos(pos), color(CREMA) {
        matriz = {
            "             ",
            "             ",
            "             ",
            "             ",
            "     111     ",
            "     111     ",
            "     111     ",
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
    vector<string> getMatrix() const { return matriz; }
};
