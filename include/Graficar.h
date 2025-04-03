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

struct PixelInfo {
    Punto punto;
    char tipo; // '1', '0', '2'
};

class Graficar {
public:
    // Función que convierte la matriz a una lista de estructuras que incluyen tipo de píxel
    static vector<PixelInfo> obtenerPuntos(const vector<string>& matriz) {
        vector<PixelInfo> puntos;
        for (size_t i = 0; i < matriz.size(); i++) {
            for (size_t j = 0; j < matriz[i].size(); j++) {
                if (matriz[i][j] == '1' || matriz[i][j] == '0' || matriz[i][j] == '2') {
                    puntos.push_back({ Punto(j, i), matriz[i][j] });
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
        int colorBase = obj.getColor();

        // 1. Obtener puntos locales de la matriz con su tipo
        vector<PixelInfo> puntos = obtenerPuntos(matriz);

        // 2. Calcular el factor de escala: queremos que la figura ocupe CELL_SIZE píxeles
        float factor = (float)CELL_SIZE / matriz[0].size();

        // 3. Escalar la figura a tamaño real (en píxeles)
        vector<Punto> puntosEscalados;
        for (const auto& p : puntos) {
            puntosEscalados.push_back(p.punto);
        }
        puntosEscalados = Escalado::escalar(puntosEscalados, factor, factor, Punto(0, 0));

        // 4. Aplicar rotación si el objeto tiene ángulo (solo Pacman rota)
        double angulo = 0.0;
        if constexpr (std::is_same<T, Pacman>::value) {
            angulo = obj.getAngulo();
        }

        int ancho = matriz[0].size();
        int alto = matriz.size();
        Punto pivote(ancho * factor / 2, alto * factor / 2);
        puntosEscalados = Rotacion::rotar(puntosEscalados, angulo, pivote);

        // 5. Trasladar la figura a la posición en pantalla
        puntosEscalados = Traslacion::trasladar(puntosEscalados, Punto(pos.getX() * CELL_SIZE, pos.getY() * CELL_SIZE));

        // 6. Dibujar cada punto con su respectivo color
        int pixelSize = (int)factor;
        for (size_t i = 0; i < puntos.size(); i++) {
            int x_pixel = puntosEscalados[i].getX();
            int y_pixel = puntosEscalados[i].getY();
            int color = colorBase;

            // Asignar colores distintos según el tipo de píxel
            if (puntos[i].tipo == '0') {
                color = WHITE;
            }
            else if (puntos[i].tipo == '2') {
                color = BLUE;
            }

            setfillstyle(SOLID_FILL, color);
            bar(x_pixel, y_pixel, x_pixel + pixelSize, y_pixel + pixelSize);
        }
    }
};
