
#include "Point.h"
#include<iostream>

using namespace std;

void Point::set(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

void Point::print() const {
    cout << "(" << getX() << " , " << getY() << ")";
}