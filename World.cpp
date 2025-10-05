
#include "World.h"
#include <iostream>
#include <string>


using namespace std;

void World::printC() const {
    cout << "The coins have landed: " <<  endl;
    for (int i = 0; i < 3; i++) {
        cout << "Coin " << i + 1 << ": ";
        coins[i].print();
        cout << endl;
    }
}


void World::set(int i, int x, int y) {
    if (i >= 0 && i < 3) {
        coins[i].set(x, y);
    }
}


int World::findCoinAt(const Point& location) const{
    for (int i = 0; i < 3; i++){
        if (location.getX() == coins[i].getX() && location.getY() == coins[i].getY()){
            return i;
        }
    }
    return -1;
}


int World::getCoinsFound() const {
    return coinsFound;
}

Point World::getCoin(int i)const{
    return coins[i];
}

void World::initGrid(){
    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            grid[x][y] = '.';
       }
       
    }

    for (int i = 0; i < 3; i++){
        int x = coins[i].getX();
        int y = coins[i].getY();
        grid[x][y] = 'C';
    }

    coinsFound = 0;
    for (int i = 0; i < 3; i++){
        coinsFoundAlert[i] = false;
    }
}

void World::updateGrid(int x, int y){
    Point tempLocation;
    tempLocation.set(x, y);
    int coinIndex = findCoinAt(tempLocation);
    if(coinIndex != -1 && !coinsFoundAlert[coinIndex]){

        grid[x][y] = 'O';
        coinsFound++;
        coinsFoundAlert[coinIndex] = true;
    }   
    else{
        grid[x][y] = 'x';
    }
    
}

void World::printGrid(const Point& robotLocation, const Point& playerLocation) const {

    cout << "- - - -\t Map \t- - - -" << endl;

    for (int y = 9; y >= 0; y--){
        cout << y << " | ";
        for (int x = 0; x < 10; x++){
            if (x == robotLocation.getX() && y == robotLocation.getY()){
                cout << "R ";
            }
            else if (x == playerLocation.getX() && y == playerLocation.getY()){
                cout << "P ";
            }
            else{
                cout << grid[x][y] << " ";
            }
        }
        cout << endl;
    }
    cout << "- - - - - - - - - - - - - - " << endl;
    cout << "    0 1 2 3 4 5 6 7 8 9" << endl;
    cout << "Legend:  . = Undiscovered map, C = Coin, x = Map unlock, O = Coin Found, R = Robot" << endl;
    cout << "Robot is at: ";
    robotLocation.print();
    cout << endl;
    cout << "Player is at: ";
    playerLocation.print();
    cout << endl;
}
