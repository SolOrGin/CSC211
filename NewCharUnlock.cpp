#include "NewCharUnlock.h"
#include <iostream>

using namespace std;



void NewCharUnlock::init(){
    location.set(0, 0);
}

void NewCharUnlock::print() const{
    cout << "Player is at ";
    location.print();
    cout << endl;
}

bool NewCharUnlock::moveNorth(){
    int currentX = location.getX();
    int currentY = location.getY();

    if (!northEnd()){
        location.set(currentX, currentY + 1);
        return true;
    }
    cout << "Wall there buddy, cannot move North" << endl;
    return false;
}
bool NewCharUnlock::moveSouth(){
    int currentX = location.getX();
    int currentY = location.getY();

    if (!southEnd()){
        location.set(currentX, currentY - 1);
        return true;
    }
    cout << "Wall there buddy, cannot move South" << endl;
    return false;
}
bool NewCharUnlock::moveEast(){
    int currentX = location.getX();
    int currentY = location.getY();

    if (!eastEnd()){
        location.set(currentX + 1, currentY);
        return true;
    }
    cout << "Wall there buddy, cannot move East" << endl;
    return false;
}
bool NewCharUnlock::moveWest(){
    int currentX = location.getX();
    int currentY = location.getY();

    if (!westEnd()){
        location.set(currentX - 1, currentY);
        return true;
    }
    cout << "Wall there buddy, cannot move West" << endl;
    return false;
}
bool NewCharUnlock::eastEnd()const{
    return location.getX() == 9;
}
bool NewCharUnlock::westEnd()const{
    return location.getX() == 0;
}
bool NewCharUnlock::northEnd()const{
    return location.getY() == 9;
}
bool NewCharUnlock::southEnd()const{
    return location.getY() == 0;
}
     
Point NewCharUnlock::getLocation() const{
    return location;
}

