#include <vector>
#include <string>
#include "Punto.h"
#include "Colisiones.h"

using namespace std;

class Pacman {
private:
    Punto pos;
    int color;
    int frame; // Para la animación
    double angulo; // Ángulo de rotación
    char direccionActual; // Dirección de movimiento actual

public:
    Pacman(Punto pos) : pos(pos), color(YELLOW), frame(0), angulo(0.0), direccionActual('d') {}

    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    double getAngulo() const { return angulo; }

    // Retorna la matriz según el estado de animación
    vector<string> getMatrix() const {
        vector<string> matriz;
        if (frame % 10 == 0 || frame % 10 == 1 || frame % 10 == 2 || frame % 10 == 9) {
            // Figura 1: boca cerrada
            matriz = {
                "    11111    ",
                "  111111111  ",
                " 11111111111 ",
                " 11111111111 ",
                "1111111111111",
                "1111111111111",
                "1111111111111",
                "1111111111111",
                "1111111111111",
                " 11111111111 ",
                " 11111111111 ",
                "  111111111  ",
                "    11111    "
            };
        }
        else if (frame % 10 == 3 || frame % 10 == 4 || frame % 10 == 5) {
            // Figura 2: boca semiabierta
            matriz = {
                "    11111    ",
                "  111111111  ",
                " 11111111111 ",
                " 11111111111 ",
                "1111111111   ",
                "1111111      ",
                "1111         ",
                "1111111      ",
                "11111111111  ",
                " 11111111111 ",
                " 11111111111 ",
                "  111111111  ",
                "    11111    "
            };
        }
        else {
            // Figura 3: boca abierta
            matriz = {
                "    1111111  ",
                "  111111111  ",
                " 111111111   ",
                " 11111111    ",
                "1111111      ",
                "11111        ",
                "1111         ",
                "11111        ",
                "1111111      ",
                " 11111111    ",
                " 111111111   ",
                "  111111111  ",
                "    1111111  "
            };
        }
        return matriz;
    }

    void actualizarFrame() { frame++; }

    // Actualiza la dirección de movimiento basada en la tecla presionada
    void cambiarDireccion(char tecla) {
        switch (tecla) {
        case 'w': case 'W':
            direccionActual = 'w';
            angulo = 270; // Rotación hacia arriba
            break;
        case 's': case 'S':
            direccionActual = 's';
            angulo = 90; // Rotación hacia abajo
            break;
        case 'a': case 'A':
            direccionActual = 'a';
            angulo = 180; // Rotación hacia la izquierda
            break;
        case 'd': case 'D':
            direccionActual = 'd';
            angulo = 0; // Rotación hacia la derecha
            break;
        default:
            break;
        }
    }

    // Mueve a Pac-Man en la dirección actual
    void mover() {
        int newX = pos.getX();
        int newY = pos.getY();
        switch (direccionActual) {
        case 'w':
            newY -= 1;
            break;
        case 's':
            newY += 1;
            break;
        case 'a':
            newX -= 1;
            break;
        case 'd':
            newX += 1;
            break;
        default:
            break;
        }
        // Solo actualiza si la nueva posición no es una pared
        if (sePuedeMover(newX, newY)) {
            pos.setX(newX);
            pos.setY(newY);
        }
    }
};

