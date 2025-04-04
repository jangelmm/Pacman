#pragma once
#include <vector>
#include <string>
#include "Punto.h"
#include "Colisiones.h"

using namespace std;

class Pacman {
private:
    Punto pos;
    int color;
    int frame;         // Para animación
    double angulo;     // Ángulo de rotación (para la animación)
    int direccion;     // 0: derecha, 1: abajo, 2: izquierda, 3: arriba
    int puntaje;       // Puntaje acumulado
    int vidas;         // Número de vidas
    bool modoAtacar;   // True cuando se ha comido un SuperPallet

public:
    // Constructor: inicializa en posición, color, dirección y con puntaje 0, 5 vidas y modo de ataque false
    Pacman(Punto pos) : pos(pos), color(YELLOW), frame(0), angulo(0.0), direccion(0), puntaje(0), vidas(5), modoAtacar(false) {}

    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    double getAngulo() const { return angulo; }
    int getPuntaje() const { return puntaje; }
    int getVidas() const { return vidas; }
    bool getModoAtacar() const { return modoAtacar; }

    // Actualiza el frame de animación
    void actualizarFrame() { frame++; }

    // Actualiza la dirección en función de la tecla pulsada y el ángulo
    void mover(char tecla) {
        switch (tecla) {
        case 'w': case 'W':
            direccion = 3; // arriba
            angulo = 270;
            break;
        case 's': case 'S':
            direccion = 1; // abajo
            angulo = 90;
            break;
        case 'a': case 'A':
            direccion = 2; // izquierda
            angulo = 180;
            break;
        case 'd': case 'D':
            direccion = 0; // derecha
            angulo = 0;
            break;
        default:
            break;
        }
    }

    // Método para avanzar continuamente en la dirección actual
    void avanzar() {
        int newX = pos.getX();
        int newY = pos.getY();
        switch (direccion) {
        case 0: newX += 1; break; // derecha
        case 1: newY += 1; break; // abajo
        case 2: newX -= 1; break; // izquierda
        case 3: newY -= 1; break; // arriba
        }
        // Si la celda destino no es pared, actualizar posición
        if (sePuedeMover(newX, newY)) {
            pos.setX(newX);
            pos.setY(newY);
        }
    }

    // Incrementa el puntaje (por ejemplo, cuando come un Pallet)
    void sumarPuntaje(int puntos) {
        puntaje += puntos;
    }

    // Activa el modo de ataque (cuando come un SuperPallet)
    void activarModoAtacar() {
        modoAtacar = true;
    }

    // Desactiva el modo de ataque (cuando termina su duración)
    void desactivarModoAtacar() {
        modoAtacar = false;
    }

    // Resta una vida y regresa a la posición inicial
    void perderVida(Punto posInicial) {
        vidas--;
        pos = posInicial;
    }

    // Retorna la matriz segun el estado de animacion
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
};
