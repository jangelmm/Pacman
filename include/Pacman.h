#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "Punto.h"
#include "Colisiones.h"

using namespace std;

class Pacman {
private:
    Punto pos;
    int color;
    int frame;
    double angulo;
    char direccionActual;
    int puntaje;
    bool atacando;
    time_t tiempoInicioAtaque;

public:
    Pacman(Punto pos)
        : pos(pos), color(YELLOW), frame(0), angulo(0.0),
        direccionActual('d'), puntaje(0), atacando(false),
        tiempoInicioAtaque(0) {
    }

    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    double getAngulo() const { return angulo; }
    int obtenerPuntaje() const { return puntaje; }
    bool estaAtacando() const { return atacando; }

    void incrementarPuntaje(int valor) {
        puntaje += valor;
    }

    void activarAtaque() {
        atacando = true;
        tiempoInicioAtaque = time(nullptr);
    }

    void actualizarModoAtaque() {
        if (atacando) {
            time_t ahora = time(nullptr);
            if (difftime(ahora, tiempoInicioAtaque) >= 5.0) {
                atacando = false;
            }
        }
    }

    void actualizarFrame() {
        frame++;
    }

    vector<string> getMatrix() const {
        if (frame % 10 <= 2 || frame % 10 == 9) {
            return {
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
        else if (frame % 10 <= 5) {
            return {
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
            return {
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
    }

    void cambiarDireccion(char tecla) {
        switch (tecla) {
        case 'w': case 'W': direccionActual = 'w'; angulo = 270; break;
        case 's': case 'S': direccionActual = 's'; angulo = 90; break;
        case 'a': case 'A': direccionActual = 'a'; angulo = 180; break;
        case 'd': case 'D': direccionActual = 'd'; angulo = 0; break;
        }
    }

    void mover() {
        int newX = pos.getX();
        int newY = pos.getY();

        switch (direccionActual) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        }

        if (sePuedeMover(newX, newY)) {
            pos.setX(newX);
            pos.setY(newY);
        }


    }
};

