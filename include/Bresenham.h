#pragma once
#pragma once
#include <cstdlib>
#include <vector>
#include "Punto.h"

using namespace std;

class Bresenham {
public:
    static vector<Punto> dibujarLinea(Punto p0, Punto p1) {
        vector<Punto> puntos;
        int dx = abs(p1.getX() - p0.getX()), dy = abs(p1.getY() - p0.getY());
        int sx = (p0.getX() < p1.getX()) ? 1 : -1;
        int sy = (p0.getY() < p1.getY()) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            puntos.push_back(Punto(p0.getX(), p0.getY()));
            if (p0.getX() == p1.getX() && p0.getY() == p1.getY()) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; p0.setX(p0.getX() + sx); }
            if (e2 < dx) { err += dx; p0.setY(p0.getY() + sy); }
        }
        return puntos;
    }
};
