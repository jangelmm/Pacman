#pragma once
#include <vector>
#include "Punto.h"

using namespace std;

class Traslacion {
public:
    static vector<Punto> trasladar(const vector<Punto>& puntos, const Punto& T) {
        vector<Punto> puntos_trasladados;
        for (const auto& p : puntos) {
            int x_nuevo = p.getX() + T.getX();
            int y_nuevo = p.getY() + T.getY();
            puntos_trasladados.emplace_back(x_nuevo, y_nuevo);
        }
        return puntos_trasladados;
    }
};
