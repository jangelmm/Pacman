#pragma once
#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

#define BLACK 0x000000 // Define BLACK color code

class Vacio {
private:
    Punto pos;
    int color;
    vector<string> matriz;
public:
    Vacio(Punto pos) : pos(pos), color(BLACK) {
        matriz = {
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111",
            "1111111111111"
        };
    }
    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    vector<string> getMatrix() const { return matriz; }
};
