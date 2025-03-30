#pragma once
#include <vector>
#include "Punto.h"

using namespace std;

class Escalado {
public:
    static vector<Punto> escalar(const vector<Punto>& puntos, float sx, float sy, Punto pivote) {
        vector<Punto> resultado;
        for (const auto& p : puntos) {
            int x_nuevo = pivote.getX() + sx * (p.getX() - pivote.getX());
            int y_nuevo = pivote.getY() + sy * (p.getY() - pivote.getY());
            resultado.emplace_back(x_nuevo, y_nuevo);
        }
        return resultado;
    }
};
#pragma once
