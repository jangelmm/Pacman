#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

class Pared {
private:
    Punto pos;
    int color;
    vector<string> matriz;
public:
    Pared(Punto pos) : pos(pos), color(BLUE) {
        matriz = vector<string>(13, string(13, '1'));
    }
    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    vector<string> getMatrix() const { return matriz; }
};
