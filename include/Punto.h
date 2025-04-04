#pragma once

class Punto {
private:
    int x, y;

public:
    Punto(int x, int y) : x(x), y(y) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    bool operator==(const Punto& otro) const {
        return x == otro.x && y == otro.y;
    }
};
#pragma once
