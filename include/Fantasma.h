#pragma once
#include <vector>
#include <string>
#include "Punto.h"
#include "Colisiones.h"

using namespace std;

class Fantasma {
private:
    Punto pos;
    int color;
    vector<string> matriz;
    int dir; // Dirección actual

    // Variables para el modo azul
    bool enModoAzul = false;
    int contadorCambio = 0;
    int tiempoAzul = 30;

    Punto posicionInicio;

    // Matrices de dirección
    vector<string> matrizDerecha = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11001110011 ",
        " 10022100221 ",
        "1100221002211",
        "1110011100111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "111 11111 111",
        " 1   1 1   1"
    };
    vector<string> matrizIzquierda = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11001110011 ",
        " 12200122001 ",
        "1122001220011",
        "1110011100111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "111 11111 111",
        " 1   1 1   1"
    };
    vector<string> matrizArriba = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11221112211 ",
        " 10220102201 ",
        "1100001000011",
        "1110011100111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "111 11111 111",
        " 1   1 1   1"
    };
    vector<string> matrizAbajo = {
        "    11111    ",
        "  111111111  ",
        " 11111111111 ",
        " 11001110011 ",
        " 10000100001 ",
        "1102201022011",
        "1112211122111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "1111111111111",
        "111 11111 111",
        " 1   1 1   1"
    };

    // Matrices para el modo azul
    vector<string> fantasmaA = {
        "    22222    ",
        "  222222222  ",
        " 22222222222 ",
        " 22222222222 ",
        " 22002220022 ",
        "2220022200222",
        "2222222222222",
        "2222222222222",
        "2202200022022",
        "2020022200202",
        "2222222222222",
        "222 22222 222",
        " 2   2 2   2"
    };
    vector<string> fantasmaB = {
        "    00000    ",
        "  000000000  ",
        " 00000000000 ",
        " 00000000000 ",
        " 00220002200 ",
        "0002200022000",
        "0000000000000",
        "0000000000000",
        "0020022200200",
        "0202200022020",
        "0000000000000",
        "000 00000 000",
        " 0   0 0   0"
    };

public:
    Fantasma(Punto pos, int color)
        : pos(pos), color(color), dir(0), posicionInicio(pos) {
        matriz = matrizDerecha;
    }

    Punto getPos() const { return pos; }
    int getColor() const { return color; }
    vector<string> getMatrix() const { return matriz; }

    // Activar modo azul cuando Pacman come SuperPallet
    void activarModoAzul() {
        enModoAzul = true;
        contadorCambio = 0;

    }

    // Actualizar estado del modo azul (debe llamarse en el bucle principal)
    void actualizarModoAzul() {
        if (enModoAzul) {
            contadorCambio++;
            if (contadorCambio >= tiempoAzul) {
                enModoAzul = false;
                color = RED;
                matriz = matrizDerecha; // Volver a la matriz normal
            }
            else {
                matriz = (contadorCambio % 2 == 0) ? fantasmaA : fantasmaB;
            }
        }
    }

    void regresarACeldaInicio() {
        pos = posicionInicio;
        enModoAzul = false;
        color = RED;
        matriz = matrizDerecha;
    }

    // Movimiento aleatorio
    void mover() {
        if (enModoAzul) {
            moverRapidoAleatorio();  // Se moverá dos veces para hacerlo más rápido
        }
        else {
            moverNormal();
        }
    }

    void moverNormal() {
        int newX = pos.getX();
        int newY = pos.getY();

        int direccion = rand() % 4;

        switch (direccion) {
        case 0: newX += 1; matriz = matrizDerecha; break;
        case 1: newX -= 1; matriz = matrizIzquierda; break;
        case 2: newY += 1; matriz = matrizAbajo; break;
        case 3: newY -= 1; matriz = matrizArriba; break;
        }

        if (sePuedeMover(newX, newY)) {
            pos.setX(newX);
            pos.setY(newY);
        }
    }

    void moverRapidoAleatorio() {
        for (int i = 0; i < 2; ++i) { // Moverse dos veces
            int newX = pos.getX();
            int newY = pos.getY();
            int direccion = rand() % 4;

            switch (direccion) {
            case 0: newX += 1; break;
            case 1: newX -= 1; break;
            case 2: newY += 1; break;
            case 3: newY -= 1; break;
            }

            if (sePuedeMover(newX, newY)) {
                pos.setX(newX);
                pos.setY(newY);
            }
        }
    }


















};

