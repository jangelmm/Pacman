#pragma once
#include <vector>
#include <string>
#include "Punto.h"
#include "..\graphics.h"
#include "Constantes.h"

using namespace std;

class Graficar {
public:
    // Función plantilla que dibuja cualquier objeto que tenga getMatrix(), getPos() y getColor()
    template<typename T>
    static void dibujar(const T& obj) {
        vector<string> matriz = obj.getMatrix();
        Punto pos = obj.getPos();
        int color = obj.getColor();

        // Calcula la esquina superior izquierda en píxeles de la celda correspondiente
        int baseX = pos.getX() * CELL_SIZE;
        int baseY = pos.getY() * CELL_SIZE;

        // Si la matriz del objeto tiene dimensiones mayores a 1 y se desea que se ajuste a CELL_SIZE,
        // se puede calcular un factor de escala. Por ejemplo, si la matriz es de 13x13, el factor es 1.
        // float factorX = (float)CELL_SIZE / matriz[0].size();
        // float factorY = (float)CELL_SIZE / matriz.size();

        // En este ejemplo, usaremos un factor de escala 1:1, es decir, cada "pixel" en la matriz equivale a 1 píxel.
        for (size_t i = 0; i < matriz.size(); i++) {
            for (size_t j = 0; j < matriz[i].size(); j++) {
                if (matriz[i][j] == '1') {
                    // Desplazamiento en la celda, sin multiplicar de nuevo por CELL_SIZE
                    int x_pixel = baseX + j;
                    int y_pixel = baseY + i;
                    setfillstyle(SOLID_FILL, color);
                    // Dibuja un píxel o un rectángulo pequeño (si se desea agrandar, cambiar 1 por el tamaño deseado)
                    bar(x_pixel, y_pixel, x_pixel + 1, y_pixel + 1);
                }
            }
        }
    }
};
