#pragma once
#include <vector>
#include <string>
#include "Punto.h"
#include "..\graphics.h"
#include "Constantes.h"
#include "Rotacion.h"
#include "Escalado.h"
#include "Traslacion.h"

using namespace std;

class Graficar {
public:
    // Función que convierte la matriz a vector de puntos (coordenadas locales)
    static vector<Punto> obtenerPuntos(const vector<string>& matriz) {
        vector<Punto> puntos;
        for (size_t i = 0; i < matriz.size(); i++) {
            for (size_t j = 0; j < matriz[i].size(); j++) {
                if (matriz[i][j] == '1') {
                    puntos.push_back(Punto(j, i));
                }
            }
        }
        return puntos;
    }

    // Función plantilla que dibuja un objeto aplicando transformaciones
    template<typename T>
    static void dibujar(const T& obj) {
        vector<string> matriz = obj.getMatrix();
        Punto pos = obj.getPos();  // pos está en "celdas" (por ejemplo, 0,0; 1,2; etc.)
        int color = obj.getColor();

        // 1. Obtener puntos locales de la matriz
        vector<Punto> puntos = obtenerPuntos(matriz);

        // 2. Calcular el factor de escala: queremos que la figura ocupe CELL_SIZE píxeles
        float factor = (float)CELL_SIZE / matriz[0].size();

        // 3. Escalar la figura a tamaño real (en píxeles)
        puntos = Escalado::escalar(puntos, factor, factor, Punto(0, 0));

        // 4. (Opcional) Aplicar rotación; en este ejemplo dejamos angulo = 0, pero puedes modificarlo
        double angulo = 0.0;
        int ancho = matriz[0].size();
        int alto = matriz.size();
        Punto pivote(ancho * factor / 2, alto * factor / 2);
        puntos = Rotacion::rotar(puntos, angulo, pivote);

        // 5. Trasladar la figura a la posición en pantalla: pos (en celdas) se convierte a píxeles
        // Nota: Multiplicamos pos por CELL_SIZE para obtener la esquina superior izquierda
        puntos = Traslacion::trasladar(puntos, Punto(pos.getX() * CELL_SIZE, pos.getY() * CELL_SIZE));

        // 6. Dibujar cada punto. Cada punto se dibuja como un rectángulo de tamaño "factor" (aproximadamente)
        int pixelSize = (int)factor;  // Tamaño de cada "pixel" del sprite
        for (const auto& p : puntos) {
            int x_pixel = p.getX();
            int y_pixel = p.getY();
            setfillstyle(SOLID_FILL, color);
            bar(x_pixel, y_pixel, x_pixel + pixelSize, y_pixel + pixelSize);
        }
    }
};
