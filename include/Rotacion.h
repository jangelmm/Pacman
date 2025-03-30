#pragma once
#include <cmath>
#include <vector>
#include "Punto.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

class Rotacion {
public:
    static vector<Punto> rotar(const vector<Punto>& puntos, double angulo, const Punto& pivote) {
        vector<Punto> puntos_rotados;
        double radianes = angulo * M_PI / 180.0;
        double cosTheta = cos(radianes);
        double sinTheta = sin(radianes);

        for (const auto& p : puntos) {
            int x = p.getX() - pivote.getX();
            int y = p.getY() - pivote.getY();

            int xNuevo = round(pivote.getX() + x * cosTheta - y * sinTheta);
            int yNuevo = round(pivote.getY() + x * sinTheta + y * cosTheta);

            puntos_rotados.emplace_back(xNuevo, yNuevo);
        }
        return puntos_rotados;
    }
};
#pragma once
