#pragma once
#include <vector>
#include <string>
#include "Punto.h"

using namespace std;

#define ORANGE 0xFFA500 // Define ORANGE color code

class Pallet {
private:
    Punto pos;
    int color;
    vector<string> matriz;
public:
    Pallet(Punto pos) : pos(pos), color(ORANGE) {
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
