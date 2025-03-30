#pragma once
#include "Constantes.h"  // Opcional: si defines ROWS, COLS y CELL_SIZE en un header común

// Declaración externa del mapa (ya definido en main.cpp)
extern const char* mapa[];

// Función inline para verificar si se puede mover a la celda (x,y)
inline bool sePuedeMover(int x, int y) {
    // Verificar límites
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return false;
    // Retorna false si la celda es una pared ('#')
    return (mapa[y][x] != '#');
}
#pragma once
