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
public:
    SuperPallet(Punto pos) : pos(pos), color(WHITE) {
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
    }
    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    vector<string> getMatrix() const { return matriz; }
};
