#include "Robot.h"
#include <iostream>
#include <cmath>

using namespace std;


void Robot::init() {
    location.set(0, 0);
    orientation = EAST;

}
void Robot::print() const {
    cout << "Robot is at ";
    location.print();
    cout << " and is facing ";

    switch (orientation) {
        case NORTH:
            cout << "North.";
            break;
        case SOUTH:
            cout << "South.";
            break;
        case EAST:
            cout << "East.";
            break;
        case WEST:
            cout << "West.";
            break;
    }
    cout << endl;
}

void Robot::setOrientation(orientation_type orientation) {
    this->orientation = orientation;
}

bool Robot::forward() {
    int currentX = location.getX();
    int currentY = location.getY();

    switch (orientation) {
        case NORTH:
            if (!northEnd()) {
                location.set(currentX, currentY + 1);
                return true;
            }
            break;
        case SOUTH:
            if (!southEnd()) {
                location.set(currentX, currentY - 1);
                return true;
            }
            break;
        case EAST:
            if (!eastEnd()) {
                location.set(currentX + 1, currentY);
                return true;
            }
            break;
        case WEST:
            if (!westEnd()) {
                location.set(currentX - 1, currentY);
                return true;
            }
            break;
    }
    return false;
}


bool Robot::reverse() {
    int currentX = location.getX();
    int currentY = location.getY();

    switch (orientation) {
        case SOUTH:
            if (!northEnd()) {
                location.set(currentX, currentY + 1);
                return true;
            }
            break;
        case North:
            if (!southEnd()) {
                location.set(currentX, currentY - 1);
                return true;
            }
            break;
        case WEST:
            if (!eastEnd()) {
                location.set(currentX + 1, currentY);
                return true;
            }
            break;
        case EAST:
            if (!westEnd()) {
                location.set(currentX - 1, currentY);
                return true;
            }
            break;
    }
    return false;
}


bool Robot::operator++(){
  return forward();
}

bool Robot::operator--(){
  return reverse();
}

float Robot::operator-(const Robot& other) const{
  int dx = location.getX() - other.location.getX();
  int dy = location.getY() - other.location.getY();

  return sqrt(pow(dx, 2) + pow(dy,2));
}

bool Robot::operator==(const Robot& other) const{
  return location == other.location;
}





void Robot::turnCW() {
    switch (orientation) {
        case NORTH:
            orientation = EAST;
            break;
        case EAST:
            orientation = SOUTH;
            break;
        case SOUTH:
            orientation = WEST;
            break;
        case WEST:
            orientation = NORTH;
            break;

    }
}

void Robot::turnAntiCW() {
    switch (orientation) {
        case NORTH:
            orientation = WEST;
            break;
        case WEST:
            orientation = SOUTH;
            break;
        case SOUTH:
            orientation = EAST;
            break;
        case EAST:
            orientation = NORTH;
            break;
    }
}

bool Robot::eastEnd() const{
    return location.getX() == 9;
}
bool Robot::westEnd() const{
    return location.getX() == 0;
}
bool Robot::southEnd() const{
    return location.getY() == 0;
}
bool Robot::northEnd() const{
    return location.getY() == 9;
}

bool Robot::zag() {
    if (orientation == EAST && eastEnd() && !northEnd()){
        turnAntiCW();
        forward();
        turnAntiCW();
        return true;
    }
    return false;
}

bool Robot::zig() {
    if(orientation == WEST && westEnd() && !northEnd()){
        turnCW();
        forward();
        turnCW();
        return true;
    }
    return false;
}

Point Robot::getLocation() const {
    return location;
}
